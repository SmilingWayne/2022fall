#include <iostream>
#include <vector>

using namespace std;
// 利用rand(7)实现rand(10)
// 如何进行一些经典的推广？
// 用rand(7) 实现rand(100)?

/**
 *  一个定理：如果rand(n) 可以生成1～n的整数
 * 那么(rand(n) - 1 )* n + rand(n) 可以随机均匀生成1～n*n的整数
 * 可以在这里找适合的范围进行缩小区间，例如：10就可以约束到1-40，11就可以约束到1-44这样（1，12，34 就选1； 2，14，26，38，就选2
 *
 * */

int rand7()
{
    return rand() % 7 + 1;
}

int rand11()
{
    int first = 0, second = 0;
    while (true)
    {
        while ((first = rand7()) > 6)
        {
            first = rand7();
        }
        while ((second = rand7()) > 6)
        {
            second = rand7();
        }
        second = (first & 1) == 1 ? second : second + 6;
        if (second < 12)
        {
            return second;
        }
    }
}

int rand11_2()
{
    while (true)
    {
        int ans = (rand7() - 1) * 7 + rand7() - 1;
        if (ans >= 1 && ans <= 44)
        {
            return ans % 11 + 1;
        }
    }
}

int main()
{

    // 按照当前时间给出随机数种子
    // printf("%d", rand7());
    vector<int> t(11, 0);
    for (int i = 0; i < 1000000; i++)
    {
        t[rand11_2() - 1] += 1;
        // printf("%d", t[0]);
    }
    for (int i = 0; i < 11; i++)
    {
        cout << (i + 1) << " " << t[i] << "\n";
    }
}