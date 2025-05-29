// 给你一棵二叉树的根节点，返回该树的 直径 。

// 二叉树的 直径 是指树中任意两个节点之间最长路径的 长度
// 。这条路径可能经过也可能不经过根节点 root 。

// 两节点之间路径的 长度 由它们之间边数表示。

// 示例 1：

// 输入：root = [1,2,3,4,5]
// 输出：3
// 解释：3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。
// 示例 2：

// 输入：root = [1,2]
// 输出：1

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

class Solution {
 public:
  int dimater = 0;

  int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    dimater = std::max(dimater, left + right);
    return std::max(left, right) + 1;
  }

  int diameterOfBinaryTree(TreeNode* root) {
    maxDepth(root);
    return dimater;
  }
};