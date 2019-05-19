#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
using namespace std;

vector<int> twoSum1(vector<int> &nums, int target)
{
    for (int i = 0; i < nums.size() - 1; i++)
    {
        for (int j = i + 1; j < nums.size(); j++)
        {
            if (nums[j] == target - nums[i])
            {
                vector<int> ret{i, j};
                return ret;
            }
        }
    }
    return vector<int>{0, 0};
}
//用map来记录元素和它的位置
vector<int> twoSum2(vector<int> &nums, int target)
{
    unordered_map<int, int> map;
    int n = (int)nums.size();
    for (int i = 0; i < n; i++)
    {
        auto p = map.find(target - nums[i]);
        if (p != map.end())
        {
            vector<int> ret{p->second + 1, i + 1};
            return ret;
        }
        map[nums[i]] = i;
    }
    return vector<int>{0, 0};
}

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode *addTwoNumbers(ListNode *L1, ListNode *L2)
{
    if (L1 == NULL and L2 == NULL)
        return NULL;
    else if (L1 == NULL)
        return L2;
    else if (L2 == NULL)
        return L1;
    int a = L1->val + L2->val;
    ListNode *p = new ListNode(a % 10);
    p->next = addTwoNumbers(L1->next, L2->next);
    if (a >= 10)
        p->next = addTwoNumbers(p->next, new ListNode(1));
    return p;
}

ListNode *addTwoNumbers2(ListNode *l1, ListNode *l2)
{
    ListNode preHead(0);
    ListNode *p = &preHead;
    int carry = 0;
    int sum;
    while (l1 || l2 || carry)
    {
        sum = l1->val + l2->val + carry;
        carry = sum / 10;
        p->next = new ListNode(sum % 10);
        p = p->next;
        l1 = l1 ? l1->next : l1;
        l2 = l2 ? l2->next : l2;
    }
    return preHead.next;
}

int inverse(int x)
{
    int s = 0;
    while (x)
    {
        int r = x % 10;
        s = s * 10 + r;
        x = x / 10;
    }
    return s;
}

int maxArea(vector<int> &height)
{

    int area = 0;
    int i = 0, j = int(height.size() - 1);
    while (i < j)
    {
        int l = height[i];
        int r = height[j];
        area = max(min(l, r) * (j - i), area);
        l < r ? i++ : j--;
    }
    return area;
}

float findMedianSortedArrays(int A[], int m, int B[], int n)
{
    vector<int> res;
    int *b = B;
    int *a = A;
    float r = 0;
    while (true)
    {
        if (B >= b + n)
        {
            while (A < m + a)
                res.push_back(*A++);
            break;
        }
        if (A >= a + m)
        {
            while (B < b + n)
                res.push_back(*B++);
            break;
        }
        if (*A < *B)
        {
            res.push_back(*A++);
        }
        else
        {
            res.push_back(*B++);
        }
    }

    if (res.size() % 2)
    {
        r = res[res.size() / 2];
    }
    else
    {
        r = (res[res.size() / 2] + res[res.size() / 2 - 1]) / 2.;
    }
    return r;
}

float findMedianSortedArrays2(int A[], int m, int B[], int n)
{
    vector<int> res;
    int i, j;
    int mid = (m + n) / 2 + 1;
    for (i = 0, j = 0; i < m && j < n;)
    {
        if (A[i] > B[j])
        {
            res.push_back(B[j++]);
        }
        else
        {
            res.push_back(A[i++]);
        }
        if (res.size() == mid)
            break;
    }
    while (res.size() != mid)
    {
        if (i < m)
            res.push_back(A[i++]);
        if (j < n)
            res.push_back(B[j++]);
    }
    if ((m + n) % 2 == 0)
        return (res[res.size() - 1] + res[res.size() - 2]) / 2.;
    return *(res.end() - 1);
}

//最长的无重复子串abcba
int lengthOfLongestSubstring(string str)
{
    unordered_map<char, int> map;
    int i, left = 0, maxlen = 0;
    if (str.length() == 0)
        return 0;
    for (i = 0; i < str.size(); i++)
    {
        if (map.find(str[i]) != map.end())
            left = max(map[str[i]] + 1, left);
        maxlen = max(maxlen, i - left + 1);
        map[str[i]] = i;
    }
    return maxlen;
}
//二分查找
int search(vector<int> &nums, int target)
{
    int l = 0, r = nums.size();
    int mid;
    while (l < r)
    {
        mid = l + (r - l) / 2;
        if (nums[mid] > target)
            r = mid;
        else if (nums[mid] < target)
            l = mid + 1;
        else
            return mid;
    }
    return -1;
}

vector<int> searchRange(vector<int> &nums, int target)
{
    int l = 0, r = nums.size();
    int mid;
    vector<int> res;
    while (l < r)
    {
        mid = l + (r - l) / 2;
        if (nums[mid] < target)
            l = mid + 1;
        else
            r = mid;
    }
    res.push_back(l);
    l = 0;
    r = nums.size();
    while (l < r)
    {
        mid = l + (r - l) / 2;
        if (nums[mid] <= target)
            l = mid + 1;
        else
            r = mid;
    }
    res.push_back(l - 1);
    return res[0] == res[1] + 1 ? res = {-1, -1} : res;
}
//有序数组
vector<int> searchRange2(vector<int> &nums, int target)
{
    int lb = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    int ub = upper_bound(nums.begin(), nums.end(), target) - nums.begin();
    if (lb == nums.size() || nums[lb] != target) //全部严格小于target或找不到target
        return vector<int>{-1, -1};
    return vector<int>{lb, ub - 1};
}

// 15. 3Sum
// Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0?
// Find all unique triplets in the array which gives the sum of zero.

vector<vector<int>> threeSum(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    unordered_map<int, int> map;
    vector<vector<int>> result;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i - 1] == nums[i] && i > 0)
        {
            continue;
        }
        int target = -nums[i];
        int l = i + 1, r = nums.size() - 1;
        while (l < r)
        {
            if (target == nums[l] + nums[r])
            {
                result.push_back(vector<int>{nums[i], nums[l], nums[r]});
                l++;
                r--;
                while (nums[l] == nums[l - 1] && l < r)
                    l++;
            }
            else if (target < nums[l] + nums[r])
                r--;
            else
                l++;
        }
    }
    return result;
}
//构建乘积数组
float MaxProduct(vector<float> num, int n)
{
    if (n <= 0)
        return 0;
    vector<float> s(n + 1, 1);
    vector<float> t(n + 1, 1);
    vector<float> p(n, 1);
    for (int i = 0; i < n; i++)
        s[i + 1] = s[i] * num[i];
    for (int j = n - 1; j >= 0; j--)
        t[j] = t[j + 1] * num[j];
    for (int k = 0; k < n; k++)
        p[k] = s[k] * t[k + 1];
    float pp = max_element(p.begin(), p.end());
    return pp;
}

int main(int argc, char const *argv[])
{
    string s = "pwwkew";
    int aa = lengthOfLongestSubstring(s);
    cout << aa << endl;
    return 0;

    int target = 10;
    float ss = 0;
    vector<int> nums1{1, 5, 4, 8};
    vector<int> nums2{0, 6, 2, 3};
    // vector<int> ss;
    int a[4] = {1, 4, 5, 8};
    int b[3] = {0, 2, 3};
    ss = findMedianSortedArrays2(a, 4, b, 3);
    cout << ss << endl;

    // vector<int> ss;
    // int a = inverse(123);
    // cout << a << endl;
    // int result = maxArea(nums);
    // cout << result << endl;

    // ss = twoSum2(nums, target);
    // for (auto it = ss.begin(); it != ss.end(); it++)
    // {
    //     cout << *it << endl;
    // }
    return 0;
}
