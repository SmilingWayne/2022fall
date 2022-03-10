#include <iostream>

#include <vector>
#include <random>
#include <string>
using namespace std;

class Mayor
{

    string name;

public:
    Mayor();
    Mayor(string &a)
    {
        name = a;
    }
    string get_name()
    {
        return name;
    }

    bool operator==(Mayor &d)
    {
        return this->name == d.get_name();
    }
};

class Student
{
    Mayor mayor;
    string name;
    int ID;

public:
    Mayor get_mayor()
    {
        return mayor;
    }
};
class MatchMayor
{
    Mayor mayor;

public:
    MatchMayor(Mayor &m)
    {
        mayor = m;
    }

    bool operator()(Student &st)
    {
        return st.get_mayor() == mayor;
    }
};

bool judge(const int &a)
{
    return a > 30;
}
int main()
{
    vector<int> a(10, 0);
    for (int i = 0; i < a.size(); i++)
    {
        a[i] = rand() % 100;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << " ";
    }
    cout << accumulate(a.begin(), a.end(), 0) << endl;
    cout << count_if(a.begin(), a.end(), judge); // 统计有多少元素 满足judge这个要求
}