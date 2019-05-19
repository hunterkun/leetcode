#coding=utf8
'''
二分法专题
'''
# 非递归版本
def binarySearch(nums, target):
    l, r = 0, len(nums) - 1
    
    while (l <= r):
        mid = l + (r - l) // 2
        if (nums[mid] == target):
            return target
        elif nums[mid] > target:
            r = mid - 1
        else:
            l = mid + 1
    return - 1
    
# 递归版本
def binarySearch2(nums, target):
    return _binarySearch(nums, 0, len(nums) - 1, target)

def _binarySearch(nums, l, r, target):
    if (l > r):
        return -1   
    mid = l + (r - l) // 2
    if (nums[mid] == target):
        return mid
    elif nums[mid] > target:
        return _binarySearch(nums, l, mid - 1, target)
    else:
        return _binarySearch(nums, mid + 1, r, target)

'''
Since the return type is an integer, the decimal digits are
truncated and only the integer part of the result is returned.
'''

def mySqrt(x):
    l, r = 0, x
    while (l < r):
        mid = (l + r) // 2 
        if (mid ** 2 > x): #这个条件说明的是会找到?**2>x的最小元素
            r = mid
        else:
            l = mid + 1
    return l-1
    

'''
378. 有序矩阵中第K小的元素
'''
# 二分查找，有序矩阵，左上角的数字一定是最小的，而右下角的数字一定是最大的，
# 这个是我们搜索的范围，然后我们算出中间数字mid,查找它在数组中是第几小的，如果
# k小于它，说明在前半部分，如果k大于它，说明在后半部分
def kthSmallest(matrix, k):
    m = len(matrix)
    n = len(matrix[0])
    l, r = matrix[0][0], matrix[m-1][n-1]
    while (l < r):
        mid = (l + r) // 2
        '''
        下面一段代码可以抽象出来，如果满足条件(rank>=k)，则r=mid,否则l=mid+1,这是找到满足条件的最小值，如果rank==k直接返回的话
        找到的不一定是数组中的元素。而如果是这样写的话，找到的一定是数组中第k小的元素。
        '''
        rank = get_rank(matrix, mid)
        if (rank >= k):
            r = mid
        else:
            l = mid + 1
    return l

# 从左上角找，找到数组中小于target的元素个数
def get_rank(matrix, target):
    m = len(matrix)
    n = len(matrix[0])
    i, res = 0, 0
    while (i < m and matrix[i][0] <= target):
        j = 0
        while (j < n and matrix[i][j] <= target):
            res += 1
            j += 1
        i += 1
    return res

# 从左下角找最快
def get_rank2(matrix, target):
    n = len(matrix[0])
    i, j = n - 1, 0
    count=0
    while (i >= 0 and j < n):
        if (target >= matrix[i][j]):
            count += i + 1
            j += 1
        else:
            i -= 1
    return count


from heapq import heappush,heappop
# 还可以使用堆完成
def kthSmallest2(matrix, k):
    m = len(matrix)
    n = len(matrix[0])
    pq = []
    for i in range(m):
        for j in range(n):
            heappush(pq, -matrix[i][j])
            if (len(pq) > k):
                heappop(pq)
    return -heappop(pq)

def kthSmallest3(matrix, k):
    m = len(matrix)
    n = len(matrix[0])
    visited = [[False for _ in range(n)] for _ in range(m)]
    pq = []
    heappush(pq, (matrix[0][0], 0, 0))
    visited[0][0] = True
    val = matrix[0][0]
    for _ in range(k):
        val, i, j = heappop(pq)
        if (i + 1 < m and not visited[i + 1][j]):
            heappush(pq, (matrix[i + 1][j], i + 1, j))
            visited[i+1][j]=True
        if (j + 1 < n and not visited[i][j + 1]):
            heappush(pq, (matrix[i][j + 1], i, j + 1))
            visited[i][j + 1] = True
        
    return val

matrix = [[1, 3, 5], [2, 4, 7], [4, 7, 17]]
l=sum(matrix, [])
print(l)



'''
1011.在 D 天内送达包裹的能力
返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力
'''
# 本质上是lower_bound问题
def shipWithinDdays(weights, D):
    l, r = max(weights), sum(weights)
    while (l < r):
        mid = (l + r) // 2
        days = 1
        count = 0
        for weight in weights:
            count += weight
            if count > mid:
                days += 1
                count = weight
        if days > D:
            l = mid + 1
        elif days <= D: #就是求解days小于等于D的条件下的值
            r = mid
    return l


# 有序数组中第一个大于等于target的元素索引
def lower_bound(nums, target):
    l, r = 0, len(nums)-1
    while (l < r):
        mid = l + (r - l) // 2
        if (nums[mid] >= target): #可以看到这就是条件
            r = mid
        else:
            l = mid + 1
    return l

# 有序数组中第一个大于target的元素索引
def upper_bound(nums, target):
    l, r = 0, len(nums)-1
    while (l < r):
        mid = l + (r - l) // 2
        if (nums[mid] > target):
            r = mid
        else:
            l = mid + 1
    return l


        
# 二分查找法, 在有序数组arr中, 查找target
# 如果找到target, 返回第一个target相应的索引index
# 如果没有找到target, 返回比target小的最大值相应的索引, 如果这个最大值有多个, 返回最大索引
# 如果这个target比整个数组的最小元素值还要小, 则不存在这个target的floor值, 返回-1                
def floor(nums, x):
    l, r = 0, len(nums) - 1
    if x >= max(nums):
        return r

    while (l < r):
        mid = l + (r - l) // 2
        if (nums[mid] > x):
            r=mid
        else:
            l = mid + 1

    return l - 1         



# 二分查找法, 在有序数组arr中, 查找target
# 如果找到target, 返回最后一个target相应的索引index
# 如果没有找到target, 返回比target大的最小值相应的索引, 如果这个最小值有多个, 返回最小的索引
# 如果这个target比整个数组的最大元素值还要大, 则不存在这个target的ceil值, 返回整个数组元素个数n
def ceil(nums, x):
    l, r = 0, len(nums) - 1
    if x >= max(nums):
        return r+1
    while (l < r):
        mid = l + (r - l) // 2
        if (nums[mid] >= x):
            r=mid
        else:
            l = mid + 1

    return l
