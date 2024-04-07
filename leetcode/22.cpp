// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且
// 有效的 括号组合。

// 示例 1：

// 输入：n = 3
// 输出：["((()))","(()())","(())()","()(())","()()()"]
// 示例 2：

// 输入：n = 1
// 输出：["()"]

// 提示：

// 1 <= n <= 8
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  vector<string> generateParenthesis(int n) {
    int left = n;
    int right = n;

    vector<string> ans;
    string temp;
    backTrack(ans, temp, left, right);
    return ans;
  }

  void backTrack(vector<string> &result, string &str, int left, int right) {
    if (left == 0 && right == 0) {
      result.push_back(str);
      return;
    }

    if (left > 0) {
      str.push_back('(');
      backTrack(result, str, left - 1, right);
      str.pop_back();
    }
    if (left < right) {
      str.push_back(')');
      backTrack(result, str, left, right - 1);
      str.pop_back();
    } else {
      return;
    }
  }
};