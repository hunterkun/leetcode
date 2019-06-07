'''152. Maximum Product Subarray
Given an integer array nums, find the contiguous subarray 
within an array (containing at least one number) which has the largest product.
'''


'''
74. Search a 2D Matrix: Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
Integers in each row are sorted from left to right.
The first integer of each row is greater than the last integer of the previous row.
'''

def searchMatrix(matrix, target):
    if not matrix:
        return False
    m = len(matrix)
    n = len(matrix[0])
    l = 0
    r = m * n
    while l < r:
        mid = l + (r - l) // 2
        i, j = divmod(mid, n)

        if (target == matrix[i][j]):
            return True
        elif target > matrix[i][j]:
            l = mid + 1
        else:
            r = mid
    return False


'''
153. Find Minimum in Rotated Sorted Array
Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
'''

def findMin(nums):
    if len(nums) == 1:
        return nums[0]
    left = 0
    right = len(nums)

    if nums[right-1] > nums[0]:
        return nums[0]
    while left < right:
        mid = left + (right - left) // 2
        if nums[mid] < nums[mid - 1]:
            return nums[mid]
        if nums[mid] > nums[mid + 1]:
            return nums[mid + 1]
        if nums[mid] > nums[0]:
            left = mid + 1
        else:
            right = mid

'''
268. Missing number
Given an array containing n distinct numbers taken from 0, 1, 2, ..., n,
find the one that is missing from the array.
'''
def missingNumber(nums):
    sort(nums)
    for i in range(len(nums)):
        if nums[i] != i:
            res = i
            break
    return res

def missingNumber2(nums):
    records = set(nums)
    for i in range(len(nums) + 1):
        if i not in records:
            return i

def missingNumber3(nums):
    res=0
    for i in range(1,len(nums) + 1):
        res ^= i
        res ^= nums[i-1]
    return res

'''
136. Given a non-empty array of integers, every element appears twice except 
for one. Find that single one.
'''
def singleNumber(nums):
    res = 0
    for i in nums:
        res ^= nums[i]
    return res

def singleNumber(nums):
    hashtable = set()
    for i in range(len(nums)):
        if nums[i] not in hashtable:
            hashtable.add(nums[i])
        else:
            hashtable.remove(nums[i])
    assert (len(hastable) == 1)
    return hashtable.pop()


'''
448. Find all numbers disappeared in an array
Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), 
some elements appear twice and others appear once.Find all the elements 
of[1, n] inclusive that do not appear in this array.
'''

def findDisappearedNumbers(nums):
    hashtable = set(nums)
    res=[]
    for i in range(1, len(nums)+1):
        if i not in hashtable:
            res.append(i)
    return res

# 利用数组的索引作为哈希值
def findDisappearedNumbers(nums):
    for i in nums:
        nums[abs(i) - 1] = -abs(nums[abs(i) - 1])
    res=[i+1 for i in range(len(nums)) if nums[i]>0]
    return res


'''
Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), 
some elements appear twice and others appear once.
Find all the elements that appear twice in this array.
'''


'''
41. First Missing Postitive
Given an unsorted integer array, find the smallest missing positive integer.
'''

#将正负元素先分开，然后利用索引来寻找是否是有1，2，3,.....
def firstMissingPostive(nums):
    n = len(nums)
    i = 0
    while i < n:
        if (nums[i] <= 0):
            nums[i], nums[n - 1] = nums[n - 1], nums[i]
            i -= 1
            n -= 1
        i += 1
    # nums[0,n)>0
    for i in range(n):
        if (abs(nums[i])-1 < n and nums[abs(nums[i])-1] > 0):
            nums[abs(nums[i]) - 1] *= -1
    # 如果没有变负数，说明就是这个索引
    for i in range(n):
        if nums[i] > 0:
            return i + 1
    return n + 1


def firstMissingPostive(nums):
    n=len(nums)
    nums = change(nums)
    for i in range(n):
        if nums[i] != i + 1:
            return i + 1
    return n+1
    

def change(nums):
    n = len(nums)
    for i in range(n):
        while (nums[i] != i + 1):
            if (nums[i] <= 0 or nums[i] > n or nums[i]==nums[nums[i]-1]):
                break
            # 注意这里不能直接使用交换操作
            tmp = nums[i]
            nums[i], nums[tmp - 1] = nums[tmp - 1], tmp


'''
287. Find the Duplicate Number
Given an array nums containing n + 1 integers where each integer is between 1 
and n (inclusive), prove that at least one duplicate number must exist. 
Assume that there is only one duplicate number, find the duplicate one.
'''
# 如果发生冲突了，说明就是重复的元素了
def findDuplicate(nums):
    n = len(nums)
    for i in range(n):
        while (nums[i] != i + 1):
            if (nums[i]==nums[nums[i]-1]):
                return nums[i]
            # 注意这里不能直接使用交换操作
            tmp = nums[i]
            nums[i], nums[tmp - 1] = nums[tmp - 1], tmp





