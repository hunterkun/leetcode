#coding=utf-8

'''
爬楼梯，可以跨一步或跨两步
基本思路：第n个阶梯可以由n-1个阶梯或n-2个阶梯到达
简单递归O(2^n)
'''

import functools
import timeit

memoized = functools.lru_cache(maxsize=None)

@memoized
def climb_dp(n):
    if n==1 or n==0:
        return 1
    return climb_dp(n-1)+climb_dp(n-2)
    
# t1=timeit.Timer('climb_dp(5)',globals=globals())
# print('climb_dp: %s s' % t1.timeit(number=1))

# print(climb_dp.cache_info())

'''
343 Integer Break
Given a positive integer n, break it into the sum of at least two positive
integers and maximize the product of those integers. Return the maximum product.
'''
# f(n)=max(1*f(n-1),2*f(n-2),....f(n-1)*1)
@memoized
def integerBreak(n):
    if n==1:
        return 1
    res=0
    for i in range(1, n):
        res=max(res,i*(n-i),i*integerBreak(n-i))
    return res

# t1=timeit.Timer('integerBreak(30)',globals=globals())
# print('Time: %s s' % t1.timeit(number=1))  

def integerBreak_dp(n):
    memo=[0 for _ in range(n+1)]
    memo[1]=1
    for i in range(2, n+1):
        for j in range(1, i):
            memo[i]=max(memo[i],memo[i-j]*j, (i-j)*j)
    
    return memo[n]

# t1=timeit.Timer('integerBreak(50)',globals=globals())
# print('Memo Time: %s s' % t1.timeit(number=1)) 
# t2=timeit.Timer('integerBreak_dp(50)',globals=globals())
# print('DP Time: %s s' % t2.timeit(number=1)) 

'''    
寻找最少的平方数，使得和为n
'''
@memoized
def numSquares(n):
    if n == 1:
        return 1
    res = n
    i=1
    while i*i<=n:
        res=min(res, 1 + numSquares(n - i * i))
        i += 1
    return res


'''
House Robber (Easy)
Given a list of non-negative integers representing the amount of money of each house
determine the maximum amount of money you can rob tonight without alerting the police.
'''
class Solution:
    def __init__(self, nums):
        self.nums = nums

    @memoized
    def rob(self,index):
        if index >= len(self.nums):
            return 0
        res=0
        for i in range(index, len(self.nums)):
            res=max(res,self.nums[i]+self.rob(i+2))
        return res

    def rob2(self):
        n = len(self.nums)
        if n == 0:
            return 0
        memo= [0 for _ in range(n)]
        memo[-1] = self.nums[-1]
        for i in range(n - 2, -1, -1):
            for j in range(i,n):
                memo[i] = max(memo[i], self.nums[j] + memo[j + 2] if j + 2 < n else self.nums[j])
        return memo[0]

'''        
House Robber2(Med)
街道为环形，最后一个和第一个房子相邻。
'''


# from random import randint
# nums2=[ randint(20,300) for _ in range(300)]
# print(Solution(nums2).rob(0))
# print(Solution(nums2).rob2())

# t1=timeit.Timer('Solution(nums).rob(0)',globals=globals())
# print('rob1: %s s' % t1.timeit(number=1))
# t2=timeit.Timer('Solution(nums).rob2()',globals=globals())
# print('rob2: %s s' % t2.timeit(number=1))


'''
You are given coins of different denominations and a total amount of money 
amount. Write a function to compute the fewest number of coins that you need 
to make up that amount. If that amount of money cannot be made up by any 
combination of the coins, return -1.
'''

import sys
sys.setrecursionlimit(5000)

@memoized
def recMC(change):
    ans = amount
    if change in coinValueList:
        return 1
    else:
        for i in [c for c in coinValueList if c <= change]:
            ans = min(ans, 1+recMC(change-i))
    return ans

def coinChange(amount):
    res = recMC(amount)
    return - 1 if res == amount else res
   

def coinChange2(change):
    memo = [change + 1] * (change + 1)
    memo[0]=0
    for coin in range(change + 1):
        for i in [c for c in coinValueList if c <= coin]:
                memo[coin] = min(memo[coin - i] + 1, memo[coin])

    return -1 if memo[change]==change+1 else memo[change]


# coinValueList = [5, 10, 20, 50, 100]
# amount = 200
# print(coinChange2(amount))

'''
背包问题:
容量为C,n种不同的物品，每件物品重wi,价值为vi,不超过容量C的前提下，
所放物体的最大价值。
状态函数：F(n,C), 考虑[0...n-1]范围内的物品, 参数个数取决于问题的限制条件
转移方程：F(i,c)=max(F(i-1, c)， F(i-1,c-Wi)+vi)
'''

def knapsack01(w, v, C):
    assert (len(w) == len(v))
    n=len(w)
    return _knapsack01(n-1, C)

@memoized
def _knapsack01(index, c):
    if (index <0  or c <= 0):
        return 0
    res = _knapsack01(index - 1, c)
    if (c-w[index]>=0):
        res =max(res,_knapsack01(index-1, c-w[index])+v[index])
    return res
    
w = [1,2,3]
v = [6,10,12]
C = 5
# res=knapsack01(w,v,C)
# print(res)

def knapsack01_dp(w, v, C):
    n=len(w)
    memo = [[0 for _ in range(C+1)] for _ in range(n)]
    for i in range(C+1):
        memo[0][i] = v[0] if w[0] <= i else 0
    for i in range(1, n):
        for j in range(C+1):
            memo[i][j] = max(memo[i-1][j - w[i]] + v[i], memo[i - 1][j]) if j >= w[i] else memo[i - 1][j]
    
    return memo[n-1][C]

print(knapsack01_dp(w, v, C))
    


'''
Given a string, your task is to count how many palindromic substrings in 
this string. The substrings with different start indexes or end indexes are 
counted as different substrings even they consist of same characters. 
'''

def countstring(s):
    table = [[False for _ in range(len(s))] for _ in range(len(s))]
    count = 0
    for i in range(len(s)):
        table[i][i] = True
        count += 1
    for i in range(len(s)-1):
        if s[i] == s[i + 1]:
            table[i][i + 1] = True
            count += 1
    for j in range(2, len(s)):
        for i in range(len(s)-j):
            if s[i] == s[i + j] and table[i + 1][i + j - 1] == True:
                table[i][i + j] = True
                count += 1
    return count


'''
给定一个整数数组nums，找到一个具有最大和的连续子数组（子数组最少包含一个元素），
返回其最大和
'''
# 如果每次求talbe的后一个数都只需要table的前一个数的话table[i]=f(table[i-1])
# 那不用table用一个数表示也行
# memo表示以i结尾的子数组的最大和
def maxSubArray(nums):
    if (len(nums) == 0):
        return 0
    memo = [0] * len(nums)
    memo[0] = nums[0]
    for i in range(1, len(nums)):
        memo[i] = max(nums[i],nums[i]+memo[i-1])
    return max(memo)

# print(maxSubArray([2,3,4,-1,9,-10,2]))

'''
5. Longest Palindromic Substring
Given a string s, find the longest palindromic substring in s.
'''
def longestPalindrome(s):
    n = len(s)
    table = [[False] * n for i in range(n)]
    ans = ''
    maxlen = 0
    for i in range(n):
        table[i][i] = True
        maxlen = 1
        ans = s[i]
    for i in range(n-1):
        if s[i] == s[i + 1]:
            table[i][i + 1] = True
            maxlen = 2
            ans = s[i:i + 2]

    for j in range(2, n):
        for i in range(n - j):
            if table[i + 1][i + j - 1] and s[i] == s[i + j]:
                table[i][i + j] = True
                if maxlen < j+1:
                    maxlen = j+1
                    ans = s[i:i + j + 1]
    return ans
    for i in range(n):
        for j in range(i+1):
            if table[j][n - i - 1 + j]:
                return s[j:n - i + j]


# '''
# 300. Longest Increasing Subsequence
# There may be more than one LIS combination, it is only necessary for you to return the length.
# Your algorithm should run in O(n2) complexity.
# '''

# # 递增规则：
# # table[i] = table[j]+1 if nums[i]>nums[j] (0<=j<i)
# # 和找零钱差不多道理对吧


# def lengthOfLIS(nums):
#     n = len(nums)
#     table = [1] * n
#     for i in range(n):
#         for j in range(i):
#             if nums[i] > nums[j] and table[j] + 1 > table[i]:
#                 table[i] = table[j] + 1
#     return max(table)

# # 直接找出递增子序列就好了，如果大于就添加进来，如果是中间值，就用二分搜索把他的上家挤掉


# def binary_search(nums, target):
#     l = 0
#     r = len(nums)
#     while l < r:
#         mid = l + (r - l) // 2
#         if target == nums[mid]:
#             return mid
#         elif target < nums[mid]:
#             r = mid
#         else:
#             l = mid + 1
#     return l


# def lengthofLIS(nums):
#     table = [nums[0]]
#     for num in nums:
#         if num > table[-1]:
#             table.append(num)
#         elif num < table[0]:
#             table[0] = num
#         else:
#             i = binary_search(table, num)
#             table[i] = num
#     return len(table)


# def findLength(A, B):
#     pass


# '''
# 最长公共子序列
# '''

# # 递归解法


# def CommonSubsequence(A, B, i, j):
#     if i == 0 or j == 0:
#         return 0

#     if A[i-1] == B[j-1]:
#         lcs = CommonSubsequence(A, B, i-1, j-1) + 1
#     else:
#         lcs = max(CommonSubsequence(A, B, i-1, j),
#                   CommonSubsequence(A, B, i, j-1))
#     return lcs


# def CommonSubsequence2(A, B):
#     return CommonSubsequence(A, B, len(A), len(B))


# def lcs(A, B):
#     table = [[0] * (len(B) + 1) for _ in range(len(A) + 1)]
#     for i in range(1, len(A)+1):
#         for j in range(1, len(B) + 1):
#             if A[i-1] == B[j-1]:
#                 table[i][j] = table[i - 1][j - 1] + 1
#             else:
#                 table[i][j] = max(table[i - 1][j], table[i][j - 1])
#     return table[len(A)][len(B)], table


# # 打印最长公共序列
# ans = []


# def traceBack(A, B, i, j, table, s=''):
#     while (i > 0 and j > 0):
#         if A[i - 1] == B[j - 1]:
#             s += A[i - 1]
#             i -= 1
#             j -= 1
#         else:
#             if table[i - 1][j] == table[i][j - 1]:
#                 traceBack(A, B, i - 1, j, table, s)
#                 traceBack(A, B, i, j - 1, table, s)
#                 return
#             elif table[i - 1][j] > table[i][j - 1]:
#                 i -= 1
#             else:
#                 j -= 1
#     ans.append(s[::-1])


# '''
# 最长公共子串的长度
# '''

# # 用二维的表去记录


# def lcs2(A, B):
#     table = [[0] * (len(B) + 1) for _ in range(len(A) + 1)]
#     ans = 0
#     for i in range(1, len(A)+1):
#         for j in range(1, len(B) + 1):
#             if A[i-1] == B[j-1]:
#                 table[i][j] = table[i - 1][j - 1] + 1
#                 if (table[i][j] > ans):
#                     ans = table[i][j]

#     return ans

# # 用一维的表记录


# def lcs3(A, B):
#     if len(A) > len(B):
#         return lcs3(B, A)
#     table = [0] * (len(B))
#     ans = 0
#     for i in range(len(A)):
#         tmp = [0] * (len(B))
#         for j in range(len(B)):
#             if A[i] == B[j]:
#                 if j == 0:
#                     tmp[0] = 1
#                 else:
#                     tmp[j] = table[j-1] + 1
#                 if (tmp[j] > ans):
#                     ans = tmp[j]
#         table = tmp
#     return ans
