#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
using namespace std;

// 致命思考：如何重载++ 操作符?如何注意先后顺序？
/**
 * 重载操作符
 * */
class Complex
{
    // friend Complex operator++();
    friend Complex operator++(Complex &a);
    friend Complex operator+(const double &a, const Complex &b);
    friend Complex operator+(const Complex &a, const Complex &b);
    friend Complex operator+(const Complex &a, const double &b);
    friend Complex operator-(const Complex &a, const Complex &b);
    friend Complex operator*(const Complex &a, const Complex &b);
    friend bool operator==(const Complex &a, const Complex &b);

private:
    double real;
    double imag;

public:
    Complex(double a, double b)
    {
        real = a;
        imag = b;
    }
    void output()
    {
        cout << real << "+" << imag << "i\n";
    }
    Complex add(const Complex &x) const
    {
        Complex temp(0, 0);
        temp.real = real + x.real;
        temp.imag = imag + x.imag;
        return temp;
    }
    // 在类内对操作符进行重载
    // Complex operator+(const Complex &x) const
    // {
    //     Complex a(0, 0);
    //     a.real = real + x.real;
    //     a.imag = imag + x.imag;
    //     return a;
    // }
};

// 利用全局 + 友元进行操作符重载
Complex operator+(const Complex &a, const Complex &b)
{
    Complex t(0, 0);
    t.real = a.real + b.real;
    t.imag = a.imag + b.imag;
    return t;
}

Complex operator-(const Complex &a, const Complex &b)
{
    Complex t(0, 0);
    t.real = a.real - b.real;
    t.imag = a.imag - b.imag;
    return t;
}
Complex operator*(const Complex &a, const Complex &b)
{
    Complex t(0, 0);
    t.real = a.real * b.real - a.imag * b.imag;
    t.imag = a.imag * b.real + a.real * b.imag;
    return t;
}

/**
 * 实现了两种数据类型之间的直接转换
 * */
Complex operator+(const Complex &a, const double &b)
{
    Complex t(0, 0);
    t.real = a.real + b;
    t.imag = a.imag;
    return t;
}

Complex operator+(const double &a, const Complex &b)
{
    Complex t(0, 0);
    t.real = a + b.real;
    t.imag = b.imag;
    return t;
}

Complex operator++(Complex &a)
{
    // Complex ans(0, 0);
    a.real = a.real + 1;
    a.imag = a.imag;
    return a;
    // return ans;
}

bool operator==(const Complex &a, const Complex &b)

{
    return a.real == b.real && a.imag == b.imag;
}
class A
{
    int x;
    int y;
    string a;

public:
    A()
    {
    }
    A(string t)
    {
        a = t;
        x = 0;
        y = 0;
    }
    A(int a, int b, string c)
    {
        x = a;
        y = b;
        this->a = c;
    }
    A(A &t)
    {
        a = t.a;
        x = t.x;
        y = t.y;
    }

    void f()
    {
        cout << "OK!" << endl;
    }
    void g()
    {
        cout << "GOK!" << endl;
    }
};

// 如何实现智能指针从而计算一个函数被调用的次数

class B
{
    A *p_a;
    int count;

public:
    B(A *p)
    {
        p_a = p;
        count = 0;
    }
    A *operator->()
    {
        count++;
        return p_a;
    }
    int get_access_time()
    {
        return count;
    }
};
int main()
{
    Complex a(1.0, 2.0), b(2.4, 4.5);
    a.output();
    Complex c = a + b;
    Complex d = a * b;
    c.output();
    d.output();
    cout << (a == b) << endl;
    Complex e = 1.2 + a; // error 操作符重载必须注意先后顺序
    e.output();
    Complex f = ++a;
    f.output();
    // 拷贝构造函数和重载赋值操作符之间的关系和差别
    A test(1, 2, "hello");
    A test2 = test;
    A test3;
    // 实现了智能指针计算被调用的次数
    B b_test(&test3);
    b_test->f();
    b_test->g();
    cout << b_test.get_access_time() << endl;

    // 利用重载new delete 实现动态内存管理
    // 首先申请一个比较大的空间，然后将其进行小空间的分配，也就是分配成链表形式的空间，有效利用内存
}