// 给定一个二叉树 root ，返回其最大深度。

// 二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。

// 示例 1：

// 输入：root = [3,9,20,null,null,15,7]
// 输出：3
// 示例 2：

// 输入：root = [1,null,2]
// 输出：2

// 提示：

// 树中节点的数量在 [0, 104] 区间内。
// -100 <= Node.val <= 100

#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

// 暴力解法 时间限制
class Solution {
 public:
  int maxDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    if (root->left == nullptr) return 1 + maxDepth(root->right);
    if (root->right == nullptr) return 1 + maxDepth(root->left);
    return maxDepth(root->left) > maxDepth(root->right)
               ? maxDepth(root->left) + 1
               : maxDepth(root->right) + 1;
  }
};

class Solution2 {
 public:
  int maxDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) return 1;
    if (root->left == nullptr) return 1 + maxDepth(root->right);
    if (root->right == nullptr) return 1 + maxDepth(root->left);

    int leftMax = maxDepth(root->left);
    int rightMax = maxDepth(root->right);
    return leftMax > rightMax ? leftMax + 1 : rightMax + 1;
  }
};

// 暴力解法 做了一些修改，少了一些递归
class Solution3 {
 public:
  int maxDepth(TreeNode *root) {
    if (root == nullptr) return 0;
    int leftMax = maxDepth(root->left);
    int rightMax = maxDepth(root->right);
    return leftMax > rightMax ? leftMax + 1 : rightMax + 1;
  }
};