#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
string multiply_2(string a, string b)
{
    string result = "";
    int row = b.size();
    int col = a.size() + 1;
    int tmp[row][col];
    memset(tmp, 0, sizeof(int) * row * col);
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < a.size(); j++)
        {
            string a_number = a.substr(j, 1);
            string b_number = b.substr(i, 1);
            tmp[i][j] += (stoi(a_number) * stoi(b_number));
            tmp[i][j + 1] = (tmp[i][j] / 10);
            tmp[i][j] %= 10;
        }
    }
    int n = a.size() + b.size();
    int ans[n];
    memset(ans, 0, sizeof(int) * n);
    for (int r = 0; r < n; r++)
    {
        int i = 0;
        int j = r;
        while (i <= r && j >= 0)
        {
            if (i < row && j < col)
            {
                ans[r] += tmp[i][j];
            }
            i++;
            j--;
        }
        if (r + 1 < n)
        {
            ans[r + 1] = ans[r] / 10;
            ans[r] %= 10;
        }
    }
    bool isZero = true;
    for (int i = n - 1; i >= 0; i--)
    {
        if (ans[i] == 0 && isZero)
        {
            continue;
        }
        isZero = false;
        result.append(to_string(ans[i]));
    }
    return result;
}

string add(string a, string b)
{
    int N = max(a.size(), b.size());
    int sum[N];
    memset(sum, 0, sizeof(int) * N);

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    for (int i = 0; i < N; i++)
    {
        int bit_a = 0;
        int bit_b = 0;
        if (i < a.size())
            bit_a = stoi(string(1, a.at(i)));
        if (i < b.size())
            bit_b = stoi(string(1, b.at(i)));

        sum[i] += (bit_a + bit_b);

        if (i < N - 1 && sum[i] > 9)
        {
            sum[i + 1] = sum[i] / 10;
            sum[i] %= 10;
        }
    }
    string result = "";
    bool zeroStartFlag = true;
    for (int i = N - 1; i >= 0; i--)
    {
        if (sum[i] == 0 && zeroStartFlag)
        {
            continue;
        }

        zeroStartFlag = false;
        result.append(to_string(sum[i]));
    }

    return result;
}

string divideAndConquer(string a, string b)
{
    if (a.size() < 2 && b.size() < 2)
    {
        return to_string(stoi(a) * stoi(b));
    }

    int n = a.size();
    int m = b.size();

    int halfN = n / 2;
    int halfM = m / 2;

    string a0 = "0";
    string a1 = "0";
    if (a.size() > halfN && halfN > 0)
    {
        a1 = a.substr(0, halfN);
        a0 = a.substr(halfN, a.size() - halfN);
    }
    else
    {
        a1 = "0";
        a0 = a;
    }

    string b0 = "0";
    string b1 = "0";
    if (b.size() > halfM && halfM > 0)
    {
        b1 = b.substr(0, halfM);
        b0 = b.substr(halfM, b.size() - halfM);
    }
    else
    {
        b1 = "0";
        b0 = b;
    }

    string a1b1 = divideAndConquer(a1, b1);
    string a0b0 = divideAndConquer(a0, b0);
    string a1b0 = divideAndConquer(a1, b0);
    string a0b1 = divideAndConquer(a0, b1);

    a1b1.append((n - halfN) + (m - halfM), '0');
    a1b0.append(n - halfN, '0');
    a0b1.append(m - halfM, '0');

    string result = "";
    result = add(a1b1, a1b0);
    result = add(result, a0b1);
    result = add(result, a0b0);
    return result;
}

int main()
{
    string a = "1234";
    string b = "5678";
    string result = multiply_2(a, b);
    cout << "Multiply: \n"
         << "\t" << a << " * " << b << " = \n"
         << result << endl;
    string result2 = divideAndConquer(a, b);
    cout << "Divide And Conquer: \n"
         << "\t" << a << " * " << b << " = \n"
         << result2 << endl;
    a = "123456789025389576378298736743982127346587";
    b = "1098738179234658982456743234567432";
    result = multiply_2(a, b);
    cout << "Multiply: \n"
         << "\t" << a << " * " << b << " = \n"
         << result << endl;
    result2 = divideAndConquer(a, b);
    cout << "Divide And Conquer: \n"
         << "\t" << a << " * " << b << " = \n"
         << result2 << endl;
    return 0;
}
