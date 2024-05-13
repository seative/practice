// 给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。

// 示例 1：

// 输入：root = [1,null,2,3]
// 输出：[1,3,2]
// 示例 2：

// 输入：root = []
// 输出：[]
// 示例 3：

// 输入：root = [1]
// 输出：[1]

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
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

// 递归
class Solution {
 public:
  vector<int> inorderTraversal(TreeNode *root) {
    vector<int> ans;
    inorderTraversal(ans, root);
    return ans;
  }

  void inorderTraversal(vector<int> &ans, TreeNode *root) {
    if (root == nullptr) return;
    inorderTraversal(ans, root->left);
    ans.emplace_back(root->val);
    inorderTraversal(ans, root->right);
  }
};

// 栈
class Solution2 {
 public:
  vector<int> inorderTraversal(TreeNode *root) {
    vector<int> res;
    stack<TreeNode *> stk;
    while (root != nullptr || !stk.empty()) {
      while (root != nullptr) {
        stk.push(root);
        root = root->left;
      }
      root = stk.top();
      stk.pop();
      res.push_back(root->val);
      root = root->right;
    }
    return res;
  }
};

// Morris 中序遍历
class Solution3 {
 public:
  vector<int> inorderTraversal(TreeNode *root) {
    vector<int> res;
    TreeNode *predecessor = nullptr;

    while (root != nullptr) {
      if (root->left != nullptr) {
        // predecessor 节点就是当前 root
        // 节点向左走一步，然后一直向右走至无法走为止
        predecessor = root->left;
        while (predecessor->right != nullptr && predecessor->right != root) {
          predecessor = predecessor->right;
        }

        // 让 predecessor 的右指针指向 root，继续遍历左子树
        if (predecessor->right == nullptr) {
          predecessor->right = root;
          root = root->left;
        }
        // 说明左子树已经访问完了，我们需要断开链接
        else {
          res.push_back(root->val);
          predecessor->right = nullptr;
          root = root->right;
        }
      }
      // 如果没有左孩子，则直接访问右孩子
      else {
        res.push_back(root->val);
        root = root->right;
      }
    }
    return res;
  }
};

// 颜色标记法
class Solution4 {
 public:
  vector<int> inorderTraversal(TreeNode *root) {
    vector<int> result;
    stack<pair<TreeNode *, int> > stk;
    stk.push((make_pair(root, 0)));

    while (!stk.empty()) {
      auto [node, type] = stk.top();
      stk.pop();
      if (node == nullptr) continue;
      if (type == 0) {
        stk.push(make_pair(node->right, 0));
        stk.push(make_pair(node, 1));
        stk.push(make_pair(node->left, 0));
      } else
        result.emplace_back(node->val);
    }

    return result;
  }
};