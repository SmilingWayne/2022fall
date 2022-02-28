#include <bits/stdc++.h>

// 这里主要写的是模版类

class single
{
public:
    int val;
};

// 仿函数？
template <class T>
struct Func
{
    void operator()(T val)
    {
        std::cout << val << std::endl;
    }
};

template <class T>
struct Single
{

    T val;

    Single(T _val)
    {
        this->val = _val;
    }
    // 初始化
    void sayVal()
    {
        std::cout << val << std::endl;
    }
};
int main()
{

    int a[20];
    for (int i = 0; i < 20; i++)
    {
        a[i] = rand() % 100 + 2;
    }

    // LAMBDA 表达式
    std::sort(a, a + 20, [](int a, int b)
              { return a > b; });
    for (int i = 0; i < 20; i++)
    {
        std::cout << a[i] << std::endl;
    }

    single s;
    s.val = 10;
    Single<int64_t> s2(20);
    // s2.val = 10;
    s2.sayVal();
    // std::cout << s.val << std::endl;
}