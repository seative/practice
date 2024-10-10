
// 给定一个经过编码的字符串，返回它解码后的字符串。

// 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k
// 次。注意 k 保证为正整数。

// 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

// 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k
// ，例如不会出现像 3a 或 2[4] 的输入。

// 示例 1：

// 输入：s = "3[a]2[bc]"
// 输出："aaabcbc"
// 示例 2：

// 输入：s = "3[a2[c]]"
// 输出："accaccacc"
// 示例 3：

// 输入：s = "2[abc]3[cd]ef"
// 输出："abcabccdcdcdef"
// 示例 4：

// 输入：s = "abc3[cd]xyz"
// 输出："abccdcdcdxyz"

// 提示：

// 1 <= s.length <= 30
// s 由小写英文字母、数字和方括号 '[]' 组成
// s 保证是一个 有效 的输入。
// s 中所有整数的取值范围为 [1, 300]

#include <stack>
#include <string>
using namespace std;

class Solution {
 public:
  string decodeString(string s) {
    string res;

    stack<char> stk;
    for (int i = 0; i < s.size(); ++i) {
      stk.push(s[i]);
      while (stk.top() == ']') {
        stk.pop();
        string temp;
        while (stk.top() != '[') {
          temp.push_back(stk.top());
          stk.pop();
        }
        stk.pop();

        string repeat;
        while (!stk.empty() && isdigit(stk.top())) {
          repeat.push_back(stk.top());
          stk.pop();
        }
        int count = stoi(string(repeat.rbegin(), repeat.rend()));

        for (int j = 0; j < count; ++j) {
          for (int k = 0; k < temp.size(); ++k) {
            stk.push(temp[temp.size() - k - 1]);
          }
        }
      }
    }

    while (!stk.empty()) {
      res.push_back(stk.top());
      stk.pop();
    }
    return string(res.rbegin(), res.rend());
  }
};