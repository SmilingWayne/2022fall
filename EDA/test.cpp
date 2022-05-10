#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <string>
#include <unordered_map>
#include <ctime>
#include <cmath>
using namespace std;

bool judge(string &a, string &b)
{
    return atoi(a.substr(1, a.size()).c_str()) < atoi(b.substr(1, b.size()).c_str());
}

/**
 * 将double保留一位小数
 * 类似python round(，1)操作
 * */
double transform_double(double a)
{
    string t = to_string(a);
    t = t.substr(0, t.find(".") + 2);
    return (double)atof(t.c_str());
}

/**
 * 产生在一个区间内的double，手动设置保留一位小数，去除末尾0
 * */
double generate_Double(const double &_min, const double &_max)
{
    if (_min >= _max)
    {
        perror("产生随机数区间有误");
        return -1;
    }
    random_device seed;
    ranlux48 engine(seed());                                      // 这里可以手动设置随机数种子
    uniform_real_distribution<> distrib(ceil(_min), floor(_max)); // 产生符合条件的随机数
    double ans_ = distrib(engine);
    return transform_double(ans_);
}

/**
 *  产生随机Port位置
 * */
vector<double> generate_Port(vector<vector<double> > &ori_module, vector<double> &new_border)
{
    double new_x = generate_Double(new_border[0], new_border[1]); // 产生x_new
    double new_y = generate_Double(new_border[2], new_border[3]);
}
// vector<double> select_pos(const vector<vector<double> > &ori, const double &x_max, const double &x_min, const double &y_max, const double &y_min)
// {
//     // while (true)
//     // {
//     //     double dum_x =
//     // }
// }
// int main()
// {

//     //
//     cout << GenerateRandomReal(120, 1000) << endl;
// }

int main()
{
    double min = 200.4;
    double max = 400.5;
    random_device seed;                                         //硬件生成随机数种子
    ranlux48 engine(seed());                                    //利用种子生成随机数引擎
    uniform_real_distribution<> distrib(ceil(min), floor(max)); //设置随机数范围，并为均匀分布
    for (int i = 0; i < 100; i++)
    {
        double random = distrib(engine); //随机数
        cout << transform_double(random) << endl;
        // cout <<  setprecision(2) << random << endl;
    }
}
