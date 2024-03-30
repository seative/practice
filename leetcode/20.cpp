// 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

// 有效字符串需满足：

// 左括号必须用相同类型的右括号闭合。
// 左括号必须以正确的顺序闭合。
// 每个右括号都有一个对应的相同类型的左括号。

// 示例 1：

// 输入：s = "()"
// 输出：true
// 示例 2：

// 输入：s = "()[]{}"
// 输出：true
// 示例 3：

// 输入：s = "(]"
// 输出：false
#include <stack>
#include <string>
#include <unordered_map>
using namespace std;

// 暴力解法
class Solution {
 public:
  bool isValid(string s) {
    while (s.size() > 0) {
      if (s.find("()") != string::npos) {
        s.erase(s.find("()"), 2);
      } else if (s.find("[]") != string::npos) {
        s.erase(s.find("[]"), 2);
      } else if (s.find("{}") != string::npos) {
        s.erase(s.find("{}"), 2);
      } else {
        return false;
      }
    }
    return true;
  }
};

// 利用栈和哈希表
// 暴力解法
class Solution {
 public:
  bool isValid(string s) {
    std::unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'},
    };

    std::stack<char> stk;
    for (auto ch : s) {
      if (pairs.count(ch)) {
        if (stk.empty() || stk.top() != pairs[ch]) {
          return false;
        } else {
          stk.pop();
        }
      } else {
        stk.push(ch);
      }
    }
    return stk.empty();
  }
};