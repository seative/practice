// 给你二叉树的根结点 root ，请你将它展开为一个单链表：

// 展开后的单链表应该同样使用 TreeNode ，其中 right
// 子指针指向链表中下一个结点，而左子指针始终为 null 。
// 展开后的单链表应该与二叉树 先序遍历 顺序相同。

// 示例 1：

// 输入：root = [1,2,5,3,4,null,6]
// 输出：[1,null,2,null,3,null,4,null,5,null,6]
// 示例 2：

// 输入：root = []
// 输出：[]
// 示例 3：

// 输入：root = [0]
// 输出：[0]

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
  void flatten(TreeNode *root) {
    vector<TreeNode *> l;
    preorderTraversal(root, l);
    int n = l.size();
    for (int i = 1; i < n; i++) {
      TreeNode *prev = l.at(i - 1), *curr = l.at(i);
      prev->left = nullptr;
      prev->right = curr;
    }
  }

  void preorderTraversal(TreeNode *root, vector<TreeNode *> &l) {
    if (root != NULL) {
      l.push_back(root);
      preorderTraversal(root->left, l);
      preorderTraversal(root->right, l);
    }
  }
};

// O1 空间复杂度的解法
class Solution2 {
 public:
  void flatten(TreeNode *root) {
    TreeNode *curr = root;
    while (curr != nullptr) {
      if (curr->left != nullptr) {
        auto next = curr->left;
        auto predecessor = next;
        while (predecessor->right != nullptr) {
          predecessor = predecessor->right;
        }
        predecessor->right = curr->right;
        curr->left = nullptr;
        curr->right = next;
      }
      curr = curr->right;
    }
  }
};