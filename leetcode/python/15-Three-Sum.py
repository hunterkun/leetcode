
'''
15. Three Sum
'''
def threeSum(nums):
    counter = {}
    ret=[]
    for i in nums:
        if i not in counter:
            counter[i]=0
        counter[i] += 1
    if 0 in counter and counter[0] >= 3:
        ret.append((0, 0, 0))
    nums2 = list(set(nums))
    nums2.sort()
    for i in range(len(nums2)):
        if counter[nums2[i]] >= 2 and -2*nums2[i]!=nums2[i] and -2*nums2[i] in counter and counter[-2*nums2[i]]>0:
            ret.append((nums2[i], nums2[i], -2 * nums2[i]))
        for j in range(i + 1, len(nums2)):
            if - (nums2[i] + nums2[j]) in counter and counter[-(nums2[i] + nums2[j])] > 0 and - (nums2[i] + nums2[j]) > nums2[j]:
                ret.append((nums2[i], nums2[j], -(nums2[i] + nums2[j])))

    return ret