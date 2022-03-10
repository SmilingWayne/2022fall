#include <iostream>
using namespace std;
//递归算法解决八皇后问题。总共有92种解法。

int c[20];
const int N = 9;
int cnt = 0;

void print()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == c[i])
            {
                cout << "1 ";
            }
            else
            {
                cout << "0 ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void search(int r)
{
    if (r == N)
    {
        cnt++;
        print();
        return;
    }
    for (int i = 0; i < N; i++)
    {
        c[r] = i;
        bool ok = true;
        for (int j = 0; j < r; j++)
        {
            if (c[r] == c[j] || c[r] - c[j] == r - j || c[r] - c[j] == j - r)
            {
                ok = false;
                break;
            }
        }
        if (ok == true)
        {
            search(r + 1);
        }
    }
}

int main()
{
    search(0);
    cout << cnt << endl;
    return 0;
}