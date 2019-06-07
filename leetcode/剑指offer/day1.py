'''
给定一个长度为n的整数数组nums，数组中所有的数字都在0∼n−1的范围内。
数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。
请找出数组中任意一个重复的数字。
nums = [2, 3, 5, 4, 3, 2, 6, 7]。
返回 2 或 3。
'''
def duplicateInArray(nums):
    record = set()
    for num in nums:
        if num in record:
            return num
        record.add(num)

def duplicateInArray2(nums):
    for i in range(len(nums)):
        while i != nums[i]:
            if nums[i] == nums[nums[i]]:
                return nums[i]
            temp = nums[i]
            nums[i] = nums[nums[i]]
            nums[nums[i]] = temp
    return - 1

'''
将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。 
数值为0或者字符串不是一个合法的数值则返回0。
'''
INT32_MAX=100
INT32_MIN=-100
def StrToInt(s):
    k = 0
    sign = 1
    res = 0
    # find the first not of 空格
    while (k < len(s) and s[k] != ' '):
        k += 1
    if s[k] == '+':
        k += 1
    if s[k] == '-':
        k += 1
        sign = -1
    for i in s:
        if i < '0' or i > '9':
            break
        if (res > INT32_MAX / 10 or (res == INT32_MAX / 10 and i - '0' > INT32_MAX % 10)):
            return INT32_MIN if sign == -1 else INT32_MAX

        res = res * 10 + i - '0'
    return res 




     
