"Binary Search Tree"
class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.left = None
        self.right = None
    
#增(insert)、删(remove)、改/查（search）
class BST:
    def __init__(self):
        self.root = None
        self.count = 0
        
    def size(self):
        return self.count

    def isEmpty(self):
        return self.root == None
    
    def insert(self, key, value):
        self.root = self._insert(self.root, key, value)
    
    def _insert(self, node, key, value):
        if node is None:
            self.count += 1
            return Node(key,value)
        if node.key == key:
            node.value = value
        elif node.key < key:
            node.right = self._insert(node.right, key, value)
        else:
            node.left = self._insert(node.left, key, value)
        return node

    def __setitem__(self, key, value):
        self.insert(key, value)

    def contain(self, key):
        return self._contain(self.root, key)

    def _contain(self, node, key):
        if node is None:
            return False
        if key == node.key:
            return True
        elif key > node.key:
            return self._contain(node.right, key)
        else:
            return self._contain(node.left, key)
    
    def search(self, node, key):
        if node is None:
            return None
        if node.key == key:
            return node.value
        elif node.key > key:
            return self.search(node.left, key)
        else:
            return self.search(node.right, key)

    def __getitem__(self, key):
        return self.search(self.root, key)
        
    def preOrder(self):
        self._preOrder(self.root)

    def _preOrder(self, node):
        if node:
            print(node.key)
            self._preOrder(node.left)
            self._preOrder(node.right)
    
    def inOrder(self):
        return self._inOrder(self.root)

    def _inOrder(self, node):
        if node:
            self._inOrder(node.left)
            print(node.key)
            self._inOrder(node.right)

    def postOrder(self):
        return self._postOrder(self.root)

    def _postOrder(self, node):
        if node:
            self._postOrder(node.left)
            self._postOrder(node.right)
            print(node.key)

    def levelOrder(self):
        from collections import deque
        q = deque()
        q.append(self.root)
        while q:
            node = q.popleft()
            if (node.left):
                q.append(node.left)
            if (node.right):
                q.append(node.right)
            print(node.key)

    def MinNode(self, node):
        if node.left is None:
            return node
        return self.MinNode(node.left)

    def removeMin(self):
        if self.root:
            self.root = self._removeMin(self.root)
    
    def _removeMin(self, node):
        if node.left is None:
            rightNode = node.right
            self.count -= 1
            del node
            return rightNode
        node.left = self._removeMin(node.left)
        return node

    def remove(self, key):
        if self.root:
            self.root = self._remove(self.root, key)
    
    def _remove(self, node, key):
        if node.key < key:
            node.right = self._remove(node.right, key)
            return node
        elif node.key > key:
            node.left = self._remove(node.left, key)
            return node
        else:
            import copy
            if (node.left is None):
                rightNode=node.right
                self.count -= 1
                del node
                return rightNode
            if (node.right is None):
                leftNode=node.left
                self.count -= 1
                del node
                return leftNode
            s = copy.deepcopy(self.MinNode(node.right))
            s.left = node.left
            s.right = self._removeMin(node.right)
            del node
            return s
            
                            


#######################################################
                ##LeetCode专题##
#######################################################
# 递归（链表，树）的关键：1.终止条件 2.返回值是什么 3.单步操作怎么写

'''
98. Validate Binary Search Tree
Given a binary tree, determine if it is a valid binary search tree (BST).
'''
import sys
MAX = sys.maxsize
MIN = -sys.maxsize - 1

def isValidBST(root):
    return _ValidBST(root,MIN,MAX)

def isValidBST(self, root, minval, maxval) -> bool:
    if root is None:
        return True
    if root.val < minval or root.val > maxval:
        return False
    if root.left is not None and root.val <= root.left.val:
        return False
    if root.right is not None and root.val >= root.right.val:
        return False
    return isValidBST(root.left, minval, root.val) and isValidBST(root.right, root.val, maxval)
    


# 使用中序遍历
def isValidBST(root):
    vec = []
    inorder(root，vec)
    for i in range(1, len(vec)):
        if vec[i-1] >= vec[i]:
            return False
    return True

def inorder(root, vec):
    if root is not None:
        inorder(root.left, vec)
        vec.append(root.val)
        inorder(root.right,vec)


'''
102. Binary Tree Level Order Traversal
Given a binary tree, return the level order traversal of its nodes' values. 
(ie, from left to right, level by level).
'''
from collections import deque
def levelOrder(self, root: TreeNode) -> List[List[int]]:
    if root is None:
        return []
    q = deque()
    q.append(root)
    level = 1
    ret = []
    while q:
        tmp = []
        new_level = 0
        for _ in range(level):
            node = q.popleft()
            if node.left:
                q.append(node.left)
                new_level += 1
            if node.right:
                q.append(node.right)
                new_level += 1
            tmp.append(node.val)
        ret.append(tmp)
        level = nwe_level
    return ret


def levelOrder(self, root: TreeNode) -> List[List[int]]:
    if root is None:
        return []
    q = deque()
    q.append((root,0))
    ret = []
    while q:
        node, level = q.popleft()
        if level == len(ret):
            ret.append([])
        ret[level].append(node.val)
        if node.left:
            q.append((node.left,level+1))
        if node.right:
            q.append((node.right,level+1))
    return ret      
    

'''
104. Maximum Depth of Binary Tree
Given a binary tree, find its maximum depth.
The maximum depth is the number of nodes along the longest path
from the root node down to the farthest leaf node.
'''
def maxDepth(self, root: TreeNode) -> int:
    if node is None:
        return 0
    return max(maxDepth(root.left), maxDepth(root.right)) + 1        

'''
226. Invert Binary Tree
'''
def invertTree(self, root: TreeNode) -> TreeNode:
    if root is None:
        return None
    root.left, root.right = root.right, root.left
    root.left = invertTree(root.left)
    root.right = invertTree(root.right)
    return root
    

'''
110. Balanced Binary Tree
Given a binary tree, determine if it is height-balanced.
For this problem, a height-balanced binary tree is defined as:
a binary tree in which the depth of the two subtrees of every node never
differ by more than 1.
'''
def isBalanced(root: TreeNode) -> bool:
    if root is None:
        return True
    if not isBalanced(root.left) or not isBalanced(root.right):
        return False
    if abs(height(root.left) - height(root.right)) > 1:
        return False
    return True
    
def height(root):
    if root is None:
        return 0
    return max(height(root.left), height(root.right)) + 1
    

'''
108.Convert Sorted Array to Binary Search Tree
Given an array where elements are sorted in ascending order,
convert it to a height balanced BST.
'''
def sortedArrayToBST(nums):
    if nums is None:
        return None
    return buildTree(nums, 0, len(nums) - 1)

def buildTree(nums, l, r):
    if l > r:
        return None
    if l == r:
        return TreeNode(nums[l])
    mid = (l + r) // 2
    root = TreeNode(nums[mid])
    root.left = buildTree(nums, l, mid - 1)
    root.right = buildTree(nums, mid + 1, r)
    return root
    
'''
230. Kth Smallest Element in a BST
'''
# inorder travel
def kthSmallest(self, root: TreeNode, k: int) -> int:
    if root is None:
        return None
    self.index=0
    return self.inorder(root,k).val

def inorder(self,node,k):
    if node is not None:
        # 保证不能返回空啊
        res=self.inorder(node.left,k)
        if res:
            return res
        self.index += 1
        if k == self.index:
            return node
        return self.inorder(node.right, k)

'''
105. Construct Binary Tree from Preorder and Inorder Traversal
Given preorder and inorder traversal of a tree, construct the binary tree.
'''
def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
    buildTree2(preorder, 0, len(preorder), inorder, 0, len(preorder))
    return root
    
def buildTree2(preorder, pl, pr, inorder, il, ir):
    if il >= ir:
        return None
    root = TreeNode(preorder[pl])
    rootPos = inorder[il:ir].index(root.val) + il
    num_left = rootPos - il
    num_right = ir - rootPos - 1
    root.left = buildTree2(preorder, pl + 1, num_left + pl + 1, inorder, il, rootPos)
    root.right = buildTree2(preorder, num_left + pl + 1, pr, inorder, rootPos + 1, ir)
    return root

'''
112. Path Sum
Given a binary tree and a sum, determine if the tree has a root-to-leaf path 
such that adding up all the values along the path equals the given sum.
'''
# 递归
def hasPathSum(root: TreeNode, sum: int) -> bool:
    if root is None:
        return False
    if (not root.left and not root.right):
        return root.val == sum

    return hasPathSum(root.left,sum-root.val) or hasPathSum(root.right,sum-root.val)

# 非递归，使用Stack
def hasPathSum(root, sum):
    if not root:
        return False
    stack = []
    stack.append((root, sum))
    while stack:
        cur, sum = stack.pop()
        if sum == cur.val and not cur.left and not cur.right:
            return True
        if cur.left:
            stack.append((cur.left, sum - cur.val))
        if cur.right:
            stack.append((cur.right, sum - cur.val))
    return False
        

'''
113. Path SumII
Given a binary tree and a sum, find all root-to-leaf paths where each path's 
sum equals the given sum.
Note: A leaf is a node with no children.
'''
def pathSum(root: TreeNode, sum: int) -> List[List[int]]:
    if not root:
        return []
    res = []
    tres = []
    dfs(root, tres, 0, sum, res)
    return res

def dfs(root, tres, sum, res):
    tres.append(root.val)
    tsum += root.val
    if (not root.left and not root.right):
        if tsum == sum:
            res.append(tres[:])
    else:
        if root.left:
            dfs(root.left, tres, tsum, sum, res)
        if root.right:
            dfs(root.right, tres, tsum, sum, res)
    # 因为先遍历左边的，再遍历右边的，必须先把左边添加的给剔除掉，再
    # 去试右边的
    tres.pop()
    return 
    
    
'''
129. Sum Root to Leaf Numbers
Given a binary tree containing digits from 0-9 only, each root-to-leaf path 
could represent a number. An example is the root-to-leaf path 1->2->3 which 
represents the number 123. Find the total sum of all root-to-leaf numbers.
Note: A leaf is a node with no children.   
'''
def sumNumbers(self, root: TreeNode) -> int:
    if not root:
        return 0
    res = []
    tres = []
    dfs(root, tres, res)
    # 先找到所有的从root->leaf的路径，然后再加起来
    ret = sum([reduce(lambda x, y: x * 10 + y, i) for i in res])
    return ret 

def dfs(root, tres, res):
    tres.append(root.val)
    if (not root.left and not root.right):
            res.append(tres)
    else:
        if root.left:
            dfs(root.left, tres, res)
        if root.right:
            dfs(root.right, tres, res)
    tres.pop()


def sumNumbers2(self, root: TreeNode) -> int:
    if not root:
        return 0
    res=0
    dfs(root, 0, res)
    return res

def dfs(root, tnum, res):
    tnum = tnum * 10 + root.val
    if (not root.left and not root.right):
            res += tnum
    else:
        if root.left:
            dfs(root.left, tres, res)
        if root.right:
            dfs(root.right, tres, res)

'''
111. Minimum Depth of Binary Tree
Given a binary tree, find its minimum depth.
The minimum depth is the number of nodes along the shortest path from 
the root node down to the nearest leaf node.
Note: A leaf is a node with no children.
'''
res = sys.maxsize
def minDepth(root):
    if not root:
        return 0
    dfs(root, 1)
    return res

def dfs(root, d):
    if not root.left and not root.right:
        if d < res:
            res = d
    else:
        if root.left:
            dfs(root.left, d + 1)
        if root.right:
            dfs(root.right, d + 1)

# 递归
def minDepth(root):
    if not root:
        return 0
    if not root.left and not root.right:
        return 1
    res = sys.maxsize
    if root.left:
        res = min(res, minDepth(root.left) + 1)
    if root.right:
        res = min(res, minDepth(root.right) + 1)
    return res

# 非递归, Using stack
def minDepth(root):
    if not root:
        return 0
    stack = []
    stack.append((root, 1))
    res = sys.maxsize
    while stack:
        root, depth = stack.pop()
        if depth < res and not root.left and not root.right:
            res = depth
        if root.left:
            stack.append((root.left, depth + 1))
        if root.right:
            stack.append((root.right, depth + 1))
    return res

# 非递归，BFS
def minDepth(root):
    if not root:
        return 0
    queue = deque()
    queue.append((root, 1))
    while queue:
        root, d = queue.popleft()
        if not root.left and not root.right:
            return d
        else:
            if root.left:
                queue.append((root.left, d + 1))
            if root.right:
                queue.append((root.right, d + 1))

'''
490. The Maze
'''


"Test Case"
if __name__ == '__main__':
      
    bst = BST()
    # bst.insert(20, 'a')
    # bst.insert(30, 'b')
    # bst.insert(40, 'c')
    bst[20] = 'a'
    bst[34] = 'b'
    bst[10] = 'c'
    bst[17] = 'd'
    bst[1] = 'e'
    bst[54]='k'
    bst[10]='g'
    # print(bst[1])
    # bst.removeMin()
    # print(bst[17])
    # print(bst[34])
    # bst.preOrder()
    # bst.preOrder()
    print(bst.count)
    bst.levelOrder()
    bst.remove(1)
    bst.remove(34)
    bst.levelOrder()
    print(bst.count)
    print(bst[10])



    