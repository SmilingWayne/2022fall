#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <algorithm>

struct Grade
{
    std::string name;
    int grade;
};

int main()
{
    std::vector<int> a;
    std::set<int> c;
    std::set<int> d;
    for (int i = 0; i < 10; i++)
    {
        a.push_back(rand() % 10 + 1);
    }
    for (int i = 0; i < a.size(); i++)
    {
        printf("%d ", a[i]);
    }
    std::cout << '\n'
              << std::endl;
    printf("%d", accumulate(a.begin(), a.end(), 0));
    // 求和函数

    for (int i = 0; i < 10; i++)
    {
        c.insert((i + 5) % 6);
        d.insert((i + 7) % 6);
    }
    std::vector<int> dest;
    std::vector<int> test;
    for (int i = 0; i < 10; i++)
    {
        test.push_back(i);
    }
    std::set_intersection(c.begin(), c.end(), d.begin(), d.end(), test.begin());
    std::set_intersection(c.begin(), c.end(), d.begin(), d.end(), std::insert_iterator<std::vector<int> >(dest, dest.begin()));
    for (auto i : test)
    {
        printf("%d\n", i);
    }
    // std::vector<int
    dest.clear();
    std::copy(c.begin(), c.end(), dest.begin());
    for (auto i : dest)
    {
        printf("\n%d ", i);
    }
    // accumulate(a.begin(), a.end(), 0, [](int a, Grade b)
    //            { return a + b.grade });
    // std::set<std::string> temp;
    // for (int i = 0; i < 10; i++)
    // {
    //     temp.insert("a");
    // }
    // for (auto i : temp)
    // {
    //     printf("%s\n", i.c_str());
    // }

    // std::set<std::string> temp;
    // for (char ch = 'a'; ch < 'z'; ch++)
    // {
    //     temp.insert(ch);
    // }
    // for (std::string i : temp)
    // {
    //     printf("%s\n", i);
    // }
}