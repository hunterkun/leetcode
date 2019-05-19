#include <iostream>
#include <queue>
#include <cassert>
#include <vector>

using namespace std;
//Binary Search Tree
//查找 删除 插入的复杂度都是O(logN)
//定义： 1. 二叉树  2. 每个节点的值大于左孩子， 小于右孩子
//与堆不同，二分查找树不一定是完全二叉树
//二分查找树可以作为map数据结构背后的具体实现方法
template <class Key, class Value>
class BST
{
  private:
    struct Node
    {
        Key key;
        Value value;
        Node *left;
        Node *right;
        Node(Key key, Value value)
        {
            this->key = key;
            this->value = value;
            this->left = NULL;
            this->right = NULL;
        }
        Node(Node *node)
        {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }
    };
    Node *root;
    int count;

  public:
    BST()
    {
        root = NULL;
        count = 0;
    }
    //释放的时候，要顾及到左右两个子节点，需要采用后序遍历
    ~BST()
    {
        destroy(root);
    }
    int size()
    {
        return count;
    }
    bool isEmpty()
    {
        return root == NULL;
    }
    //返回插入新节点后的二叉搜索树的根
    void insert(Key key, Value value)
    {
        root = insert(root, key, value);
    }
    bool contain(Key key)
    {
        return contain(root, key);
    }
    /*search返回值讨论：
    如果返回的是Node，那么没有对外隐藏私有变量
    如果返回的是Value，那么当没有查找到时，C++不能直接返回空
    因此，可以返回Value*,当没查找到时，指针可以为空，同时用户还可以
    非常方便的修改这个元素
    */
    Value *search(Key key)
    {
        return search(root, key);
    }
    //深度优先遍历
    void preOrder()
    {
        preOrder(root);
    }
    void postOrder()
    {
        postOrder(root);
    }
    //广度优先遍历
    void levelOrder()
    {
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *node = q.front();
            q.pop();
            if (node->left != NULL)
            {
                q.push(root->left);
            }
            if (node->right != NULL)
                q.push(root->right);
            cout << node->key << endl;
        }
    }
    //寻找最小的键
    Key minimum()
    {
        assert(count != 0);
        Node *minNode = minimum(root);
        return minNode->key;
    }

    //寻找最大的键
    Key maximum()
    {
        assert(count != 0);
        Node *maxNode = maximum(root);
        return maxNode->key;
    }
    //删除操作，麻烦在于要处理左右子节点
    void removeMin()
    {
        if (root)
            root = removeMin(root);
    }

    void remove(Key key)
    {
        if (root)
            root = remove(root, key);
    }

  private:
    Node *remove(Node *node, Key key)
    {
        if (node == NULL)
            return NULL;
        if (node->key < key)
        {
            node->right = remove(node->right, key);
            return node;
        }
        else if (node->key > key)
        {
            node->left = remove(node->left, key);
            return node;
        }
        else //key==node->key
        {
            if (node->right == NULL)
            {
                Node *leftNode = node->left;
                delete leftnode;
                count--;
                return leftNode;
            }
            else if (node->left == NULL)
            {
                Node *rightNode = node->right;
                delete rightNode;
                count--;
                return rightNode;
            }
            else
            {
                //removeMin会使得s消失，所以要拷贝而不是简单赋值
                Node *s = new Node(minimum(node->right));
                count++;
                s->left = node->left;
                s->right = removeMin(node->right);
                delete node;
                count--;
                return s;
            }
        }
    }
    Node *removeMin(Node *node)
    {
        if (node->left == NULL)
        {
            Node *rightnode = node->right;
            delete node;
            count--;
            return rightnode;
        }
        node->left = removeMin(node->left);
        return node;
    }
    Node *minimum(Node *node)
    {
        if (node->left == NULL)
            return node;

        return minimum(node->left);
    }
    //插入操作的递归实现
    Node insert(Node *root, Key key, Value value)
    {
        if (root == NULL)
        {
            count++;
            return new Node(key, value);
        }
        if (root->key == key)
        {
            root->value = value;
        }

        else if (root->key < key)
        {
            root->right = insert(root->right, key, value);
        }
        else
            root->left = insert(root->left, key, value);

        return root;
    }
    //插入操作的非递归实现
    /*
     TO DO ....
    */

    bool contain(Node *node, Key key)
    {
        if (node == NULL)
            return false;
        if (node->key == key)
            return true;
        else if (node->key > key)
            return contain(node->left, key);
        else
        {
            return contain(node->right, key);
        }
    }

    Value *search(Node *node, Key key)
    {
        if (node == NULL)
            return NULL;
        if (node->key == key)
            return &(node->value);
        else if (node->key > value)
        {
            return search(node->left, key);
        }
        else
        {
            return search(node->right, key);
        }
    }

    void preOrder(Node *node)
    {
        if (node != NULL)
        {
            cout << node->key << endl;

            preOrder(node->left);
            preOrder(node->right);
        }
    }
    void postOrder(Node *node)
    {
        if (node != NULL)
        {
            preOrder(node->left);
            preOrder(node->right);
            cout << node->key << endl;
        }
    }
    void destory(Node *node)
    {
        if (node != NULL)
        {
            destory(node->left);
            destory(node->right);
            delete node;
            count--;
        }
    }
    Node *minimum(Node *node)
    {
        if (node->left)
            minimum(node->left);
        return node;
    }
    Node *maximum(Node *node)
    {
        if (node->right == NULL)
            return node;
        maximum(node->right);
    }
};

//SequenceST顺序查找表
template <class Key, class Value>
class SST
{
    // to do ...
};

//编写测试用例
int main()
{
    string filename = "bible.txt";
    vector<string> words;
    if (Fileops::readFile(filename, words))
    {
        cout << "There are totally" << words.size() << "words in" << filename;
        cout << endl;

        //test BST
        time_t startTime = clock();
        BST<string, int> bst = BST<string, int>();
        for (auto iter = words.begin(); iter != words.end(); iter++)
        {
            int *res = bst.search(*iter);
            if (res == NULL)
                bst.insert(*iter, 1);
            else:
                (*res)++;
        }
        cout << "'god" << endl;
    }
}