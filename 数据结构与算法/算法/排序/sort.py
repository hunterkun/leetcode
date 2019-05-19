#coding=utf-8

#1. 冒泡排序
def bubblesort(nums):
    for i in range(len(nums)):
        for j in range(1,len(nums)-i):
            if (nums[j] < nums[j-1]):
                nums[j - 1], nums[j] = nums[j], nums[j - 1]
    return

def bubblesort2(nums):
    swap=False
    for i in range(len(nums)):
        for j in range(1, len(nums) - i):
            if (nums[j] < nums[j - 1]):
                nums[j - 1], nums[j] = nums[j], nums[j - 1]
                swap = True
        if swap == False:
            break

def bubblesort3(nums):
    n = len(nums)
    while True:
        index = 0
        for j in range(1, n):
            if (nums[j] < nums[j - 1]):
                nums[j - 1], nums[j] = nums[j], nums[j - 1]
                index = j
        n = index
        if n == 0:
            break
    return



#2. 快速排序
def quicksort(nums):
    n = len(nums)
    __quicksort(nums, 0, n - 1)

def __quicksort(nums, l, r):
    if (l >= r):
        return
    p = partition(nums, l, r)
    __quicksort(nums, l, p - 1)
    __quicksort(nums, p + 1, r)

from random import randint   
# nums(l...j]<v, nums[j+1...i-1]>=v
def partition(nums, l, r):
    k = randint(l, r)
    nums[l], nums[k] = nums[k], nums[l]
    v = nums[l]
    j = l
    for i in range(l+1,r+1):
        if (nums[i] < v):
            j+=1
            nums[i], nums[j] = nums[j], nums[i]
    nums[l], nums[j] = nums[j], nums[l]
    return j

# 三路快排
# nums(l...j]<v, nums(j...i]=v, nums(k...r]>v
def partition2(nums, l, r):
    k = randint(l, r)
    nums[l], nums[k] = nums[k], nums[l]
    v = nums[l]
    j = l; k = r; i = l + 1
    while (i <= k):
        if (nums[i] > v):
            nums[i], nums[k] = nums[k], nums[i]
            k -= 1
        elif (nums[i] < v):
            j+=1
            nums[i], nums[j] = nums[j], nums[i]
            i += 1
        else:
            i += 1
    nums[l], nums[j] = nums[j], nums[l]
    return j - 1, k + 1
    
def quicksort2(nums):
    n = len(nums)
    __quicksort2(nums, 0, n - 1)

def __quicksort2(nums, l, r):
    if (l >= r):
        return
    j,k = partition2(nums, l, r)
    __quicksort(nums, l, j)
    __quicksort(nums, k, r)


# 第k大的数
def quicksortFind(nums, k):
    n = len(nums)
    res = __quicksortFind(nums, 0, n - 1, n-k)
    return res

def __quicksortFind(nums, l, r, k):
    j,p = partition2(nums, l, r)
    if ( p <= k):
        return __quicksortFind(nums, p, r, k)
    elif (j >= k):
        return __quicksortFind(nums, l, j, k)
    else:
        return nums[k]


# 归并排序
def mergesort(nums):
    __mergesort(nums, 0, len(nums) - 1)

def __mergesort(nums, l, r):
    if (l >= r):
        return
    mid = l + (r - l) // 2
    __mergesort(nums, l, mid)
    __mergesort(nums, mid + 1, r)
    if(nums[mid]>nums[mid+1]):
        __merge(nums, l, mid, r)
    
def __merge(nums, l, mid, r):
    nums2=[]
    for i in range(l, r + 1):
        nums2.append(nums[i])
    i = l; j = mid + 1
    for k in range(l, r + 1):
        if (i > mid):
            nums[k] = nums2[j-l]
            j += 1
        elif (j>r):
            nums[k] = nums2[i-l]
            i+=1
        elif (nums2[i-l] > nums2[j-l]):
            nums[k] = nums2[j-l]
            j+=1
        else:
            nums[k] = nums2[i-l]
            i += 1


# 逆序对的数量
def inversioncount(nums):
    return __inversioncount(nums, 0, len(nums) - 1)

def __inversioncount(nums, l, r):
    if (l >= r):
        return 0
    mid = l + (r - l) // 2
    return __inversioncount(nums, l, mid) + __inversioncount(nums, mid + 1, r) \
           + __inversionmerge(nums, l, mid, r)
    
def __inversionmerge(nums, l, mid, r):
    nums2=[]
    for i in range(l, r + 1):
        nums2.append(nums[i])
    i = l; j = mid + 1
    count=0
    for k in range(l, r + 1):
        if (i > mid):
            nums[k] = nums2[j-l]
            j += 1
        elif (j>r):
            nums[k] = nums2[i-l]
            i+=1
        elif (nums2[i-l] > nums2[j-l]):
            nums[k] = nums2[j-l]
            j += 1
            count += mid-i+1
        else:
            nums[k] = nums2[i-l]
            i += 1
    return count



nums = [randint(0, 100) for _ in range(5)]
print(nums)
# ans = quicksortFind(nums, 2)
ans = inversioncount(nums)
print(ans)
        
    


                