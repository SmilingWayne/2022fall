#include "Reallocate.h"

// 三态函数，判断两个double在eps精度下的大小关系
int dcmp(double x)
{
    if (fabs(x) < eps)
        return 0;
    else
        return x < 0 ? -1 : 1;
}

//判断点Q是否在P1和P2的线段上
bool OnSegment(Point P1, Point P2, Point Q)
{
    return dcmp((P1 - Q) ^ (P2 - Q)) == 0 && dcmp((P1 - Q) * (P2 - Q)) <= 0;
}

//判断点P在多边形内-射线法
/**
 * @param: size_ edges of the polygon
 * @param: polygon: vectors of edges
 * @param: P current point
 * */
bool InPolygon(Point P, const size_t &size_, const vector<Point> &polygon)
{
    bool flag = false;
    Point P1, P2; //多边形一条边的两个顶点
    for (size_t i = 0, j = size_ - 1; i < size_; j = i++)
    {
        j = j % size_;
        P1 = polygon[i];
        P2 = polygon[j];
        if (OnSegment(P1, P2, P))
            return true; //点在多边形一条边上
        if ((dcmp(P1.y - P.y) > 0 != dcmp(P2.y - P.y) > 0) && dcmp(P.x - (P.y - P1.y) * (P1.x - P2.x) / (P1.y - P2.y) - P1.x) < 0)
            flag = !flag;
    }
    return flag;
}

/**
 * 将double保留一位小数
 * 类似python round(, 1)操作
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
double Generate_Double(const double &_min, const double &_max)
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

Point GeneratePoint(const vector<vector<Point> > &polygons, const vector<Point> &init_Polygon, const double &min_x, const double &max_x, const double &min_y, const double &max_y, const unordered_set<Point, Point_Hash> &set)
{
    bool flag = true;
    Point new_Point = Point(0, 0);
    while (flag)
    {
        double new_x = Generate_Double(min_x, max_x);
        double new_y = Generate_Double(min_y, max_y);
        new_Point = Point(new_x, new_y);
        if (set.find(new_Point) != set.end())
        {
            continue;
        }
        if (InPolygon(new_Point, init_Polygon.size(), init_Polygon) == false)
        {
            for (size_t i = 0; i < polygons.size(); i++)
            {
                if (InPolygon(new_Point, polygons[i].size(), polygons[i]))
                {
                    // cout << "F " << endl;
                    break;
                }
                flag = false;
            }
        }
        else
        {
            continue;
        }
    }
    return new_Point;
}

// void test_1()
// {
//     vector<Point> poly;
//     poly.push_back(Point(0, 0));
//     poly.push_back(Point(0, 100));
//     poly.push_back(Point(100, 100));
//     poly.push_back(Point(100, 0));
//     cout << InPolygon(Point(0, 0), 4, poly) << endl;
// }

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

vector<Point> get_locations(const string &a)
{
    vector<Point> result;
    regex reg("-?(([1-9]\\d*\\.\\d*)|(0\\.\\d*[1-9]\\d*))");
    smatch matchResult;
    const sregex_iterator end;
    int idx = 1;
    Point cur_point(0, 0);
    for (sregex_iterator iter(a.begin(), a.end(), reg); iter != end; ++iter)
    {
        if (idx == 2)
        {

            cur_point.y = atof(iter->str().c_str());
            result.push_back(cur_point);
            idx = 1;
        }
        else
        {
            cur_point.x = atof(iter->str().c_str());
            idx++;
        }
    }
    return result;
}

/**
 * 进行坐标修正
 * */
vector<Point> modify_axis(vector<Point> &ori, const double &modify_x, const double &modify_y)
{
    for (int i = 0; i < ori.size(); i++)
    {
        ori[i].x -= modify_x;
        ori[i].y -= modify_y;
    }
    return ori;
}

// void output_ans(vector<OUTPUT> &p)
// {

//     ofstream myfile;
//     myfile.open("/Users/apple/Sites/jstest/AEDA/fifthtest.csv");
//     for (auto &t : p)
//     {
//         myfile << t.loc.x << "," << t.loc.y << "," << t.type_ << "," << t.mod_num << "\n";
//     }
//     myfile.close();
// }

// void test_2()
// {
//     vector<Point> poly;
//     poly.push_back(Point(166.8, 446.9));
//     poly.push_back(Point(166.8, 494.7));
//     poly.push_back(Point(111.8, 494.7));
//     poly.push_back(Point(111.8, 508.6));
//     poly.push_back(Point(50, 508.6));
//     poly.push_back(Point(50, 446.9));
//     cout << InPolygon(Point(139, 512.9), 10, poly) << endl;

//     cout << InPolygon(Point(161.5, 465.9), 10, poly) << endl;

//     cout << InPolygon(Point(179.4, 450.4), 10, poly) << endl;
// }

int main()
{

    string data_path = fs::current_path();
    data_path.append("/data/16-");
    // const string data_path = "Cpps/EDA/data/16-";

    vector<OUTPUT> ans;

    // 判断border的范围
    double border_x_min = __MAX;
    double border_x_max = -__MAX;
    double border_y_min = __MAX;
    double border_y_max = -__MAX;

    string current_connect_path = data_path;
    string current_data_path = data_path;
    current_data_path.append(to_string(13860));
    current_data_path.append("/connect_1.txt");
    vector<string> t = func_1(current_data_path);

    unordered_set<Point, Point_Hash> occupied_Points;

    for (int i = 13860; i < 13861; i++)
    {
        double modify_x = 1e10;
        double modify_y = 1e10;
        string current_data_path = data_path;
        current_data_path.append(to_string(i));
        current_data_path.append("/Module.txt");
        vector<string> t = func_1(current_data_path);
        string Rule_;

        int module_name_ = -1;
        int module_count = -1;
        int counter_port = 0;
        vector<vector<Point> > Modules_(25, vector<Point>()); // FIXME: 设定最多25块Modules
        vector<int> Module_Ports(25, 0);                      // 记录每个Module可能有的port数量，默认最多25个Modules
        for (auto &line : t)
        {
            if (line.find("Area") != string::npos)
            {
                vector<Point> Area_ = get_locations(line);
                for (size_t i = 0; i < Area_.size(); i++)
                {
                    // 确定图是否需要修正
                    modify_x = min(Area_[i].x, modify_x);
                    modify_y = min(Area_[i].y, modify_y);
                }
                Area_ = modify_axis(Area_, modify_x, modify_y);
                for (auto &Area_Point : Area_)
                {
                    border_x_max = max(border_x_max, Area_Point.x);
                    border_x_min = min(border_x_min, Area_Point.x);
                    border_y_max = max(border_y_max, Area_Point.y);
                    border_y_min = min(border_y_min, Area_Point.y);
                }
            }
            else if (line.find("Module") != string::npos)
            {
                counter_port = 0;
                module_name_ = atoi(line.substr(8, line.size()).c_str());
                module_count = max(module_count, module_name_);
            }
            else if (line.find("Boundary") != string::npos)
            {
                if (module_name_ >= (int)Modules_.size())
                {
                    cout << "当前模块" << i << endl;

                    perror("Modules 数量多于! 重新设置Modules数量. 当前板块 \n");
                    break;
                }
                vector<Point> cur_module_boundary_ = get_locations(line);
                cur_module_boundary_ = modify_axis(cur_module_boundary_, modify_x, modify_y);
                Modules_[module_name_ - 1] = cur_module_boundary_;
            }
            else if (line.find("Port") != string::npos)
            {
                counter_port++;
                Module_Ports[module_name_ - 1] += 1;
            }
        }
        Modules_.erase(Modules_.begin() + module_count, Modules_.end());
        Module_Ports.erase(Module_Ports.begin() + module_count, Module_Ports.end());
        vector<vector<Point> > resize_Modules_(Modules_.size(), vector<Point>());
        for (size_t i = 0; i < Modules_.size(); i++)
        {
            double min_x = __MAX;
            double max_x = -__MAX;
            double min_y = __MAX;
            double max_y = -__MAX;
            vector<Point> temp_module = Modules_[i];
            for (size_t j = 0; j < temp_module.size(); j++)
            {
                min_x = min(min_x, temp_module[j].x - ran_range);
                min_y = min(min_y, temp_module[j].y - ran_range);
                max_x = max(max_x, temp_module[j].x + ran_range);
                max_y = max(max_y, temp_module[j].y + ran_range);
                min_x = max(min_x, border_x_min);
                max_x = min(max_x, border_x_max);
                min_y = max(min_y, border_y_min);
                max_y = min(max_y, border_y_max);
                vector<Point> resize_Module = {Point(min_x, min_y), Point(max_x, min_y), Point(max_x, max_y), Point(min_x, max_y)};
                resize_Modules_[i] = resize_Module;
            }
            cout << "Ori Modules:" << endl;
            for (size_t k = 0; k < temp_module.size(); k++)
            {
                cout << temp_module[k];
                ans.push_back(Point4Out(temp_module[k], "module", (int)(i + 1)));
            }
            cout << "Resize Modules:" << endl;
            for (size_t k = 0; k < resize_Modules_[i].size(); k++)
            {
                cout << resize_Modules_[i][k];
            }
            for (size_t l = 0; l < Module_Ports[i]; l++)
            {
                Point np = GeneratePoint(Modules_, Modules_[i], min_x, max_x, min_y, max_y, occupied_Points);
                occupied_Points.emplace(np);
                ans.push_back(Point4Out(np, "port", (int)(i + 1)));
                cout << "New Point:" << endl;
                cout << np;
            }
        }
    }
}
