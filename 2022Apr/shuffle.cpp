#include <iostream>
#include <vector>
using namespace std;
#define N 10
#define M 30

// 第一种洗牌算法：生成一个新的vector存储结果，每次都把随机到的结果放进去
// 需要新空间
void Fisher_Yates_Shuffle(vector<int> &arr, vector<int> &res)
{
    srand((unsigned)time(NULL));
    int k;
    for (int i = 0; i < M; ++i)
    {
        k = rand() % arr.size();
        res.push_back(arr[k]);
        arr.erase(arr.begin() + k);
    }
}

/**
 * 算法思路：需要反着来，一个有顺序的数组，直接从最后一个开始，随机地把数字放到前面的数据中去。
 * FIXME:缺点：需要知道数组总长度，无法处理动态增减的情况
 * */
void Knuth_Durstenfeld_Shuffle(vector<int> &arr)
{
    for (int i = arr.size() - 1; i >= 0; --i)
    {
        srand((unsigned)time(NULL));
        swap(arr[rand() % (i + 1)], arr[i]);
    }
}

/**
 * 支持动态增加的数组进行shuffle
 * 同时原数组还能保持不变
 * O(n)的空间复杂度和O(n)的时间复杂度
 * */
void Inside_Out_Shuffle(const vector<int> &arr, vector<int> &res)
{
    res.assign(arr.size(), 0);
    copy(arr.begin(), arr.end(), res.begin());
    int k;
    for (int i = 0; i < arr.size(); ++i)
    {
        srand((unsigned)time(NULL));
        k = rand() % (i + 1);
        res[i] = res[k];
        res[k] = arr[i];
    }
    printf("\n\n");
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
}

/**
 * 蓄水池抽样：在不知道样本容量的情况下
 * 等概率地从数据流或者队列中抽取1或k个元素
 * */
void Reservoir_Sampling(vector<int> &arr)
{
    int k;
    for (int i = M; i < arr.size(); ++i)
    {
        srand((unsigned)time(NULL));
        k = rand() % (i + 1);
        if (k < M)
        {
            swap(arr[k], arr[i]);
        }
    }

    // 这里返回的可以就是arr的前M个数字
}

/**
 * TODO: 写几个洗牌算法
 * */
int main()
{
    vector<int> arr(100, 0);
    for (int i = 0; i < 100; i++)
    {
        arr[i] = i + 1;
    }
    vector<int> ans;
    Knuth_Durstenfeld_Shuffle(arr);
    for (int i = 0; i < 100; i++)
    {
        cout << arr[i] << " ";
    }

    Inside_Out_Shuffle(arr, ans);
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    printf("\n\n");

    printf("\n\n");

    Reservoir_Sampling(ans);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
}
