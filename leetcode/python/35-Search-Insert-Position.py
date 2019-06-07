'''
35. Search Insert Position
'''
def searchInsert(nums, target):
    l, r = 0, len(nums) - 1
    if target > nums[-1]:
        return len(nums)
    while l < r:
        mid = (l + r) // 2
        if (nums[mid] >= target):
            r = mid
        else:
            l = mid + 1
    return l