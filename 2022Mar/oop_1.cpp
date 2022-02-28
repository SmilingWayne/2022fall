#include <iostream>

#include <vector>
using namespace std;
int main()
{
    int a = 10;
    printf("输入数字：\n");
    scanf("%d", &a);
    vector<int> temp;
    for (int i = 0; i < a; ++i)
    {
        temp.push_back(i);
        cout << temp[temp.size() - 1]
             << endl;
    }
    return 0;
}