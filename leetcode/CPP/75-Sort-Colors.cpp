//排序问题变种
/*
75 Sort Colors
给定一个有n个元素的数组，数组中元素的取值只有0，1，2三种可能。为这个数组排序
*/

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//计数排序
//扫描数组两遍
void sortColors(vector<int> &nums)
{
    int count[3] = {0};
    for (int i = 0; i < nums.size(); i++)
    {
        assert(nums[i] <= 3 && nums[i] >= 0);
        count[nums[i]]++;
    }
    for (int i = 0; i < nums.size(); i++)
    {
        if (i < count[0])
            nums[i] = 0;
        else if (i < count[1])
            nums[i] = 1;
        else
            nums[i] = 2;
    }
}

//3路快排思路,只遍历一遍数组
void sortColors(vector<int> &nums)
{
    //nums[0...zero]=0, nums[zero+1...i-1]==1
    //nums[two...n-1]==2
    int n = nums.size();
    int zero = -1, two = n, i = 0;
    while (i < two)
    {
        if (nums[i] == 0)
        {
            swap(nums[++zero], nums[i++]);
        }

        else if (nums[i] == 1)
            i++;
        else
        {
            assert(nums[i] == 2);
            swap(nums[i], nums[--two]);
        }
    }
}