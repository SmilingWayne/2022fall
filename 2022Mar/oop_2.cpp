#include <iostream>
using namespace std;
class A; //这里的类A必须先声明一下，否则后面在B类的print_a函数中会报错。ps：虽然这样写VS也会提示使用未曾定义的类A，但是可以正常通过编译。
class B
{
public:
    int b;
    void print_a(const A x); //此处不可对函数体进行定义！              <---这里还有注释↓
};
class A
{
public:
    int a;
    friend void B::print_a(const A x); //在此处声明为类A的友元函数，致此，此函数才有访问类A内成员的权限
    A(int x)
    {
        this->a = x;
    }
};
void B::print_a(const A x)
{
    cout << "This is in a " << x.a << endl;
}

int main()
{
    A x(3);
    B y;
    y.print_a(x);
    return 0;
}
