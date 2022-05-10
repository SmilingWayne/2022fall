#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <cmath>
#include <unordered_set>
#include <unordered_map>

const double __MAX = 1e9;
using namespace std;
namespace fs = std::filesystem;

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
    // 计算两个点之间的距离
    double operator&(const Point &b) const
    {
        return sqrt(pow((x - b.x), 2) + pow((y - b.y), 2));
    }
    friend ostream &operator<<(ostream &out, const Point &m);

} Point;
ostream &operator<<(ostream &out, const Point &p)
{
    cout << "(" << p.x << ", " << p.y << ")" << endl;
    return out;
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

void output_result(vector<pair<int, int> > &graph, vector<Point> &points, string &path)
{

    ofstream myfile;
    try
    {
        myfile.open(path);
    }
    catch (...)
    {
        cout << "文件" << path << "打开失败" << endl;
    }
    myfile << "Start_X"
           << ","
           << "Start_Y"
           << ","
           << "End_X"
           << ","
           << "End_Y"
           << "\n";
    for (auto &t : graph)
    {
        myfile << points[t.first].x << "," << points[t.first].y << "," << points[t.second].x << "," << points[t.second].y << "\n";
    }
    myfile.close();
}

vector<pair<int, int> > Prim(vector<vector<double> > &Graph, vector<double> &lowcost, vector<int> &closest, vector<bool> &visited)
{
    int size = lowcost.size();
    visited[0] = true;
    vector<pair<int, int> > result;
    double ans = 0;
    int pre_flag = 0;
    vector<int> pre(closest.size(), 0);
    for (int i = 1; i < size; i++)
    {
        lowcost[i] = Graph[0][i];
        closest[i] = 0;
    }
    // double ans = 0;
    for (int i = 0; i < size; i++)
    {
        double min_ = __MAX;
        int index = -1;
        for (int j = 1; j < size; j++)
        {
            if (lowcost[j] < min_ && !visited[j])
            {
                min_ = lowcost[j];
                index = j;
            }
        }
        if (index == -1 && min_ == __MAX)
        {
            break;
        }
        ans += min_;
        visited[index] = true;
        for (int j = 0; j < size; j++)
        {
            if ((Graph[index][j] < lowcost[j]) && (!visited[j]))
            {
                lowcost[j] = Graph[index][j];
                closest[j] = index;
                // pre[j] = index;
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        result.push_back(make_pair(i, closest[i]));
    }
    return result;
}

void implement_Version1()
{
    string target_path = fs::current_path();
    target_path.append("/resultOACDT.csv");

    string output_path = "/Users/apple/Sites/jstest/AEDA/EDAvisualization/resultMST.csv";
    vector<vector<string> > csv_contents = read_csv_with_head(target_path);
    vector<Point> points;
    unordered_set<pair<double, double>, pair_hash<double, double> > set;
    for (auto &content : csv_contents)
    {
        pair<double, double> tmp = make_pair(stod(content[0]), stod(content[1]));
        if (set.empty())
        {
            set.emplace(tmp);
            points.push_back(Point(tmp.first, tmp.second));
            continue;
        }
        if (set.find(tmp) == set.end())
        {
            Point t = Point(tmp.first, tmp.second);
            points.push_back(t);
            set.emplace(tmp);
        }
    }

    vector<vector<double> > Graph(points.size(), vector<double>(points.size(), 0));
    for (int i = 0; i < points.size(); i++)
    {
        for (int j = i + 1; j < points.size(); j++)
        {
            Graph[i][j] = (points[i] & points[j]);
            Graph[j][i] = Graph[i][j];
        }
        Graph[i][i] = __MAX;
    }
    vector<double> lowcost(Graph.size(), 0);
    vector<int> closet(Graph.size(), 0);
    vector<bool> visited(Graph.size(), false);
    vector<pair<int, int> > z = Prim(Graph, lowcost, closet, visited);
    for (auto &t : z)
    {
        cout << t.first << "->" << t.second << endl;
    }
}

vector<pair<double, double> > get_Point_Type()
{
    vector<vector<string> > csv_contents = read_csv_with_head("/Users/apple/Sites/jstest/Cpps/EDA/resultORI.csv");
    vector<pair<double, double> > ans;
    for (auto &content : csv_contents)
    {
        if (content[2] == "module")
        {
            ans.push_back(make_pair(stod(content[0]), stod(content[1])));
        }
    }
    return ans;
}

void implement_Version2()
{
    string target_path = fs::current_path();
    target_path.append("/resultOACDT.csv");
    string output_path = "/Users/apple/Sites/jstest/AEDA/EDAvisualization/resultOACDTMST_deleteleaf.csv";
    vector<vector<string> > csv_contents = read_csv_with_head(target_path);
    vector<Point> points;
    unordered_set<pair<double, double>, pair_hash<double, double> > set;
    // vector<pair<double, double > >
    // 给你看个东西
    // 我希望早上没删掉
    unordered_map<pair<double, double>, int, pair_hash<double, double> > map;

    set.emplace(make_pair(stod(csv_contents[0][0]), stod(csv_contents[0][1])));
    map.emplace(make_pair(stod(csv_contents[0][0]), stod(csv_contents[0][1])), 0);
    points.push_back(Point(stod(csv_contents[0][0]), stod(csv_contents[0][1])));
    int idx = 1;
    for (auto &content : csv_contents)
    {
        pair<double, double> tmp = make_pair(stod(content[0]), stod(content[1]));
        pair<double, double> tmp2 = make_pair(stod(content[2]), stod(content[3]));
        if (set.find(tmp) == set.end())
        {
            Point t = Point(tmp.first, tmp.second);
            points.push_back(t);
            map.emplace(tmp, idx++);
            set.emplace(tmp);
        }
        if (set.find(tmp2) == set.end())
        {
            Point t = Point(tmp2.first, tmp2.second);
            points.push_back(t);
            map.emplace(tmp2, idx++);
            set.emplace(tmp2);
        }
    }
    vector<vector<double> > Graph(points.size(), vector<double>(points.size(), __MAX));

    for (auto &content : csv_contents)
    {
        double loc0 = stod(content[0]);
        double loc1 = stod(content[1]);
        double loc2 = stod(content[2]);
        double loc3 = stod(content[3]);
        int pre = map[make_pair(loc0, loc1)];
        int post = map[make_pair(loc2, loc3)];
        Graph[pre][post] = Point(loc0, loc1) & Point(loc2, loc3);
        Graph[post][pre] = Graph[pre][post];
    }
    vector<double> lowcost(Graph.size(), 10000);
    vector<int> closet(Graph.size(), 0);
    vector<bool> visited(Graph.size(), false);
    vector<pair<int, int> > z = Prim(Graph, lowcost, closet, visited);

    vector<pair<double, double> > module_points = get_Point_Type();

    vector<int> calculate_leaf(300, 0);
    for (int i = 0; i < z.size(); i++)
    {
        calculate_leaf[z[i].first] += 1;
        calculate_leaf[z[i].second] += 1;
    }

    vector<pair<int, int> > new_z;
    // vector<pair<int, int> >
    for (auto &nz : z)
    {
        bool inp = true;
        if (calculate_leaf[nz.first] == 1)
        {
            Point cur = points[nz.first];
            if (find(module_points.begin(), module_points.end(), make_pair(cur.x, cur.y)) != module_points.end())
            {
                inp = false;
            }
        }
        if (calculate_leaf[nz.second] == 0)
        {
            Point cur = points[nz.second];
            if (find(module_points.begin(), module_points.end(), make_pair(cur.x, cur.y)) != module_points.end())
            {
                inp = false;
            }
        }
        if (inp)
        {
            new_z.push_back(nz);
        }
    }
    output_result(new_z, points, output_path);
    // for(int i = 0 ;i  <)

    // for (auto &p : test)
    // {
    //     cout << map[make_pair(p.x, p.y)] << endl;
    // }
}

int main()
{
    implement_Version2();
}