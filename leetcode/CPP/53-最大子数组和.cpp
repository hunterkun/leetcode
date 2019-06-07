#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
53.最大子数组和
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和
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
int MaxSum2(vector<int> &nums, int l, int r)
{
    int mid = l + (r - l) / 2;
    if (r - l == 1) //递归的退出条件，当只有1个数的时候
        return nums[l];

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

/*3.只考虑数组的第一个元素以及剩下的一段数组。则结果只能有3种情况
1.最大值为左边元素（待考虑）
2.最大值为左边元素+剩下的数组
3.最大值为剩下的数组
先从最右边遍历原数组，存储答案。需要tmp数组的配合
*/
int MaxSum3(vector<int> &nums)
{
    int n = nums.size();
    vector<int> ans(n);
    vector<int> tmp(n);
    int tmpp = nums[n - 1], anss = nums[n - 1];
    ans[n - 1] = nums[n - 1];
    tmp[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        // tmp[i] = max(tmp[i + 1] + nums[i], nums[i]);
        // ans[i] = max(ans[i + 1], tmp[i]);
        // 不用数组也行
        // tmpp = max(tmpp + nums[i], nums[i]);
        // anss = max(tmpp, anss);
        // 等价写法
        if (tmpp < 0)
            tmpp = 0;
        tmpp += nums[i];
        if (anss < tmpp)
            anss = tmpp;
    }
    return anss;
}

int main()
{
    int target = 3;
    vector<int> nums{1, 5, 3, 2};
    int ans = MaxSum2(nums, 0, nums.size());
    cout << ans << endl;
    return 0;
}
