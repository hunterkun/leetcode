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

//125 字符串回文, 344 逆序,345 ,11 contain most water
bool isPalindrome(string s)
{
    int n = s.length();
    int l = 0, r = n - 1;
    while (l < r)
    {
        if (!isalnum(s[l]))
            l++;
        else if (!isalnum(s[r]))
            r--;
        else
        {
            if (tolower(s[l]) != tolower(s[r]))
                return false;
            l++;
            r--;
        }
    }
    return true;
}