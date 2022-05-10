#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <random>
#include <cstring>
#include <regex>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <ctime>
#include <cmath>
#include <bitset>

using namespace std;
namespace fs = std::filesystem;
typedef long long ll;

const double eps = 1e-6;
const double PI = acos(-1);
const double __MAX = 1e9;
const double ran_range = 15;

/**
 * 定义输入的节点的结构体
 * */
typedef struct Point
{
    double x, y;
    string type;
    Point(double x = 0, double y = 0, string t_ = "vertex") : x(x), y(y), type(t_) {}

    //向量+
    Point operator+(const Point &b) const
    {
        return Point(x + b.x, y + b.y);
    }
    //向量-
    Point operator-(const Point &b) const
    {
        return Point(x - b.x, y - b.y);
    }
    //点积
    double operator*(const Point &b) const
    {
        return x * b.x + y * b.y;
    }
    //叉积
    // P^Q>0,P在Q的顺时针方向；<0，P在Q的逆时针方向；=0，P，Q共线，可能同向或反向
    double operator^(const Point &b) const
    {
        return x * b.y - b.x * y;
    }
    double operator&(const Point &b) const
    {
        return sqrt(pow((x - b.x), 2) + pow((y - b.y), 2));
    }
    friend ostream &operator<<(ostream &out, const Point &m);

} Point;

/**
 * Point 结构体对应的Hash函数
 * */
struct Point_Hash
{
    size_t operator()(const Point &_r) const
    {
        string tmp = to_string(_r.x) + to_string(_r.y);
        return hash<string>()(tmp);
    }
};
ostream &operator<<(ostream &out, const Point &p)
{
    cout << "(" << p.x << ", " << p.y << ")" << endl;
    return out;
}
bool operator==(const Point &X, const Point &Y)
{
    return (X.x == Y.x) && (X.y == Y.y);
}

typedef struct Point4Out
{
    Point loc;
    string type_;
    int mod_num;

    Point4Out(Point x, string y, int m) : loc(x), type_(y), mod_num(m) {}
} OUTPUT;

vector<vector<string> > read_csv_without_head(string filename) //传入文件所在的位置
{
    ifstream inFile(filename);
    string lineStr;
    vector<vector<string> > strArray;

    while (getline(inFile, lineStr))
    {

        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;
        while (getline(ss, str, ','))
        {
            lineArray.push_back(str);
        }
        strArray.push_back(lineArray);
    }
    return strArray;
}

vector<vector<string> > read_csv_with_head(string filename) //传入文件所在的位置
{
    ifstream inFile(filename);
    string lineStr;
    vector<vector<string> > strArray;
    bool isHead = true;
    while (getline(inFile, lineStr))
    {
        if (isHead)
        {
            isHead = false;
            continue;
        }
        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;
        while (getline(ss, str, ','))
        {
            lineArray.push_back(str);
        }
        strArray.push_back(lineArray);
    }
    return strArray;
}

template <class T1, class T2>
struct pair_hash
{
    size_t operator()(const pair<T1, T2> &p) const
    {
        return hash<T1>()(p.first) ^ hash<T2>()(p.second); //异或思想
    }

    bool operator()(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) const
    {
        return equal_to<T1>()(lhs.first, rhs.first) && equal_to<T2>()(lhs.second, rhs.second);
    }
};