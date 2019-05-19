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

'''
98. Validate Binary Search Tree
Given a binary tree, determine if it is a valid binary search tree (BST).
'''
import sys
MIN = sys.maxsize
MAX = -sys.maxsize - 1

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



    