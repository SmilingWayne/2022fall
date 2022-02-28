// #include <bits/stdc++.h>
#include <array>

#include <iostream>
#include <vector>
#include <queue>
#include <list>

namespace Sequence
{
    void testArray()
    {
        std::array<int, 10> arr = {1, 4, 5, 2, 7, 3};
        auto out = [&arr]()
        {
            std::cout << '[';
            for (auto i : arr)
            {
                std::cout << i << ' ';
            }
            std::cout << ']' << '\n';
        };
        // auto out = [&arr]()
        // {
        //     std::cout << '[';
        //     for (int i = 0; i < (int)(arr.size()); i++)
        //     {
        //         std::cout << arr[i] << ' ';
        //     }
        //     std::cout << ']' << '\n';
        // };
        out();
        std::sort(arr.begin(), arr.end());
        out();
        std::sort(arr.rbegin(), arr.rend());
        out();

        arr.front() = -2;
        arr.back() = 114514;
        std::cout << arr.at(2) << std::endl;
        out();
    }

    void vectorTest()
    {
        std::vector<int> a(10, -1);
        for (int i = 0; i < 10; i++)
        {
            std::cout << a.size() << " " << a.capacity() << '\n';
            a.push_back(i + 3);
            a[i] = i % 5;
        }

        auto out = [&a]()
        {
            std::cout << '[';
            for (int i = 0; i < (int)(a.size() - 1); ++i)
            {
                std::cout << a[i] << ", ";
            }

            std::cout << a[a.size() - 1] << ']' << '\n';
        };

        out();
        // 在begin的位置插入
        a.insert(a.begin() + 3, {502, 333}), out();
        std::swap(a[2], a[4]);
        out();

        a.erase(std::find(a.begin(), a.end(), 10), a.end());
        // 找到第一个10，并删除到末尾的所有元素
        // std::iota(a.begin(), a.end(), 2);
        out();
    }

    void testString()
    {
        std::string a(20, '*');

        auto out = [&a]()
        {
            std::cout << "`" << a << "`" << std::endl;
        };
        out();

        a.append("+++");
        out();

        a = a.substr(1, (int)(a.size() - 2));
        out();
        for (char c : a)
        {
            // 获取每个字符的具体i内容给你
            // char c = a[i];
            printf("%c ", c);
        }
        std::cout << "\n";

        std::vector<std::string> temp(10, "hello");
        for (auto a : temp)
        {
            std::cout << a << " world!" << '\n';
        }
    }

}

void print_list_content(std::list<int> &a)
{
    for (auto t : a)
    {
        std::cout << t << " ";
    }
}
int main()
{
    // Sequence::testArray();
    // Sequence::vectorTest();
    // Sequence::testString();
    std::queue<int> a;
    for (int i = 0; i < 10; i++)
    {
        a.push(i);
    }
    std::queue<int> b = a;
    printf("%lu ", b.size());

    std::list<int> ans;
    for (int i = 0; i < 10; i++)
    {
        if (i % 2 == 1)
        {
            ans.push_front(i);
        }
        else
        {
            ans.push_back(i - 10);
        }
    }
    print_list_content(ans);
}