/*
167 Two Sum II
给定一个有序整型数组和一个整数target,在其中寻找两个元素，
使其和为target,返回两个数的索引。
*/

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//对撞指针思路
vector<int> twoSum(vector<int> &numbers, int target)
{
    assert(numbers.size() >= 2);
    int i = 0, j = numbers.size() - 1;
    while (i < j)
    {
        int sum = numbers[i] + numbers[j];
        if (sum == target)
        {
            int res[2] = {i + 1, j + 1};
            return vector<int>(res, res + 2);
        }
        else if (sum > target)
            j--;
        else
            i++;
    }
    throw invalid_argument("the input has no solution.");
}
