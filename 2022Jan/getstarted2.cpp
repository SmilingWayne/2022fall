#include <bits/stdc++.h>

int main()
{

    // 实现简单的排序 + 去重的功能
    int a[] = {1, 2, 3, 4, 5, 5, 5, 2, 2, 3, 43, 43, 5, 6, 2, 33, 2};
    int n = sizeof(a) / sizeof(*a);

    int up_bd = std::upper_bound(a, a + n, 6) - a; // 找到第一个大于三的下
    std::cout << up_bd << std::endl;
    std::sort(a, a + n);
    int aft_len = std::unique(a, a + n) - a;
    for (int i = 0; i < aft_len; i++)
    {
        printf("%d ", a[i]);
    }
    std::cout << '\n'
              << std::endl;
    for (int i = 0; i < aft_len; i++)
    {
        printf("%d ", a[i]);
    }

    // 返回一个二分查找的内容
    bool ok = std::binary_search(a, a + aft_len, 4);
    std::cout << (ok ? "Yes" : "No") << std::endl;

    return 0;
}