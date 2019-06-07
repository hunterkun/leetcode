'''
1. Two Sum
'''
# One-Pass Hash Table
def twosum(nums, target):
    records = {}
    for i in range(len(nums)):
        if target - nums[i] in records:
            return records[target-nums[i]], i
        records[nums[i]] = i    










    

    