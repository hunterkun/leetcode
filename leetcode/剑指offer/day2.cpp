#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include <set>
using namespace std;

/*
在一个字符串(1<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符,
并返回它的位置
*/

int FirstNotRepeatingChar(string str)
{
    map<char, int> count;
    for (auto &c : str)
        count[c]++;

    for (int i = 0; i < str.size(); i++)
        if (count[str[i]] == 1)
            return i;
    return -1;
}

/*350 Intersection of Two Arrays
两个数组的交集
*/
//基本思想：利用map同时记录元素和对应的频次，再遍历查找另一个数组。
vector<int> intersection2(vector<int> &nums1, vector<int> &nums2)
{
    unordered_map<int, int> record;
    for (int &num : nums1)
        record[num]++;

    vector<int> res;
    for (int &num : nums2)
    {
        if (record[num] != 0)
        {
            res.push_back(num);
            record[num]--;
        }
    }
    return res;
}

/*202 Happy Number
A happy number is a number defined by the following process: 
Starting with any positive integer, replace the number by the sum of 
the squares of its digits, and repeat the process until the number 
equals 1 (where it will stay), or it loops endlessly in a cycle which 
does not include 1. Those numbers for which this process ends in 1 are
happy numbers.
*/
//思路：如果结果为1，那肯定是，退出。如果结果不是1，那就使用哈希表记录该结果，
//如果哈希表的记录中有，说明陷入死循环，则肯定不是，退出。

int f(int n)
{
    int s = 0;
    while (n)
    {
        int r = n % 10;
        s += r * r;
        n /= 10;
    }
    return s;
}

bool isHappy(int n)
{
    set<int> record;

    while (true)
    {
        int s = f(n);
        if (s == 1)
            return true;
        else if (record.find(s) != record.end())
        {
            return false;
        }
        else
        {
            record.insert(s);
        }

        n = s;
    }
}
/*
丑数
把只包含因子2、3和5的数称作丑数（Ugly Number）
例如6、8都是丑数，但14不是，因为它包含因子7。 习惯上我们把1当做是第一个丑数。
求按从小到大的顺序的第N个丑数
*/
bool isUglyNumber(int n)
{
    while (n % 2 == 0) //能被2整除
        n = n / 2;
    while (n % 3 == 0)
        n = n / 3;
    while (n % 5 == 0)
        n = n / 5;
    return n == 1 ? true : false;
}
int getUglyNumber(int index)
{
    int n = 0;
    int i = 1;
    while (n != index)
    {
        if (isUglyNumber(i))
            n++;
        i++;
    }
    return i;
}
