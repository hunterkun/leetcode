def findMedianSortedArrays(nums1, nums2):
    res = []
    m, n = len(nums1), len(nums2)
    mid = (m + n) / 2 + 1
    i, j = 0, 0
    while i < m and j < n:
        if (nums1[i] < nums2[j]):
            res.append(nums1[i])
            i += 1
        else:
            res.append(nums2[j])
            j += 1
        if len(res) >= mid:
            break
    
    while len(res) != mid:
        if i >= m:
            res.append(nums2[j])
            j += 1
        if j >= n:
            res.append(nums1[i])
            i += 1
    if (m + n) % 2:
        return res[-1]
    else:
        return (res[-1] + res[-2]) / 2.

    