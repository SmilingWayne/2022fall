#include "Reallocate.h"

/**
 * 边的数据结构
 * */
struct Edge
{
    Point p0;
    Point p1;
    Edge() {}
    Edge(Point a, Point b) : p0(a), p1(b) {}
    double slope()
    {
        if (p0.x == p1.x)
        {
            return __MAX;
        }
        return (p0.y - p1.y) / (p0.x - p1.x);
    }
    vector<Point> getPoints()
    {
        return vector<Point>{p0, p1};
    }
};

struct Circle
{

    double x;
    double y;
    double r;

    Circle() {}
    Circle(double x_, double y_, double r_) : x(x_), y(y_), r(r_) {}
};

struct vPoint
{

    double x;
    double y;
    double r;
    Point point;
    string type;
    vPoint() {}
    vPoint(double a, double b, double c, string s = "cc") : x(a), y(b), r(c), type(s){};
};

vPoint CircumCircle(Point &a, Point &b, Point &c)
{
    double A = b.x - a.x;
    double B = b.y - a.y;
    double C = c.x - a.x;
    double D = c.y - a.y;
    double E = A * (a.x + b.x) + B * (a.y + b.y);
    double F = C * (a.x + c.x) + D * (a.y + c.y);
    double G = 2 * (A * (c.y - b.y) - B * (c.x - b.x));
    double minx, miny, dx, dy;

    double x, y, r;

    if (fabs(G) < eps)
    {
        minx = min(a.x, min(b.x, c.x));
        miny = min(a.y, min(b.y, c.y));
        dx = (max(a.x, max(b.x, c.x)) - minx) * 0.5;
        dy = (max(a.y, max(b.y, c.y)) - miny) * 0.5;
        x = minx + dx;
        y = miny + dy;
        r = dx * dx + dy * dy;
    }
    else
    {
        x = (D * E - B * F) / G;
        y = (A * F - C * E) / G;
        dx = x - a.x;
        dy = y - a.y;
        r = sqrt(dx * dx + dy * dy);
    }
    return vPoint(x, y, r);
}

typedef struct Triangle
{
    Edge e0;
    Edge e1;
    Edge e2;
    Point p0;
    Point p1;
    Point p2;
    vPoint c;

    Triangle() {}
    Triangle(Edge &e0, Edge &e1, Edge &e2)
    {
        this->e0 = e0;
        this->e1 = e1;
        this->e2 = e2;
        this->p0 = this->e0.p0;
        this->p1 = this->e0.p1;
        this->p2 = this->e1.p0;
        this->c = CircumCircle(p0, p1, p2);
    }

    bool contains(Point &point)
    {
        double pointDist = (point.x - this->c.x) * (point.x - this->c.x) + (point.y - this->c.y) * (point.y - this->c.y);
        double r = this->c.r * this->c.r;
        // cout << r << " " << pointDist << endl;
        return (pointDist < r);
    }

    // 这里少写了一个remove函数？
    vector<Edge> getEdges()
    {
        return vector<Edge>{e0, e1, e2};
    }

} Triangle;

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

vector<Edge> getOutSizeEdges(vector<Triangle> &triangles)
{
    vector<Edge> localEdges;
    vector<Edge> res;

    for (Triangle &trian : triangles)
    {
        // cout << "FUCK" << endl;
        localEdges.push_back(trian.e0);
        localEdges.push_back(trian.e1);
        localEdges.push_back(trian.e2);
    }
    // cout << localEdges.size() << endl;
    bitset<10000> btm;
    for (int i = 0; i < localEdges.size(); i++)
    {

        Edge edgeA = localEdges[i];
        for (int j = 0; j < localEdges.size(); j++)
        {
            Edge edgeB = localEdges[j];

            if (i == j)
            {
                continue;
            }
            if (edgeA.slope() == edgeB.slope())
            {
                if ((edgeA.p0 == edgeB.p0 || edgeA.p0 == edgeB.p1) && (edgeA.p1 == edgeB.p0 || edgeA.p1 == edgeB.p1))
                {
                    btm.set(i);
                } // found a duplicate
            }
        }
    }
    for (int a = 0; a < localEdges.size(); a++)
    {
        if (!btm.test(a))
        {
            res.push_back(localEdges[a]);
        }
    }
    return res;
}

struct Controller
{

    vector<Point> points;
    vector<Edge> edges;
    vector<Triangle> triangles;
    vector<vPoint> superPoints;
    Controller() {}
    Controller(vector<Point> p_, vector<Edge> e_, vector<Triangle> t_, vector<vPoint> vp)
    {
        points = p_;
        edges = e_;
        triangles = t_;
        superPoints = vp;
    }
    void initSuperTriangle()
    {

        double d = 1000;
        vPoint p0 = vPoint(330, -d, 0);
        vPoint p1 = vPoint(-d, 548, 0);
        vPoint p2 = vPoint(660 + d, 548, 0);
        this->superPoints.push_back(p0);
        this->superPoints.push_back(p1);
        this->superPoints.push_back(p2);

        Edge e0 = Edge(Point(p0.x, p0.y), Point(p1.x, p1.y));
        Edge e1 = Edge(Point(p1.x, p1.y), Point(p2.x, p2.y));
        Edge e2 = Edge(Point(p2.x, p2.y), Point(p0.x, p0.y));

        Triangle superTriangle = Triangle(e0, e1, e2);
        this->triangles.push_back(superTriangle);
    }
    void triangulate(Point point)
    {
        bitset<1000> btm;
        // this->points.push_back(point);
        vector<Triangle> triangleBuffer;
        // cout << "Hsas" << this->triangles.size() << endl;
        if (this->triangles.size() > 0)
        {
            cout << "ANS :" << this->triangles.size() << endl;
            for (int i = 0; i < this->triangles.size(); i++)
            {
                if (this->triangles[i].contains(point))
                {
                    triangleBuffer.push_back(this->triangles[i]);
                    btm.set(i);
                }
            }
        }
        vector<Triangle> new_triangles;
        for (int i = 0; i < this->triangles.size(); i++)
        {
            if (!btm.test(i))
            {
                new_triangles.push_back(this->triangles[i]);
            }
        }
        this->triangles = new_triangles;

        vector<Edge> edgeBuffer = getOutSizeEdges(triangleBuffer);
        for (int i = 0; i < edgeBuffer.size(); i++)
        {
            Edge e0 = Edge(edgeBuffer[i].p0, edgeBuffer[i].p1);
            Edge e1 = Edge(point, e0.p0);
            Edge e2 = Edge(point, e0.p1);
            this->triangles.push_back(Triangle(e0, e1, e2));
        }
        // getOutsideEdges
    }

    void removeSuper()
    {
        // constexpr int len = this->triangles.size();
        bitset<1000> btm;
        for (int i = 0; i < this->triangles.size(); i++)
        {
            bool found = false;
            for (size_t j = 0; j < this->triangles[i].getEdges().size(); j++)
            {
                vector<Point> edgePoints = this->triangles[i].getEdges()[j].getPoints();
                for (size_t k = 0; k < edgePoints.size(); k++)
                {
                    for (size_t l = 0; l < this->superPoints.size(); l++)
                    {
                        if (this->superPoints[l].x == edgePoints[k].x && this->superPoints[l].y == edgePoints[k].y)
                        {
                            // toDelete.push(i);
                            btm.set(i);
                            found = true;
                            break;
                        }
                        if (found)
                        {
                            break;
                        }
                    }
                    if (found)
                    {
                        break;
                    }
                }
                if (found)
                {
                    break;
                }
            }
        }
        vector<Triangle> res;
        for (int i = 0; i < this->triangles.size(); i++)
        {
            if (!btm.test(i))
            {
                res.push_back(this->triangles[i]);
            }
        }
        this->triangles = res;
    }
};

// TODO: 写一个输出函数 controller里面写就可以
int main()
{
    Controller st;
    st.initSuperTriangle();
    string data_path = fs::current_path();
    data_path.append("/example.csv");

    vector<vector<string> > csv_contents = read_csv_without_head(data_path);
    vector<Point> points;
    unordered_set<pair<double, double>, pair_hash<double, double> > set;
    for (auto &content : csv_contents)
    {
        // cout << "D" << endl;
        pair<double, double> tmp = make_pair(stod(content[0]), stod(content[1]));
        if (set.empty())
        {
            set.emplace(tmp);
            st.points.push_back(Point(tmp.first, tmp.second));
            continue;
        }
        if (set.find(tmp) == set.end())
        {
            Point t = Point(tmp.first, tmp.second);
            st.points.push_back(t);
            set.emplace(tmp);
        }
    }
    for (auto &t : st.points)
    {
        st.triangulate(t);
        // cout <
    }

    st.removeSuper();
    cout << st.triangles.size() << endl;
    // cout << ans.size() << endl;
    // ofstream myfile;
    // myfile.open("/Users/apple/Sites/jstest/AEDA/5thtest.csv");
    // for (auto &t : st.triangles)
    // {
    //     myfile << t.e0.p0.x << "," << t.e0.p0.y << "," << t.e0.p1.x << "," << t.e0.p1.y << "\n";
    //     myfile << t.e2.p0.x << "," << t.e2.p0.y << "," << t.e2.p1.x << "," << t.e2.p1.y << "\n";
    //     myfile << t.e1.p0.x << "," << t.e1.p0.y << "," << t.e1.p1.x << "," << t.e1.p1.y << "\n";
    // }
    // myfile.close();
    // for (auto &t : st.edges)
    // {
    //     cout << t.p0 << endl;
    //     cout << " Second" << endl;
    //     cout << t.p1 << endl;
    // }
    // for (auto &t : occupied_Points)
    // {
    //     ans.push_back(Point4Out(t, "port"));
    // }
    // cout << ans.size() << endl;
    // output_ans(ans);
}
