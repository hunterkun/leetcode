// 查找表相关 set和map数据结构

#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <map>
using namespace std;

/*349 Intersection of Two Arrays
给定两个数组nums,求两个数组的公共元素。
结果中每个元素只能出现一次，出现顺序是任意的
*/

//基本思想：将其中一个nums变为set，然后对另一个数组进行遍历查找即可
vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
{
    set<int> record;
    set<int> res;
    record.insert(nums1.begin(), nums1.end());
    for (int i = 0; i < record.size(); i++)
    {
        if (record.find(nums2[i]) != record.end())
            res.insert(nums2[i]);
    }
    return vector<int>(res.begin(), res.end());
}

/*350 Intersection of Two Arrays
两个数组的交集
*/
//基本思想：利用map同时记录元素和对应的频次，再遍历查找另一个数组。
vector<int> intersection2(vector<int> &nums1, vector<int> &nums2)
{
    map<int, int> record;
    for (int i = 0; i < nums1.size(); i++)
        record[nums1[i]]++;
    vector<int> result;
    for (int i = 0; i < record.size(); i++)
    {
        if (record[nums2[i]] != 0)
        {
            result.push_back(nums2[i]);
            record[nums2[i]]--;
        }
    }
    return result;
}

//242 Valid Anagram
//解法1：将字符串进行排序
bool isAnagram(string s, string t)
{
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());

    return s == t;
}
//解法2：利用长度为26的数组，每个字母进行统计，出现一次加1
//遍历另一个字符串，出现一次就减1，如果小于0说明没有就失败了。

//202 Happy Number
//思路：如果结果为1，那肯定是，退出。如果结果不是1，那就使用哈希表记录该结果，
//如果哈希表的记录中有，说明陷入死循环，则肯定不是，退出。

//290 Word Pattern
//205 lsomorhphic Strings
//451 Sort Characters By Frequency
