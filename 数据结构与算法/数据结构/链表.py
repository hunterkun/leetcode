#coding=utf8
class Node:
    def __init__(self,e, node_next=None):
        self.e = e
        self.next = node_next

class LinkedList():
    def __init__(self):
        # 虚拟头节点，（头节点的前一个节点）
        self.dummyHead = Node(None, None)
        self.size = 0
        
    def getSize(self):
        return self.size

    def isEmpty(self):
        return self.size == 0

    # 在索引处插入元素e
    def add(self, index, e):
        count = 0
        prev = self.dummyHead
        while count < index:
            prev = prev.next
            count += 1
        # node = Node(e)
        # node.next = prev.next
        # prev.next = node
        prev.next = Node(e, prev.next)
        self.size += 1

    # 在链表头插入元素
    def addFirst(self, e):
        # 不用虚拟头节点，单独处理头节点
        # node = Node(e)
        # node.next = head
        # head = node
        # self.head = Node(e, self.head)
        # self.size += 1
        self.add(0, e)
        
    def addLast(self, e):
        self.add(self.size, e)

    def travel(self):
        cur = self.dummyHead
        for i in range(self.size):
            print(cur.next.e, end='->')
            cur = cur.next
        print('NULL')

    def getter(self, index):
        cur=self.dummyHead.next
        for _ in range(index):
            cur = cur.next
        return cur.e
    
    def getFirst(self):
        return self.getter(0)
    
    def getLast(self):
        return self.getter(self.size-1)
    
    def setter(self, index, e):
        cur=self.dummyHead.next
        for _ in range(index):
            cur = cur.next
        cur.e = e
    
    def contains(self, e):
        cur = self.dummyHead.next
        while cur is not None:
            if cur.e == e:
                return True
            cur = cur.next
        return False
    
    def remove(self, index):
        prev = self.dummyHead
        for i in range(index):
            prev = prev.next
        
        node = prev.next
        prev.next = node.next
        node.next = None
        self.size -= 1
        return node.e
        
    def removeFirst(self):
        return self.remove(0)
    
    def removeLast(self):
        return self.remove(self.size - 1)


# 栈顶就是链表头节点
class Stack:
    def __init__(self):
        self._list = LinkedList()
        
    def getSize(self):
        return self._list.getSize()

    def isEmpty(self):
        return self._list.isEmpty()

    def push(self,e):
        self._list.addFirst(e)
    
    def pop(self):
        return self._list.removeFirst()

    def peek(self):
        return self._list.getFirst()

    def travel(self):
        print("Stack: top",end=' ')
        self._list.travel()

# 链表实现队列
# 使用头指针作为队首负责删除元素，尾指针作为队尾负责插入元素
class Queue:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0
    
    def getSize(self):
        return self.size
    
    def isEmpty(self):
        return self.size == 0
        
    def enqueue(self, e):
        if self.tail:
            self.tail.next = Node(e)
            self.tail = self.tail.next
        else:
            self.head = Node(e)
            self.tail = self.head
        self.size += 1
        
    def dequeue(self):
        retNode = self.head
        self.head = self.head.next
        if not self.head:
            self.tail = None
        self.size -= 1
        retNode.next = None
        return retNode.e
            
    def getFront(self):
        if not self.isEmpty():
            return self.head.e

    def travel(self):
        print("Queue: front",end=' ')
        cur = self.head
        while cur:
            print(cur.e, end='->')
            cur = cur.next
        print("NULL tail") 
        
        

###################################################
                #LeetCode专题#
###################################################

class ListNode:
    def __init__(self, val):
        self.val = val
        self.next = None

'''
203. Remove all elements from a linked list of integers 
that have value val.
'''

def removeElements(head: ListNode, val: int):
    # 头节点单独处理，因为没有prev
    while (head is not None and head.val == val):
        node = head
        head = head.next
        node.next = None

    if (head is None):
        return None

    prev=head
    while (prev.next is not None):
        if (prev.next.val == val):
            node = prev.next
            prev.next = node.next
            node.next = None
        else:
            prev = prev.next

    return head

# 使用虚拟头节点
def removeElements2(self, head: ListNode, val: int) -> ListNode:
    dummyHead = ListNode(-1)
    dummyHead.next=head
    prev = dummyHead
    while (prev.next is not None):
        if (prev.next.val == val):
            node = prev.next
            prev.next = node.next
            node.next = None
        else: 
            prev = prev.next

    return head

# 使用递归求解
def removeElements3(self, head, val):
    if head is None:
        return None
    head.next = self.removeElements3(head.next, val)
    return head.next if head.val==val else head


'''
206.反转链表
'''
# 经分析可知需要三个指针prev, cur, next
def reverseList(head: ListNode) -> ListNode:
    prev = None
    cur = head
    # nex = head.next 
    while (cur):
        nex = cur.next
        cur.next = prev
        prev = cur
        cur = nex
    return prev

# 递归法
def reverseList2(head: ListNode) -> ListNode:
    if head is None or head.next is None:
        return head
    rhead = reverseList2(head.next)
    head.next.next = head
    head.next = None
    return rhead

    
'''        
92. 反转链表II
反转从位置 m 到 n 的链表。请使用一趟扫描完成反转。
说明: 1 ≤ m ≤ n ≤ 链表长度。
'''
def reverseBetween(head: ListNode, m: int, n: int) -> ListNode:
    prev = None
    cur = head
    for _ in range(m - 1):
        prev = cur
        cur = cur.next
    node1 = prev
    node2 = cur
    prev = cur
    cur = cur.next
    for _ in range(n - m):
        nex = cur.next
        cur.next = prev
        prev = cur
        cur = nex
    if node1:
        node1.next = prev
    if node2:
        node2.next = cur
    return head if node1 else prev


def reverseBetween2(head: ListNode, m: int, n: int) -> ListNode:
    dummyHead = ListNode(-1)
    dummyHead.next=head
    prev = dummyHead
    for _ in range(m - 1):
        prev = prev.next
    tail = prev.next
    prev.next = reverse(prev.next, n - m)
    tail.next = left
    ret = dummyHead.next
    del dummyHead
    return ret

def reverse(head, index):
    if index == 0:
        global left
        left = head.next
        return head
    ret = reverse(head.next, index - 1)
    head.next.next = head
    return ret


def reverseBetween2(head: ListNode, m: int, n: int) -> ListNode:
    dummyHead = ListNode(-1)
    dummyHead.next=head
    prev = dummyHead
    for _ in range(m - 1):
        prev = prev.next
    tail = prev.next
    left = tail
    prev.next = reverse2(prev.next, n - m)
    if (tail != left):
        tail.next = left
    ret = dummyHead.next
    del dummyHead
    return ret

def reverse2(head, index):
    global left
    if (head is None or head.next is None or index==0):
        return head
    prev = head
    cur = head.next
    while (index):
        nex = cur.next
        cur.next = prev
        prev = cur
        cur = nex
        index -= 1
    left = cur
    return prev
        


'''
82. Remove Duplicates from Sorted ListII
给定一个排序链表，删除所有含有重复数字的节点，只保留原始链表中
没有重复出现的数字。
'''
def deleteDuplicates(self, head: ListNode) -> ListNode:
    dummyHead = ListNode(-1)
    dummyHead.next = head
    prev = dummyHead
    cur = head
    while (cur):
        num = 0
        p = cur
        while (p and p.val == cur.val):
            num += 1
            p = p.next
        if (num > 1):
            prev.next = p
        else:
            prev = cur
        cur = p
    return dummyHead.next


'''      
83. Remove Duplicates from Sorted List
给定一个排序链表，删除所有重复的元素，使得每个元素只出现一次
'''
def deleteDuplicates2(self, head):
    cur = head
    while (cur):
        num = 0
        p = cur
        while (p and p.val == cur.val):
            num += 1
            p = p.next
        if (num > 1):
            cur.next = p
        cur = p
    return head

'''
86. Partition List
给定一个链表和一个特定值 x，对链表进行分隔，使得所有小于 x 的节点都在大于或等于 x 
的节点之前。
'''
def partition(self, head: ListNode, x: int) -> ListNode:
    dummyHead1 = ListNode(-1)
    dummyHead2 = ListNode(-1)
    cur = head
    p1 = dummyHead1
    p2 = dummyHead2
    while (cur):
        if (cur.val < x):
            p1.next = cur
            cur = cur.next
            p1 = p1.next
        else:
            p2.next = cur
            cur = cur.next
            p2 = p2.next
    p2.next = None
    p1.next = dummyHead2.next
    ret = dummyHead1.next
    return ret

        

        


'''
328. Odd Even Linked List
'''
def oddEvenList(head):
    if head is None or head.next is None or head.next.next is None:
        return head
    dummyHead1 = ListNode(-1)
    dummyHead2 = ListNode(-2)
    p1 = dummyHead1
    p2 = dummyHead2
    p = head
    i = 0
    while p:
        if i % 2==0:
            p1.next = p
            p = p.next
            p1 = p1.next
        else:
            p2.next = p
            p = p.next
            p2 = p2.next  
        i += 1
    p1.next = None
    p2.next = None
    p1.next = dummyHead2.next
    ret = dummyHead1.next
    del dummyHead1
    del dummyHead2
    return ret
    
'''
一个链表，奇数位升序，偶数位降序，让链表变成升序的
''' 

def merge2(a, b):
    dummyHead = ListNode(-1)
    p1 = a
    p2 = b
    p = dummyHead
    while (p1 and p2):
        if (p1.val < p2.val):
            p.next = p1
            p1 = p1.next
            p = p.next
            p.next = None
        else:
            p.next = p2
            p2 = p2.next
            p = p.next
            p.next = None
    if p1:
        p.next = p1
    if p2:
        p.next = p2
    ret = dummyHead.next
    del dummyHead
    return ret

def splitOddEven(head):
    if head is None or head.next is None or head.next.next is None:
            return head
    dummyHead1 = ListNode(-1)
    dummyHead2 = ListNode(-2)
    p1 = dummyHead1
    p2 = dummyHead2
    p = head
    i = 0
    while p:
        if i % 2==0:
            p1.next = p
            p = p.next
            p1 = p1.next
        else:
            p2.next = p
            p = p.next
            p2 = p2.next  
        i += 1
    p1.next = None
    p2.next = None
    return dummyHead1.next, dummyHead2.next

def reverseList3(head: ListNode) -> ListNode:
    if head is None or head.next is None:
        return head
    rhead = reverseList3(head.next)
    head.next.next = head
    head.next = None
    return rhead

def OddIncreaseEvenDecrease(head):
    head1,head2 = splitOddEven(head)
    head2 = reverse3(head2)
    head = merge(head1, head2)
    return head

        


'''
Given a singly linked list, determine if it is a palindrome.
'''
def isPalindrome(head):
    if (head is None or head.next is None):
        return True
    slow, fast = head, head
    while (fast.next and fast.next.next):
        slow = slow.next
        fast = fast.next.next
    slow = reverse3(slow.next)
    cur = head
    while (slow):
        if cur.val != slow.val:
            return False
        else:
            slow = slow.next
            cur = cur.next
    return True

def reverse3(head):
    if head is None or head.next is None:
        return head
    prev = None
    cur = head
    while (cur):
        nex = cur.next
        cur.next = prev
        prev = cur
        cur = nex
    return prev


'''
141. Given a linked list, determine if it has a cycle in it. To represent a 
cycle in the given linked list, we use an integer pos which represents the 
position (0 - indexed) in the linked list where tail connects to. If pos 
is - 1, then there is no cycle in the linked list.
'''
#就是检测有没有重复值
def hasCycle(head):
    if head is None:
        return False
    table = set()
    cur = head
    while cur:
        if cur in table:
            return True
        else:
            table.append(cur)
        cur = cur.next
    return False

'''
142. Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
To represent a cycle in the given linked list, we use an integer pos which 
represents the position (0-indexed) in the linked list where tail connects to. 
If pos is -1, then there is no cycle in the linked list. Note: Do not modify the linked list.
'''
def detectCycle(head):
    if head is None:
        return None
    records = set()
    cur = head
    while cur:
        if cur in table:
            return cur
        else:
            records.add(cur)
        cur = cur.next
    return None


'''
Sort List
'''
# 归并排序
def sortList(head):
    if head is None or head.next is None:
        return head
    slow = head
    fast = head
    while (fast.next and fast.next.next):
        slow = slow.next
        fast = fast.next.next
    head2 = slow.next
    slow.next = None
    head=sortList(head)
    head2=sortList(head2)
    return merge(head, head2)

def merge(a, b):
    dummyHead = ListNode(-1)
    p1 = a
    p2 = b
    p = dummyHead
    while (p1 and p2):
        if (p1.val < p2.val):
            p.next = p1
            p1 = p1.next
            p = p.next
            p.next = None
        else:
            p.next = p2
            p2 = p2.next
            p = p.next
            p.next = None
    if p1:
        p.next = p1
    if p2:
        p.next = p2
    ret = dummyHead.next
    del dummyHead
    return ret
    


    

def creatLinkedList(arr) -> ListNode:
    n = len(arr)
    if n == 0:
        return None
    dummyHead = ListNode(-1)
    prev = dummyHead
    for i in range(n):
        node = ListNode(arr[i])
        prev.next = node
        prev = prev.next
    return dummyHead.next


def printLinkedList(head):
    cur = head
    while cur:
        print(cur.val, end=' -> ')
        cur = cur.next
    print("NULL")
    return 
    

def deleteLinkedList(head):
    cur = head
    while cur:
        delNode = cur
        cur = cur.next
        del delNode





# 对链表进行测试
if __name__=="__main__":
    # l = Stack()
    # for i in range(5):
    #     l.push(i)
    #     l.travel()
    # l.pop()
    # l.travel()
    # l.add(2, 666)
    # l.travel()
    # l.remove(2)
    # l.travel()
    # l.removeFirst()
    # l.travel()
    # l.removeLast()
    # l.travel()
    # q = Queue()
    # for i in range(10):
    #     q.enqueue(i)
    #     q.travel()
    #     if (i % 3 == 2):
    #         q.dequeue()
    #         q.travel()
    

    # 根据数组创建链表进行测试
    arr = [1,8,3,6,5,4,7,2,9]
    head = creatLinkedList(arr)
    # printLinkedList(head)
    ret=OddIncreaseEvenDecrease(head)
    printLinkedList(ret)
    # print(isPalindrome(head))
    # rhead = reverseBetween2(head,2,4)
    # rethead= reverseList2(head)
    # printLinkedList(rhead)


    
        

        
        

        

