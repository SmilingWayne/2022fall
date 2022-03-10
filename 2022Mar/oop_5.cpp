#include <iostream>
#include <set>

using namespace std;
class new_set
{

    friend new_set operator&(const new_set &a, const new_set &b);

private:
    set<int> content;

public:
    new_set()
    {
        content.insert(0);
        content.empty();
    }
    new_set(const set<int> &n)
    {
        content = n;
    }
    void output()
    {
        for (auto i : content)
        {
            cout << i << ".." << endl;
        }
    }
};
/**
 * 用public方式进行定义
 * */
class new_new_set : public new_set
{
    int z;

public:
    new_new_set() { z = 0; }
    new_new_set(int a) { z = a; };
    new_new_set(const set<int> &d, int a) : new_set(d)
    {
        z = a;
    }
    void sayHello()
    {
        cout << z << endl;
    }
};

new_set operator&(const new_set &a, const new_set &b)
{
    set<int> c;
    for (auto i : a.content)
    {
        if (b.content.find(i) != b.content.end())
        {
            c.insert(i);
        }
    }
    return set<int>(c);
}
int main()
{
    set<int> a;
    for (int i = 0; i < 10; i++)
    {
        a.insert(i);
    }
    new_set a_(a);
    a.clear();
    for (int i = 5; i < 15; i++)
    {
        a.insert(i);
    }
    new_set b_(a);
    new_set c_ = a_ & b_;
    c_.output();
}