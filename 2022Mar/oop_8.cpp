#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <random>
#include <cstring>
#include <regex>
#include <algorithm>
using namespace std;

class output_test
{
    string name;
    string number;
    friend ostream &operator<<(ostream &out, const output_test &a);

public:
    output_test(){};
    output_test(string a, string b)
    {
        name = a;

        number = b;
    }
};
ostream &operator<<(ostream &out, const output_test &a)
{
    out << "Name: " << a.name << " Number :" << a.number << '\n';
    return out;
}

class Module
{
    friend class Port;
    vector<vector<double> > Locations;
    string Module_name;
    // string Type;

public:
    Module()
    {
        Module_name = "None";
    };

    Module(const vector<vector<double> > &a, const string N)
    {
        Locations = a;
        Module_name = N;
    }
    // ~Module(){}
};

class Chip
{
    friend class Module;
    vector<vector<double> > Locations;
    string Rules;
    vector<Module> Modules;

public:
    Chip() {}
    Chip(const vector<vector<double> > &a, const string &r, const vector<Module> &m)
    {
        Locations = a;
        Rules = r;
        Modules = m;
    }
};

class Port
{
    vector<vector<double> > Locations;
    int Port_number;

public:
    Port() {}
    Port(const vector<vector<double> > &l, const int &p)
    {
        Locations = l;
        Port_number = p;
    }
};

vector<string> func_1(const string &input_file_path)
{

    // string out_name = "./name.txt";
    // string duplicate_name = "./name_2.txt";
    vector<string> file_content;
    // ofstream fout(out_name.c_str()); // default mode is ios::out | ios::trunc
    ifstream inp(input_file_path);
    // ofstream dup_fout(duplicate_name.c_str());
    if (!inp)
    {
        std::cerr << "Error: open file for output failed!" << std::endl;
        return file_content;
        // exit(-1); // in <cstdlib> header
    }
    // for (int i = 0; i < rand() % 200; i++)
    // {
    //     string ip = "";
    //     for (int j = 0; j < rand() % 30; j++)
    //     {
    //         ip.push_back(rand() % 26 + 'a');
    //     }
    //     fout << ip << endl;
    // }
    // fout.close();
    // if (!inp)
    // {
    //     cerr << "Fail!" << endl;
    //     exit(-1);
    // }
    else
    {
        while (!inp.eof())
        {
            string str = "";
            getline(inp, str);
            file_content.push_back(str);
        }
        return file_content;
    }
}

/**
 * 实现了对位置坐标的处理
 *
 * */
vector<vector<double> > get_locations(const string &a)
{
    vector<double> ans;
    vector<vector<double> > res;
    regex reg("-?(([1-9]\\d*\\.\\d*)|(0\\.\\d*[1-9]\\d*))");
    smatch matchResult;

    const sregex_iterator end;
    int idx = 0;
    for (sregex_iterator iter(a.begin(), a.end(), reg); iter != end; ++iter)
    {
        if (idx == 2)
        {
            res.push_back(ans);
            ans.clear();
            idx = 1;
        }
        else
            idx++;
        ans.push_back(stold(iter->str()));
    }
    res.push_back(ans);
    return res;
}

void display_loc(const vector<vector<double> > &a)
{
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

/**
 * TODO: 了解一下析构函数的特性 这个项目可以暂缓继续
 *
 * */
void read_chip(const vector<string> &lines)
{
    Chip c;
    vector<vector<double> > area;
    vector<Module> modules;
    string rule;
    for (auto line : lines)
    {
        if (line.find("Area") != string::npos)
        {
            area = get_locations(line);
        }
        else if (line.find("Module") != string::npos)
        {
        }
        else if (line.find("Boundary") != string::npos)
        {
        }
        else if (line.find("Port") != string::npos)
        {
        }
    }
}

int main()
{

    const string data_path = "Cpps/cpp_data/16-";
    for (int i = 10001; i < 10002; i++)
    {
        Chip current_chip;
        string current_data_path = data_path;
        current_data_path.append(to_string(i));
        current_data_path.append("/Module.txt");
        vector<string> t = func_1(current_data_path);
        for (auto &line : t)
        {

            if (line.find("Area") != string::npos)
            {
                vector<vector<double> > Area = get_locations(line);
                display_loc(Area);
            }
            else if (line.find("Boundary") != string::npos)
            {
                vector<vector<double> > Boundary = get_locations(line);
                display_loc(Boundary);
            }
        }
    }
}