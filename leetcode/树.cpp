#include <iostream>
#include <vector>
#include <cassert>
#include <set>
#include <map>
#include <unordered_map>
using namespace std;

/*
104. Maximum Depth of Binary Tree
*/
struct TreeNode
{
    /* data */
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int maxDepth(TreeNode *root)
{
    if (root == NULL)
        return 0;
    return max(maxDepth(root->left) + 1, maxDepth(root->right) + 1);
}

/*
111. Minimum Depth of Binary Tree
*/

/*
226. Invert Binary Tree
*/

TreeNode *invertTree(TreeNode *root)
{
    if (root == NULL)
        return NULL;
    invertTree(root->left);
    invertTree(root->right);
    swap(root->left, root->right);

    return root;
}
