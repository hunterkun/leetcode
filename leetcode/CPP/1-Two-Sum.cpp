#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

/*1 Two Sum
*/
//基本思路：存储值和相应的索引，边遍历边查找
vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> record;
    for (int i = 0; i < nums.size(); i++)
        if (record.find(target - nums[i]) == record.end())
            record[nums[i]] = i;
        else
        {
            int res[2] = {i, record[nums[i]]};
            return vector<int>(res, res + 2);
        }
    throw invalid_argument('the input has no solution');
}

/*15. 3Sum 
Given an array nums of n integers, are there elements a, b, c in nums such
that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
*/
//基本思路：由于要找到所有独特的组合，不能有重复，所以首先想到剔除重复元素，同时用map统计值和频次
//然后双指针一前一后遍历数组。注意要单独讨论重复的情况。同时三个元素重复的话只能全为0.
vector<vector<int>> threeSum(vector<int> &nums)
{
    unordered_map<int, int> counter;
    for (int i = 0; i < nums.size(); i++)
        counter[nums[i]]++;
    vector<vector<int>> res;
    //单独讨论全为0的情况
    if (counter[0] >= 3)
        res.push_back({0, 0, 0});
    //剔除vector重复元素，固定操作
    sort(nums.begin(), nums.end());
    auto iter = unique(nums.begin(), nums.end());
    nums.erase(iter, nums.end());
    //一前一后遍历
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = i + 1; j < nums.size(); j++)
        {
            //单独讨论如果答案有两个元素重复的情况
            if (nums[i] * 2 + nums[j] == 0 && counter[nums[i]] >= 2)
                res.push_back({nums[i], nums[i], nums[j]});

            if (nums[j] * 2 + nums[i] == 0 && counter[nums[j]] >= 2)
                res.push_back({nums[i], nums[j], nums[j]});
            //保证存在-nums[i]-nums[j],且在双指针的右边
            int c = -nums[i] - nums[j];
            if (counter[c] > 0 && nums[j] < c)
                res.push_back({nums[i], nums[j], c});
        }
    }
    return res;
}