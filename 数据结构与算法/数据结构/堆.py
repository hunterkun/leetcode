class Maxheap:
    def __init__(self):
        self.count = 0
        self.heaplist = [-1]

    def heapify(self, nums):
        self.heaplist.extend(nums)
        self.count = len(nums)
        for i in range(self.count // 2, 0, -1):
            self.shiftDown(i)

    def size(self):
        return self.count

    def isEmpty(self):
        return self.count == 0

    def insert(self, item):
        self.heaplist.append(item)
        self.count += 1
        self.shiftUp(self.count)

    def shiftUp(self, k):
        # while (count>2 and self.heaplist[count] > self.heaplist[count // 2]):
        #     self.heaplist[count], self.heaplist[count // 2] = self.heaplist[count // 2], self.heaplist[count]
        #     count=count // 2
        tmp=self.heaplist[k]
        while (k // 2):
            if (tmp > self.heaplist[k // 2]):
                self.heaplist[k] = self.heaplist[k // 2]
                k = k // 2
            else:
                break
        self.heaplist[k] = tmp

    def extractMax(self):
        val = self.findMax()
        self.heaplist[1] = self.heaplist[self.count]
        del self.heaplist[self.count]
        self.count -= 1
        if self.count == 0:
            return val
        self.shiftDown(1)
  
        return val

    def findMax(self):
        if self.count == 0:
            raise
        return self.heaplist[1]
    
    def shiftDown(self, k):
        tmp = self.heaplist[k]
        while (2 * k <= self.count):   
            j = 2 * k
            if (j + 1 <= self.count and self.heaplist[j] < self.heaplist[j + 1]):
                j += 1
            if (tmp < self.heaplist[j]):
                self.heaplist[k] = self.heaplist[j]
                k = j
            else:
                break
        self.heaplist[k] = tmp
        
    # extractMax + insert == 复制+shiftDown
    def replace(self, item):
        ret = self.heaplist[1]
        self.heaplist[1] = item
        self.shiftDown(1)
        return ret



class PriorityQueue:
    def __init__(self):
        self.maxHeap = Maxheap()
    
    def getSize(self):
        return self.maxHeap.size()
    
    def isEmpty(self):
        return self.maxHeap.isEmpty()

    def getFront(self):
        return self.maxHeap.findMax()

    def enqueue(self,e):
        self.maxHeap.insert(e)

    def dequeue(self):
        return self.maxHeap.extractMax()


'''
Given a non-empty array of integers, return the k most frequent elements.
'''
from heapq import heappush, heappop
def topKFrequent(nums, k):
    counter = dict()
    pq = []
    res = []
    for i in nums:
        counter[i] = counter[i] + 1 if i in counter else 1
    # 确保pq的大小为k,而不是任意大，这时就是最小堆
    for i in counter.keys():
        if len(pq)<k:
            heappush(pq, (counter[i],i)) # tuple with first element to be sorted
        else:
            if counter[i]>pq[0][0]:
                heappop(pq)
                heappush(pq, (counter[i],i))
                
    while pq:
        res.append(heappop(pq)[1])
    return res


from heapq import nlargest
def topKFrequent2(nums, k):
    counter=dict()
    for i in nums:
        counter[i] = counter[i] + 1 if i in counter else 1
    return [i[0] for i in nlargest(k, counter.items(), key=lambda e:e[1])]
    

# print(topKFrequent([4,1,-1,2,-1,2,3],2))

    
        





            
import random      
heap = Maxheap()

# heap.insert(3)
# heap.insert(-5)
# heap.insert(0)
# heap.insert(14)
# heap.insert(34)
for _ in range(50):
    heap.insert(random.randint(0, 100))
    
# print(heap.heaplist)
# print(heap.size())
# while not heap.isEmpty():
#     print(heap.extractMax(), end=' ')

# print('')
# print(heap.heaplist)
# print(heap.size())

# 利用堆实现排序算法
# 复杂度：O(nlogn)
def heapSort1(nums):
    maxheap = Maxheap()
    for i in nums:
        maxheap.insert(i)

    nums2=list()
    for _ in range(len(nums)):
        nums2.append(maxheap.extractMax())
    return nums2[::-1]

# 复杂度：O(n)
def heapSort2(nums):
    maxheap = Maxheap()
    maxheap.heapify(nums)
    nums2 = [maxheap.extractMax() for _ in range(len(nums))]
    nums2.reverse()
    return nums2

# 原地堆排序
# 与上面实现的堆不同，这里索引从1开始
def heapSort(nums):
    # 首先对nums进行heapify
    # 第一个非叶子节点(count-1)/2
    n = len(nums)
    for k in range((n - 1) // 2, -1, -1):
        __shiftDown(nums, n, k)
    
    for i in range(n - 1, 0, -1):
        nums[0], nums[i] = nums[i], nums[0]
        __shiftDown(nums, i, 0)
        

def __shiftDown(nums, n, k):
    tmp = nums[k]
    while (2 * k + 1 < n):   
        j = 2 * k + 1
        if (j + 1 < n and nums[j] < nums[j + 1]):
            j += 1
        if (tmp < nums[j]):
            nums[k] = nums[j]
            k = j
        else:
            break
    nums[k] = tmp
        

max=50
a = [random.randint(-max, max) for x in range(max)]
# print(a)
heapSort(a)
print(a)


            
        

        
        

        