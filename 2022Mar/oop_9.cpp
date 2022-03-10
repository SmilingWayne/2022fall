#include <iostream>
#include <vector>
#include <fstream>

// 设计的专门的处理EDA比赛的数据结构
using namespace std;

void func_2()
{
    string t = "abbbbcs";
    string g = "bs";
    int idx = t.find(g);
    vector<int> loc;
    int pre = 0;

    while (idx >= 0)
    {
        loc.push_back(pre + idx);
        pre = pre + idx + g.size() - 1;
        t = t.substr(idx + 1);
        idx = t.find(g);
    }
    for (auto i : loc)
    {
        cout << i << endl;
    }
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

int main()
{
}