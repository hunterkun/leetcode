//滑动窗口+查找表
#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_set>

using namespace std;
/* 219 Contains Duplicate II (easy)
Given an array of integers and an integer k, find out whether there are 
two distinct indices i and j in the array such that nums[i] = nums[j] and 
the absolute difference between i and j is at most k.
*/
//基本思想：遍历数组，将值依次加入set,如果有说明找到，注意set长度不大于k,一旦超过就删除元素
bool containsNearbyDuplicate(vector<int> &nums, int k)
{
    unordered_set<int> record;
    for (int i = 0; i < nums.size(); i++)
    {
        if (record.find(nums[i]) != record.end())
            return true;
        record.insert(nums[i]);
        if (record.size() > k) //record长度保持为k+1
            record.erase(nums[i - k]);
    }
    return false;
}

/* 217 Contains Duplicate (easy)
Given an array of integers, find if the array contains any duplicates.
Your function should return true if any value appears at least twice in 
the array, and it should return false if every element is distinct.
*/
//直接将值加入set即可，一旦找到，就说明重复了。
bool containsDuplicate(vector<int> &nums)
{
    unordered_set<int> record;
    for (int i = 0; i < nums.size(); i++)
    {
        if (record.find(nums[i]) != record.end())
            return true;
        record.insert(nums[i]);
    }
    return false;
}