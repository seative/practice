// 给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

// 有效 二叉搜索树定义如下：

// 节点的左子树
// 只包含 小于 当前节点的数。
// 节点的右子树只包含 大于 当前节点的数。
// 所有左子树和右子树自身必须也是二叉搜索树。

// 示例 1：

// 输入：root = [2,1,3]
// 输出：true
// 示例 2：

// 输入：root = [5,1,4,null,null,3,6]
// 输出：false
// 解释：根节点的值是 5 ，但是右子节点的值是 4 。

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

// class Solution {
//  public:
//   bool isValidBST(TreeNode *root) {
//     if (root->left == nullptr && root->right == nullptr) return true;

//     if (root->left == nullptr && root->right->val > root->val) return true;

//     if (root->right == nullptr && root->left->val < root->val) return true;

//     if (root->left->val >= root->val || root->right->val <= root->val)
//       return false;

//     return isValidBST(root->left) && isValidBST(root->right);
//   }
// };

class Solution {
 public:
  bool isValidBST(TreeNode *root) {
    stack<TreeNode *> stack;
    long long inorder = (long long)INT_MIN - 1;

    while (!stack.empty() || root != nullptr) {
      while (root != nullptr) {
        stack.push(root);
        root = root->left;
      }
      root = stack.top();
      stack.pop();
      // 如果中序遍历得到的节点的值小于等于前一个 inorder，说明不是二叉搜索树
      if (root->val <= inorder) {
        return false;
      }
      inorder = root->val;
      root = root->right;
    }
    return true;
  }
};