
'''
53. Maximum Subarray连续子数组最大和
Given an integer array nums, find the contiguous subarray
(containing at least one number) which has the largest sum and return its sum.
Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
'''
INT32_MIN = -100
INT32_MAX = 100

# 动态规划： dp[i]=dp[i-1]+nums[i]/nums[i]
def maxSubArray(nums):
    if len(nums) == 1:
        return nums[0]
    dp = [0 for _ in range(len(nums))]
    dp[0] = nums[0]
    for i in range(len(nums)):
        dp[i] = dp[i - 1] + nums[i] if dp[i - 1] > 0 else nums[i]
    return max(dp)

# 分治递归解法：
def maxSubArray2(nums, l, r): #[l, r)
    if r - l <= 1:
        return nums[l]
    mid = (l + r) // 2
    res1 = maxSubArray2(nums, l, mid)
    res2 = maxSubArray2(nums, mid, r)
    best1, best2 = INT32_MIN, INT32_MIN
    tmp1, tmp2 = 0, 0
    for i in range(mid, l-1, -1):
        tmp1 += nums[i]
        if tmp1 > best1:
            best1 = tmp1
    for i in range(mid, r):
        tmp2 += nums[mid]
        if tmp2 > best2:
            best2 = tmp2
    res3 = best1 + best2
    return max(res1, res2, res3)