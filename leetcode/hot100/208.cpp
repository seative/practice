// Trie（发音类似 "try"）或者说 前缀树
// 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

// 请你实现 Trie 类：

// Trie() 初始化前缀树对象。
// void insert(String word) 向前缀树中插入字符串 word 。
// boolean search(String word) 如果字符串 word 在前缀树中，返回
// true（即，在检索之前已经插入）；否则，返回 false 。 boolean startsWith(String
// prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true
// ；否则，返回 false 。

// 示例：

// 输入
// ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
// [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
// 输出
// [null, null, true, false, true, null, true]

// 解释
// Trie trie = new Trie();
// trie.insert("apple");
// trie.search("apple");   // 返回 True
// trie.search("app");     // 返回 False
// trie.startsWith("app"); // 返回 True
// trie.insert("app");
// trie.search("app");     // 返回 True

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 暴力解法
class Trie {
  struct TrieNode {
    std::unordered_map<char, TrieNode*> child;
    bool is_end = false;
  };

  TrieNode* root;

 public:
  Trie() { root = new TrieNode(); }

  void insert(string word) {
    TrieNode* node = root;
    for (auto c : word) {
      if (root->child.find(c) == root->child.end()) {
        root->child[c] = new TrieNode();
      }
      root = root->child[c];
    }
    root->is_end = true;
    root = node;
  }

  bool search(string word) {
    TrieNode* node = root;
    for (auto c : word) {
      if (node->child.find(c) == node->child.end()) {
        return false;
      }
      node = node->child[c];
    }
    return node->is_end;
  }

  bool startsWith(string prefix) {
    TrieNode* node = root;
    for (auto c : prefix) {
      if (node->child.find(c) == node->child.end()) {
        return false;
      }
      node = node->child[c];
    }
    return true;
  }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */