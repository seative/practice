// 给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater
// Sum Tree），使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

// 提醒一下，二叉搜索树满足下列约束条件：

// 节点的左子树仅包含键 小于 节点键的节点。
// 节点的右子树仅包含键 大于 节点键的节点。
// 左右子树也必须是二叉搜索树。
// 注意：本题和 1038:
// https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree/ 相同

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

// 先中序遍历再反序
class Solution {
 public:
  void inorder(TreeNode* root, std::vector<TreeNode*>& path) {
    if (root == nullptr) return;
    inorder(root->left, path);
    path.push_back(root);
    inorder(root->right, path);
  }

  // std::vector<TreeNode*> inorderStack(TreeNode * root)
  // {
  //     std::vector<TreeNode*> ans;
  //     std::stack<TreeNode*> stk;

  //     while(root!=nullptr|| !stk.empty())
  //     {
  //     while(root!=nullptr)
  //     {
  //         stk.push(root);
  //         root=root->left;
  //     }

  //     TreeNode *cur=stk.top();
  //     stk.pop();
  //     ans.push_back(cur);
  //     root=cur->right;
  //     }
  //     return ans;
  // }

  TreeNode* convertBST(TreeNode* root) {
    std::vector<TreeNode*> path;
    inorder(root, path);

    int preVal = 0;
    while (!path.empty()) {
      TreeNode* cur = path.back();
      path.pop_back();
      cur->val += preVal;
      preVal = cur->val;
    }

    return root;
  }
};

class Solution2 {
 public:
  int sum = 0;

  TreeNode* convertBST(TreeNode* root) {
    if (root != nullptr) {
      convertBST(root->right);
      sum += root->val;
      root->val = sum;
      convertBST(root->left);
    }
    return root;
  }
};