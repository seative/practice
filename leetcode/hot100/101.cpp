// 给你一个二叉树的根节点 root ， 检查它是否轴对称。

// 示例 1：

// 输入：root = [1,2,2,3,4,4,3]
// 输出：true
// 示例 2：

// 输入：root = [1,2,2,null,3,null,3]
// 输出：false

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

class Solution {
 public:
  bool isEqual(TreeNode *left, TreeNode *right) {
    if (left == nullptr && right == nullptr) return true;
    if (left == nullptr || right == nullptr) return false;
    if (left->val != right->val) return false;

    return isEqual(left->right, right->left) &&
           isEqual(left->left, right->right);
  }
  bool isSymmetric(TreeNode *root) { return isEqual(root->left, root->right); }
};