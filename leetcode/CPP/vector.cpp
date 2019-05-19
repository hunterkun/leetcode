#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

/*
连续子数组的最大和
*/

//1.暴力解法
int MaxSum(vector<int> &nums)
{
    int best = -INT16_MIN;
    int sum;
    for (int i = 0; i < nums.size(); i++)
    {
        sum = 0;
        for (int j = i; j < nums.size(); j++)
        {
            sum += nums[j];
            if (sum > best)
                best = sum;
        }
    }
    return best;
}

/*2.分治递归解法：
将原数组分为长度相等的两段数组，分别求出两段数组各自的子数组最大和，则原数组的最大子数组
的和为以下三种情况的最大值：
1.原数组与第一半的答案相同
2.原数组与第二半的答案相同
3.原数组的最大子数组跨过中间的两个元素[n/2-1],[n/2]
前两种用递归求解，第三种需要遍历一次找到以[n/2-1]结尾和以[n/2]开头的子数组，相加即可
*/
int max3(int a, int b, int c)
{
    int m = a;
    if (b > m)
        m = b;
    if (c > m)
        m = c;
    return m;
}
int MaxSum2(vector<int> &nums, int l, int r)
{
    if (r - l == 1)
        return nums[l];
    int mid = l + (r - l) / 2;

    int sum1 = MaxSum2(nums, l, mid);
    int sum2 = MaxSum2(nums, mid, r);
    int tmp1 = 0, best1 = INT16_MIN;
    for (int i = mid - 1; i >= l; i--)
    {
        tmp1 += nums[i];
        if (tmp1 > best1)
            best1 = tmp1;
    }
    int tmp2 = 0, best2 = INT16_MIN;
    for (int i = mid; i < r; i++)
    {
        tmp2 += nums[i];
        if (tmp2 > best2)
            best2 = tmp2;
    }
    return max(max(sum1, sum2), best1 + best2);
}

int main()
{
    int target = 3;
    vector<int> nums{1, 5, 3, 2};
    string ss("  3abcdef3gh");
    auto pos = ss.find_first_not_of("10");
    cout << pos << endl;
    return 0;
}