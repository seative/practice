// 小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。

// 除了 root
// 之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。
// 如果 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。

// 给定二叉树的 root 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。

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

#include <cmath>
#include <map>

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
  int rob(TreeNode *root) {
    auto [not_rob, rob] = dp(root);
    return max(not_rob, rob);
  }

  std::pair<int, int> dp(TreeNode *root) {
    
    if (root == nullptr) return {0, 0};
    if (root->left == nullptr && root->right == nullptr) return {root->val, 0};

    auto [left_rob, left_not_rob] = dp(root->left);
    auto [right_rob, right_not_rob] = dp(root->right);

    int not_rob = max(left_rob, left_not_rob) + max(right_rob, right_not_rob);
    int rob = root->val + left_not_rob + right_not_rob;
    return {rob, not_rob};
  }
};