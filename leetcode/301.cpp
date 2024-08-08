// 301. 删除无效的括号
// 困难
// 相关标签
// 相关企业
// 提示
// 给你一个由若干括号和字母组成的字符串 s
// ，删除最小数量的无效括号，使得输入的字符串有效。

// 返回所有可能的结果。答案可以按 任意顺序 返回。

// 示例 1：

// 输入：s = "()())()"
// 输出：["(())()","()()()"]
// 示例 2：

// 输入：s = "(a)())()"
// 输出：["(a())()","(a)()()"]
// 示例 3：

// 输入：s = ")("
// 输出：[""]

// 提示：

// 1 <= s.length <= 25
// s 由小写英文字母以及括号 '(' 和 ')' 组成
// s 中至多含 20 个括号

#include <string>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<string> res;
  vector<string> removeInvalidParentheses(string s) {
    int lremove = 0;
    int rremove = 0;

    for (char c : s) {
      if (c == '(') {
        lremove++;
      } else if (c == ')') {
        if (lremove == 0) {
          rremove++;
        } else {
          lremove--;
        }
      }
    }
    helper(s, 0, lremove, rremove);
    return res;
  }

  void helper(string str, int start, int lremove, int rremove) {
    if (lremove == 0 && rremove == 0) {
      if (isValid(str)) {
        res.push_back(str);
      }
      return;
    }
    for (int i = start; i < str.size(); i++) {
      if (i != start && str[i] == str[i - 1]) {
        continue;
      }
      // 如果剩余的字符无法满足去掉的数量要求，直接返回
      if (lremove + rremove > str.size() - i) {
        return;
      }
      // 尝试去掉一个左括号
      if (lremove > 0 && str[i] == '(') {
        helper(str.substr(0, i) + str.substr(i + 1), i, lremove - 1, rremove);
      }
      // 尝试去掉一个右括号
      if (rremove > 0 && str[i] == ')') {
        helper(str.substr(0, i) + str.substr(i + 1), i, lremove, rremove - 1);
      }
    }
  }

  inline bool isValid(const string& str) {
    int cnt = 0;

    for (int i = 0; i < str.size(); i++) {
      if (str[i] == '(') {
        cnt++;
      } else if (str[i] == ')') {
        cnt--;
        if (cnt < 0) {
          return false;
        }
      }
    }

    return cnt == 0;
  }
};