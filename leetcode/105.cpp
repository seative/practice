// 给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历，
// inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

// 示例 1:

// 输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
// 输出: [3,9,20,null,null,15,7]
// 示例 2:

// 输入: preorder = [-1], inorder = [-1]
// 输出: [-1]

#include <algorithm>
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

class Solution {
 public:
  TreeNode *buildTree(int pre_l, int pre_r, int in_l, int in_r,
                      vector<int> &preorder, vector<int> &inorder) {
    if (pre_l > pre_r) return nullptr;

    int n = std::find(inorder.begin() + in_l, inorder.begin() + in_r,
                      preorder[pre_l]) -
            inorder.begin();

    auto leftTree =
        buildTree(pre_l + 1, pre_l + n - in_l, in_l, n - 1, preorder, inorder);
    auto rightTree =
        buildTree(pre_l + n - in_l + 1, pre_r, n + 1, in_r, preorder, inorder);
    return new TreeNode(preorder[pre_l], leftTree, rightTree);
  }

  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    if (preorder.size() == 0) return nullptr;
    int n = preorder.size();
    return buildTree(0, n - 1, 0, n - 1, preorder, inorder);
  }
};