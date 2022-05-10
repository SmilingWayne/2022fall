#include <iostream>
#include <bitset>
using namespace std;
int main()
{
    bitset<20> a;
    bitset<20> b;

    a.set(2);
    cout << a << endl;
    for (int i = 0; i < 20; i++)
    {
        if (!a.test(i))
        {
            cout << i << endl;
        }
    }
    // bitset<20> c("10011");
    // bitset<20> d("10111");
    // cout << (c ^ d) << endl;
    // for (size_t i = 10; i < a.size(); i++)
    // {
    //     a.set(i);
    //     if (i % 2 == 1)
    //     {
    //         b.set(i);
    //     }
    // }

    // cout << a << endl;
    // a.reset(0);

    // cout << (a ^ b) << endl;
}