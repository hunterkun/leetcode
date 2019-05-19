#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <map>
#include <algorithm>
#include <string>

using namespace std;
/*
给定一个长度为n的整数数组nums，数组中所有的数字都在0∼n−1的范围内。
数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。
请找出数组中任意一个重复的数字。

样例
nums = [2, 3, 5, 4, 3, 2, 6, 7]。
返回 2 或 3。
*/

//用set来保存访问过的元素即可
int duplicateInArray(vector<int> &nums)
{
    set<int> record;
    // for (int i = 0; i < nums.size(); i++)
    //     if (nums[i] < 0 || nums[i] >= nums.size())
    //         return -1;
    for (auto x : nums)
        if (x < 0 || x >= nums.size())
            return -1;

    for (int i = 0; i < nums.size(); i++)
    {
        if (record.find(nums[i]) == record.end())
        {
            record.insert(nums[i]);
        }
        else
        {
            return nums[i];
        }
    }
    return -1;
}

//由于题目限定了范围[0...n-1],如果没有重复元素，则第i个位置有数字i
//遍历数组，通过交换操作把当前元素放到正确的位置，如果该元素的位置已经有了，说明为重复元素
int duplicateInArray(vector<int> &nums)
{
    for (auto x : nums)
        if (x < 0 || x >= nums.size())
            return -1;

    for (int i = 0; i < nums.size(); i++)
    {
        //通过交换将当前i的位置放入正确的元素
        while (nums[i] != i) //如果该元素不在自己的位置上，则准备进行交换操作把它放在对的位置
        {
            if (nums[nums[i]] == nums[i]) //交换时看一下目的元素，相等的话说明重复
                return nums[i];
            else
            {
                swap(nums[i], nums[nums[i]]);
            }
        }
    }
    return -1;
}

/*
将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。 
数值为0或者字符串不是一个合法的数值则返回0。
*/
int StrToInt(const string &str)
{
    int s = 0;
    int sign = 1;
    int n = str.size();
    //找到第一个非空字符
    int k = 0;
    while (str[k] == ' ' && k < n)
        k++;
    if (str[k] = '+')
        k++;
    else if (str[k] = '-')
    {
        k++;
        sign = -1;
    }
    for (int i = k; i < n; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            break;
        if (s > INT32_MAX / 10 || (s == INT32_MAX / 10 && str[i] - '0' > INT32_MAX % 10))
            return sign == -1 ? INT32_MIN : INT32_MAX;
        s = s * 10 + str[i] - '0';
    }
    return s * sign;
}

/*
判断字符串是否表示一个数值
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。
但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是
*/
bool isNumber(string s)
{
    int n = s.size();
    int l = 0, r = n - 1;
    while (l < n && s[l] == ' ')
        l++;
    while (r >= 0 && s[r] == ' ')
        r--;

    bool point = false, e = false, num1 = false, num2 = false;
    for (int i = l; i <= r; i++)
    {
        switch (s[i])
        {
        case '.':
            if (point || e)
                return false;
            point = true;
            break;
        case 'e':
        case 'E':
            if (!num1 || e)
                return false;
            e = true;
        case '+':
        case '-':
            if (i != l && s[i - 1] != 'e' && s[i - 1] != 'E')
                return false;
            break;
        default:
            if (s[i] < '0' || s[i] > '9')
                return false;
            if (!e)
                num1 = true;
            else
            {
                num2 = true;
            }
            break;
        }
    }
    return (num1 && !e) || (num1 && e && num2);
}

/*
给定一个整数数组nums，找到一个具有最大和的连续子数组（子数组最少包含一个元素），
返回其最大和。
*/
//动态规划
//状态函数F(i)表示以arr[i]结尾的连续子数组的最大和,
//状态转移方程：F(i)=max(arr[i], F(i-1)+arr[i])
//ans=max(F(i))

//记忆化搜索
class Solution
{
  private:
    vector<int> memo;
    int __FindGreatestSumOfSubArray(vector<int> array, int i)
    {
        if (i == 0)
            return array[0];
        if (memo[i] != -100)
            return memo[i];
        int r = __FindGreatestSumOfSubArray(array, i - 1);

        int res = r < 0 ? array[i] : array[i] + r;
        memo[i] = res;
        return res;
    }

  public:
    int FindGreatestSumOfSubArray(vector<int> array)
    {
        memo = vector<int>(array.size(), -100);
        int res = array[0];
        for (int i = 1; i < array.size(); i++)
            res = max(res, __FindGreatestSumOfSubArray(array, i));
        return res;
    }
};

int main()
{
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int res = Solution().FindGreatestSumOfSubArray(arr);
    cout << res << endl;
    return 0;
}

/*
将一组数拼接成最大数字
排成最大数字
排成最小数字
给定一组非负整数，重新排列它们的顺序使之组成一个最大的整数
*/
bool comp(int num1, int num2)
{
    string s1 = to_string(num1) + to_string(num2);
    string s2 = to_string(num2) + to_string(num1);
    return s1 > s2;
}
string smallestNumber(vector<int> &nums)
{
    sort(nums.begin(), nums.end(), comp);
    if (!nums.empty() && nums[0] == 0)
        return "0";
    string res = "";

    for (int num : nums)
        res = res + to_string(num);
    return res;
}

//最长上升子序列
vector<int> memo;
int lengthOfLIS(vector<int> &nums)
{
    if (nums.size() == 0)
        return 0;
    int r = 0;
    memo = vector<int>(nums.size(), 0);
    for (int i = 0; i < nums.size(); i++)
        r = max(r, _lengthOfLIS(nums, i));
}

//LIS(i)=max(LIS(j)+1)  对所有的(j<i)
int _lengthOfLIS(vector<int> &nums, int i)
{
    if (i == 0)
        return 1;
    if (memo[i] != 0)
        return memo[i];
    int r = 0;
    for (int j = i - 1; j >= 0; j--)
        r = max(r, 1 + _lengthOfLIS(nums, j));
    memo[i] = r;
    return r;
}

//翻转字符串，单词不翻转
//模仿python ' '.join(s.split(' ')[::-1])
void reverseWords(string &s)
{
    vector<string> vec = split(s);
    if (vec.size() == 0)
    {
        s = "";
        return;
    }
    reverse(vec.begin(), vec.end());
    s = vec[0];
    for (int i = 1; i < vec.size(); i++)
        s += " " + vec[i];
}

vector<string> split(string &s)
{
    vector<string> res;
    int start = nextnonspace(s, 0);
    for (int i = start + 1; i <= s.size();)
        if (s[i] == ' ' || s[i] == s.size())
        {
            res.push_back(s.substr(start, i - start));
            start = nextnonspace(s, i);
            i = start + 1;
        }
        else
        {
            i++;
        }
    return res;
}

int nextnonspace(string s, int index)
{
    int i = index;
    for (; i < s.size(); i++)
        if (s[i] != ' ')
            return i;
    return i;
}

void reverse(string &s, int start, int end)
{
    int i = start, j = end;
    while (i < j)
        swap(s[i++], s[j--]);
}