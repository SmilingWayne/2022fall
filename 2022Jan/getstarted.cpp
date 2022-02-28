
#include <bits/stdc++.h>

struct node
{
    int a, b, c;
    //这就是所谓重载运算符?
    bool operator<(const node &target) const
    {
        return this->c > target.c;
    }
};
// using namespace std;

/**
 * a > b ,降序, a < b, 升序
 **/
bool cmp(int a, int b)
{
    return a > b;
}
/**
 * 按照绝对值进行排序
 * */
bool abs_cmp(int a, int b)
{
    return std::abs(a) > std::abs(b);
}

/**
 * 对于一个结构体进行排序
 * */
bool node_cmp(node a, node b)
{
    return a.c > b.c;
}

int main()
{
    int a, b;
    printf("输入两个数字:\n");
    scanf("%d %d", &a, &b);
    std::swap(a, b);
    std::cout << a << " " << b << std::endl;
    printf("输入数量:\n");
    scanf("%d", &a);
    int arr[a];
    node nodes[a];
    for (int i = 0; i < a; i++)
    {
        arr[i] = rand() % 100 - 50;
        nodes[i].c = arr[i];
        nodes[i].a = 0;
        nodes[i].b = 0;
    }
    std::sort(arr, arr + a, cmp); // 需要事先定义cmp

    std::reverse(arr, arr + a); // 直接倒过来

    // std::sort(nodes, nodes + a, node_cmp);

    printf("下面是排序和随机后的结果:\n");
    for (int i = 0; i < a; i++)
    {
        std::cout << nodes[i].c << std::endl;
    }
    // std::sort(arr, arr + a, std::greater<int>());
    // 内置的降序写法

    // std::sort(arr, arr + a, std::less<int>());
    // 内置的升序写法

    // printf("下面是排序和随机后的结果:\n");
    // for (int i = 0; i < a; i++)
    // {
    //     std::cout << arr[i] << std::endl;
    // }

    // std::sort(arr, arr + a, abs_cmp);
    // printf("下面是排序和随机后的结果:\n");
    // for (int i = 0; i < a; i++)
    // {
    //     std::cout << arr[i] << std::endl;
    // }

    return 0;
}
