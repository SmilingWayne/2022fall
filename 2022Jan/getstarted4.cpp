#include <bits/stdc++.h>

// 重载运算符?
std::ostream &operator<<(std::ostream &os, std::pair<int, int> &p)
{
    return os << "(" << p.first << ", " << p.second << ")"
              << "\n";
}

// // 不知道这啥情况...
namespace Utility
{
    void testPair()
    {
        std::pair<int, int> p1;
        std::cout << p1 << "\n";
        p1 = std::make_pair(1, 2);

        std::pair<int, int> p2;
    }

    void testTuple()
    {
        std::tuple<int, int, int> t{1, 2, 1212};
        auto [x, y, z] = t;
        std::cout << z << "\n";
    }

    void testInitializerList()
    {
        std::initializer_list<int> l{1, 2, 3, 4};
        std::cout << std.max();
        int a, b, c;
        std::tie(a, b, c) = std::make_tuple(-1, 2, 3);
    }
};
int main()
{
    // Utilily::testPair();
    // Utility::testTuple();
}