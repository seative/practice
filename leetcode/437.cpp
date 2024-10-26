// 给定一个二叉树的根节点 root ，和一个整数 targetSum
// ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

// 路径
// 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

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

class Solution {
 public:
  int count = 0;
  // void buildSumTree(TreeNode* root,TreeNode * sumroot)
  // {
  //     if(root==nullptr) return ;

  //     if(root->left!=nullptr)
  //     {
  //         sumroot->left=new TreeNode(root->left->val+sumroot->val);
  //         buildSumTree(root->left,sumroot->left);
  //     }
  //     if(root->right!=nullptr)
  //     {
  //         sumroot->right=new TreeNode(root->right->val+sumroot->val);
  //         buildSumTree(root->right,sumroot->right);
  //     }
  // }

  void findTarget(TreeNode* root, long targetSum, int& count) {
    if (root == nullptr) return;
    int val = root->val;
    if (val == targetSum) count += 1;
    findTarget(root->left, targetSum - val, count);
    findTarget(root->right, targetSum - val, count);
  }

  int pathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) return 0;
    // TreeNode * sumTreeRoot=new TreeNode(root->val);;
    // buildSumTree(root,sumTreeRoot);l
    findTarget(root, targetSum, count);
    pathSum(root->left, targetSum);
    pathSum(root->right, targetSum);
    return count;
  }
};

#include <unordered_map>
// 前缀和+回溯 优化
class Solution2 {
 public:
  std::unordered_map<long long, int> prefix;

  int dfs(TreeNode* root, long long curr, int targetSum) {
    if (!root) {
      return 0;
    }

    int ret = 0;
    curr += root->val;
    if (prefix.count(curr - targetSum)) {
      ret = prefix[curr - targetSum];
    }

    prefix[curr]++;
    ret += dfs(root->left, curr, targetSum);
    ret += dfs(root->right, curr, targetSum);
    prefix[curr]--;

    return ret;
  }

  int pathSum(TreeNode* root, int targetSum) {
    prefix[0] = 1;
    return dfs(root, 0, targetSum);
  }
};