// 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

// 百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点
// p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x
// 的深度尽可能大（一个节点也可以是它自己的祖先）。”

// 示例 1：

// 输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
// 输出：3
// 解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
// 示例 2：

// 输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
// 输出：5
// 解释：节点 5 和节点 4 的最近公共祖先是节点 5
// 。因为根据定义最近公共祖先节点可以为节点本身。 示例 3：

// 输入：root = [1,2], p = 1, q = 2
// 输出：1

#include <queue>
#include <unordered_map>
#include <vector>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 自顶向下递归
class Solution {
 public:
  bool find_node(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == NULL) return false;
    if (root == p || root == q) return true;
    return find_node(root->right, p, q) || find_node(root->left, p, q);
  }
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == p || root == q) return root;
    bool left_find = find_node(root->left, p, q);
    bool right_find = find_node(root->right, p, q);
    if (left_find && right_find) return root;
    if (right_find == false) return lowestCommonAncestor(root->left, p, q);
    return lowestCommonAncestor(root->right, p, q);
  }
};

// 自底向上递归
class Solution1 {
 public:
  TreeNode* ans;
  bool dfs(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr) return false;
    bool lson = dfs(root->left, p, q);
    bool rson = dfs(root->right, p, q);
    if ((lson && rson) ||
        ((root->val == p->val || root->val == q->val) && (lson || rson))) {
      ans = root;
    }
    return lson || rson || (root->val == p->val || root->val == q->val);
  }
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    dfs(root, p, q);
    return ans;
  }
};

class Solution2 {
  std::unordered_map<int, TreeNode*> parent;
  std::unordered_map<int, bool> visited;
  std::queue<TreeNode*> que;

 public:
  void dfs(TreeNode* root) {
    if (root->left != nullptr) {
      parent[root->left->val] = root;
      dfs(root->left);
    }
    if (root->right != nullptr) {
      parent[root->right->val] = root;
      dfs(root->right);
    }
  }

  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    parent[root->val] = nullptr;
    dfs(root);
    while (p != nullptr) {
      visited[p->val] = true;
      p = parent[p->val];
    }
    while (q != nullptr) {
      if (visited[q->val]) return q;
      q = parent[q->val];
    }
    return nullptr;
  }
};