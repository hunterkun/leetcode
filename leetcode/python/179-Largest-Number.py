'''
179. Largest Number
Given a list of non negative integers, arrange them such that they 
form the largest number.
Input: [10,2]
Output: "210"
'''
# sort按小于排序，如果你认为第一个参数“小于”第二个参数（返回值<0)，则sort会把它放前面
from functools import cmp_to_key
def smallestNumber(nums):
    if any(nums):
        nums = sorted([str(x) for x in nums], key=cmp_to_key(lambda x, y: int(x + y) - int(y + x)), reverse=True)
        return ''.join(nums)
    return '0'