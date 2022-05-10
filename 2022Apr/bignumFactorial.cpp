#include <iostream>
#include <vector>
#include <string>

#define ll long long

using namespace std;
const int N = 2022;  // n!
const int K = 10000; // Factorial_3 中存放的最大长度

/**
 * 在数据规模较大的时候比较快
 * */
void Factorial_3()
{
    int temp[K] = {0};
    temp[0] = 1;
    int n = N;       //阶乘数
    int dig = K - 1; //结果位数
    for (int k = 1; k <= n; k++)
    {
        for (int i = 0; i < dig; i++)
            temp[i] = temp[i] * k;

        for (int j = 0; j < dig; j++) //进位循环
        {
            temp[j + 1] += temp[j] / 10;
            temp[j] = temp[j] % 10;
        }
    }
    int total = 0;
    bool flag = false;
    for (int i = dig; i >= 0; i--)
        if (temp[i] != 0 || flag)
        {
            cout << temp[i];
            total++;
            flag = true;
        }
    cout << endl;
}

vector<int> trans_Int2_Vec(int &a)
{
    vector<int> ans;
    int t = a;
    while (t > 0)
    {
        ans.push_back(t % 10);
        t /= 10;
    }
    return ans;
}

/**
 * 可以存放任意长度的内容
 * */
void Factorial_2(vector<int> &ans, int a)
{
    if (a == N + 1)
    {
        reverse(ans.begin(), ans.end());
        for (auto &x : ans)
        {
            cout << x;
        }
        return;
    }
    vector<int> a_vec = trans_Int2_Vec(a);
    vector<int> t(ans.size() + a_vec.size(), 0);
    for (int i = 0; i < a_vec.size(); i++)
    {
        for (int j = 0; j < ans.size(); j++)
        {
            int cur = (t[i + j] + ans[j] * a_vec[i]);
            t[i + j] = cur % 10;
            if (i + j + 1 >= t.size())
                t.push_back(0);
            t[i + j + 1] += (cur / 10);
        }
    }
    while (t.back() == 0)
    {
        t.pop_back();
    }
    Factorial_2(t, a + 1);
}

ll factorial_1(ll a)
{
    if (a == 1)
    {
        return 1;
    }
    return a * factorial_1(a - 1);
}

/**
 * C++ long long 最长表示到2^63 - 1
 * 最多只能表示成19的阶乘
 * 只能用字符串进行操作
 * */
int main()
{
    clock_t startTime, endTime;
    startTime = clock();
    Factorial_3();
    endTime = clock();
    cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    startTime = clock();
    vector<int> ans = {1};
    Factorial_2(ans, 1);
    endTime = clock();
    cout << "\nThe run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
}