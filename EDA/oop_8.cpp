#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <random>
#include <cstring>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;
class ExceptionClass
{
    friend ostream &operator<<(ostream &out, const ExceptionClass &a);
    string name;

public:
    ExceptionClass(){};
    ExceptionClass(const string &a)
    {
        name = a;
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
    void dis()
    {
        cout << "\nNumber :" << Port_number << "\n";
        for (auto &k : Locations)
        {
            for (auto &d : k)
            {
                cout << d << " ";
            }
        }
    }
};

class Module
{
    friend class Port;
    vector<vector<double> > Locations;
    string Module_name;
    vector<Port> ports;

public:
    Module()
    {
        Module_name = "";
        Locations.clear();
        ports.clear();
        // Module_name = "None";
    };

    Module(const vector<vector<double> > &a, const string N, const vector<Port> &p)
    {
        Locations = a;
        Module_name = N;
        ports = p;
    };
    string get_Module_Name()
    {
        return this->Module_name;
    }
    vector<Port> get_Module_Port()
    {
        return this->ports;
    }
    vector<vector<double> > get_Boundary()
    {
        return this->Locations;
    }
    void dispM()
    {
        cout << Module_name << " HH\n";
        cout << ports.size() << " END!\n";
    };
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

vector<string> func_1(const string &input_file_path)
{
    vector<string> file_content;
    ifstream inp(input_file_path);
    if (!inp)
    {
        std::cerr << "Error: open file for output failed!" << std::endl;
        return file_content;
        // exit(-1); // in <cstdlib> header
    }
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
bool sort_module(Module &a, Module &b)
{
    return atoi(a.get_Module_Name().substr(1, a.get_Module_Name().size()).c_str()) < atoi(b.get_Module_Name().substr(1, b.get_Module_Name().size()).c_str());
}

/**
 * 一个独立实现的分割字符串的函数
 * */
void splitString(vector<string> &strings, const string &org_string, const string &seq)
{
    string::size_type p1 = 0;
    string::size_type p2 = org_string.find(seq);

    while (p2 != string::npos)
    {
        if (p2 == p1)
        {
            ++p1;
            p2 = org_string.find(seq, p1);
            continue;
        }
        strings.push_back(org_string.substr(p1, p2 - p1));
        p1 = p2 + seq.size();
        p2 = org_string.find(seq, p1);
    }

    if (p1 != org_string.size())
    {
        strings.push_back(org_string.substr(p1));
    }
}

// void modify_axis(vector<vector<double> > )
/**
 * 进行坐标修正
 * */
vector<vector<double> > modify_axis(vector<vector<double> > &ori, const double &modify_x, const double &modify_y)
{
    for (int i = 0; i < ori.size(); i++)
    {
        ori[i][0] -= modify_x;
        ori[i][1] -= modify_y;
    }
    return ori;
}

/**
 * 计算两个点之间的差乘
 * */
double cross(const vector<double> &p0, const vector<double> &p1, const vector<double> &p2)
{
    return (p1[0] - p0[0]) * (p2[1] - p0[1]) - (p2[0] - p0[0]) * (p1[1] - p0[1]);
}

/**
 * 判断一个点是否在一个多边形内
 * */
bool Compl_inside_convex(const vector<double> &p, const vector<vector<double> > &con, int n)
{
    double eps = 1e-5;
    if (n < 3)
        return false;
    if (cross(con[0], p, con[1]) > -eps)
        return false;
    if (cross(con[0], p, con[n - 1]) < eps)
        return false;

    int i = 2, j = n - 1;
    int line = -1;
    while (i <= j)
    {
        int mid = (i + j) >> 1;
        if (cross(con[0], p, con[mid]) > -eps)
        {
            line = mid;
            j = mid - 1;
        }
        else
            i = mid + 1;
    }
    return cross(con[line - 1], p, con[line]) < -eps;
}

int main()
{
    const string data_path = "Cpps/EDA/data/16-";
    double ran_range = 15;
    int idx = 0;
    string current_connect_path = data_path;
    string current_data_path = data_path;
    current_data_path.append(to_string(13860));
    current_data_path.append("/connect_1.txt");
    vector<string> t = func_1(current_data_path);
    unordered_map<int, vector<pair<int, int> > > connect_map;
    unordered_map<int, int> connect_map2;
    int Link_ = 1;
    for (int i = 0; i < t.size(); i += 3)
    {

        string mod_connect = t[i + 1];
        string mod_port = t[i + 2];
        vector<pair<int, int> > connect_;

        vector<string> arr_mod_connect;
        vector<string> arr_port_connect;
        splitString(arr_mod_connect, mod_connect, " ");
        splitString(arr_port_connect, mod_port, " ");
        if (arr_mod_connect.size() != arr_port_connect.size())
        {
            perror("数据读取错误!");
            return 0;
        }
        for (int j = 0; j < arr_mod_connect.size(); j++)
        {
            connect_.push_back(make_pair(atoi(arr_mod_connect[j].substr(1, arr_mod_connect[j].size()).c_str()), atoi(arr_port_connect[j].c_str())));
        }
        connect_map.emplace(Link_, connect_);
        Link_++;
    }
    // for (int i = 1; i <= connect_map.size(); i++)
    // {
    //     auto k = connect_map[i];
    //     for (int u = 0; u < k.size(); u++)
    //     {
    //         cout << k[u].first << "  " << k[u].second << endl;
    //     }
    // }
    for (int i = 0; i < 10; i++)
    {
        connect_map2.emplace(i, i + 1);
    }
    for (int i = 13860; i < 13861; i++)
    {
        double modify_x = 1e10;
        double modify_y = 1e10;
        string current_data_path = data_path;
        current_data_path.append(to_string(i));
        current_data_path.append("/Module.txt");
        vector<string> t = func_1(current_data_path);
        bool vis_bound = false; // 检查是否遍历过了
        Chip c;
        vector<vector<double> > area_; // area 矩阵
        vector<Module> modules;        // module板块
        string rule_;
        Module module_;
        vector<Port> ports_;
        vector<vector<double> > boundary_;
        string module_name_;
        int cur_port_num = 1;

        for (auto &line : t)
        {
            idx++;
            if (line.find("Area") != string::npos)
            {
                vector<vector<double> > Area = get_locations(line);
                for (int i = 0; i < Area.size(); i++)
                {
                    // 确定图是否需要修正
                    modify_x = min(Area[i][0], modify_x);
                    modify_y = min(Area[i][1], modify_y);
                }
                Area = modify_axis(Area, modify_x, modify_y);
            }
            else if (line.find("Module") != string::npos)
            {
                if (vis_bound)
                {
                    module_ = Module(boundary_, module_name_, ports_);
                    modules.push_back(module_);
                    ports_.clear();
                }
                module_name_ = line.substr(7, line.size());
                vis_bound = true;
            }
            else if (line.find("Rule") != string::npos)
            {
                rule_ = line.substr(5, line.size());
            }
            else if (line.find("Boundary") != string::npos)
            {
                boundary_ = get_locations(line);
                boundary_ = modify_axis(boundary_, modify_x, modify_y);
            }
            else if (line.find("Port") != string::npos)
            {
                vector<vector<double> > cur_p = get_locations(line);
                ports_.push_back(Port(cur_p, cur_port_num));
                cur_port_num = cur_port_num == 3 ? 1 : cur_port_num + 1;
            }
            if (idx == t.size())
            {
                module_ = Module(boundary_, module_name_, ports_);
                modules.push_back(module_);
                c = Chip(area_, rule_, modules);
            }
        }
        sort(modules.begin(), modules.end(), sort_module); // 针对Module进行排序 测试通过
        for (auto &j : modules)
        {
            vector<vector<double> > curr_bord = j.get_Boundary();
            double min_x = 1e10;
            double max_x = -100;
            double min_y = 1e10;
            double max_y = -100;
            for (auto &point : curr_bord)
            {
                min_x = min(min_x, point[0] - ran_range);
                max_x = max(max_x, point[0] + ran_range);
                min_y = min(min_y, point[1] - ran_range);
                max_y = max(max_y, point[1] + ran_range);
            }
            vector<double> t_ans = {min_x, max_x, min_y, max_y};
            // for (auto &yy : t_ans)
            // {
            //     cout << yy << endl;
            // }
            // cout << min_x << " " << max_x << " " << min_y << " " << max_y << "\n";
            display_loc(curr_bord);
            cout << "----\n";
        }
    }
}
