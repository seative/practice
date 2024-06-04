// 给你二叉树的根节点 root ，返回其节点值的 层序遍历 。
// （即逐层地，从左到右访问所有节点）。

// 示例 1：

// 输入：root = [3,9,20,null,null,15,7]
// 输出：[[3],[9,20],[15,7]]
// 示例 2：

// 输入：root = [1]
// 输出：[[1]]
// 示例 3：

// 输入：root = []
// 输出：[]

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
  vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> result;

    if (root == nullptr) return result;
    vector<TreeNode *> pre{root};
    vector<TreeNode *> path;

    while (!pre.empty()) {
      vector<int> layerRes;
      for (int i = 0; i < pre.size(); ++i) {
        if (pre[i]->left != nullptr) path.push_back(pre[i]->left);
        if (pre[i]->right != nullptr) path.push_back(pre[i]->right);
        layerRes.push_back(pre[i]->val);
      }
      result.push_back(layerRes);
      pre = std::move(path);
    }
  }
};

// 官方题解 BFS 思路类似 但是使用了队列
class Solution2 {
 public:
  vector<vector<int>> levelOrder(TreeNode *root) {
    queue<TreeNode *> que;
    vector<vector<int>> res;
    if (root != nullptr) que.push(root);
    while (!que.empty()) {
      vector<int> tmp;
      for (int i = que.size(); i > 0; --i) {
        root = que.front();
        que.pop();
        tmp.push_back(root->val);
        if (root->left != nullptr) que.push(root->left);
        if (root->right != nullptr) que.push(root->right);
      }
      res.push_back(tmp);
    }
    return res;
  }
};