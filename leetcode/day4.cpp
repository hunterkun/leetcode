//双索引技术 Two Pointer
// 滑动窗口

/*
209 Minimum Size Subarray Sum (Med)
Given an array of n positive integers and a positive integer s,
find the minimal length of a contiguous subarray of which the sum ≥ s. 
If there isn't one, return 0 instead.
给定一个整型数组和一个数字s,找到数组中最短的一个连续子数组，使得连续子数组
的数字和sum>=s,返回这个最短的连续子数组的长度值，没有解怎么办？返回0
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;

//基本思路：使用两个指针一头一尾，表示滑动窗口，如果大于等于sum了，则将
//左边界往前移动一格。如果小于s，说明右边界还要往前移动。注意当右边界到底时，
//这时需要不停的移动左边界，即使和小于s.

int minSubArrayLen(int s, vector<int> &nums)
{
    int l = 0, r = -1; //nums[l...r]为滑动窗口
    int res = nums.size() + 1;
    int sum = 0;
    while (l < nums.size())
    {
        if (sum < s && r + 1 < nums.size())
        {
            sum += nums[++r];
        }
        else
        {
            sum -= nums[l++];
        }
        if (sum >= s)
            res = min(res, r - l + 1);
    }
    if (res == nums.size() + 1)
        return 0;
    return res;
}

//暴力解法
int minSubArrayLen(int s, vector<int> &nums)
{
    int res = nums.size() + 1;
    for (int i = 0; i < nums.size(); i++)
        for (int j = i; j < nums.size(); j++)
        {
            int sum = 0;
            for (int k = i; k <= j; k++)
                sum += nums[k];
            if (sum >= s)
                res = min(res, j - i + 1);
        }
    if (res == nums.size() + 1)
        return 0;
    return res;
}
//部分和数组优化暴力解法
int minSubArrayLen(int s, vector<int> &nums)
{
    int res = nums.size() + 1;
    vector<int> psum(nums.size() + 1, 0);
    //求出部分和数组
    for (int i = 1; i <= nums.size(); i++)
        psum[i] = psum[i - 1] + nums[i - 1];
    for (int i = 0; i < nums.size(); i++)
        for (int j = i; j < nums.size(); j++)
        {
            int sum = psum[j + 1] - psum[i]; //原数组nums[i...j]的和等于部分和数组psum[j+1]-psum[i]
            if (sum >= s)
                res = min(res, j - i + 1);
        }
    if (res == nums.size() + 1)
        return 0;
    return res;
}
//使用部分和数组的有序性，遍历原数组，每次都取一个数作为左边界，
//利用lower_bound去找到滑动窗口内和>=s的右边界,而不是上面一步步求。
int minSubArrayLen(int s, vector<int> &nums)
{
    int res = nums.size() + 1;
    vector<int> psum(nums.size() + 1, 0);
    for (int i = 1; i < nums.size(); i++)
    {
        psum[i] = psum[i - 1] + nums[i - 1];
    }
    for (int l = 0; l < nums.size() - 1; l++)
    {
        auto rbound = lower_bound(psum.begin(), psum.end(), s + psum[l]);
        if (rbound != psum.end())
        {
            int r = rbound - psum.begin();
            res = min(res, r - l);
        }
    }
}
/*3 Longest Substring without repeating characters
Given a string, find the length of the longest substring 
without repeating characters.
*/
int lengthOfLongestSubstring(string s)
{
    int res = 0;
    int i = 0, j = -1;
    int freq[256] = {0};
    while (i < s.size())
    {
        if (freq[s[j + 1]] == 0 && j + 1 < s.size())
        {
            freq[s[++j]]++;
        }
        else
        {
            freq[s[i++]]--;
        }
        res = max((j - i + 1), res);
    }
    return res;
}

//438.Given a string s and a non-empty string p,
//find all the start indices of p's anagrams in s.
//Strings consists of lowercase English letters only and
//the length of both strings s and p will not be larger than 20100.

bool isAnagram(string s, string t)
{
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    return s == t;
}

vector<int> findAnagrams(string s, string p)
{
    vector<int> res;
    for (int i = 0; i + p.size() < s.size(); i++)
    {
        string ss(s.begin() + i, s.begin() + i + p.size());
        if (isAnagram(p, ss))
            res.push_back(i);
    }
    return res;
}