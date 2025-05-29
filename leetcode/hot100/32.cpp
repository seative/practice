// 给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号
// 子串
// 的长度。

// 示例 1：

// 输入：s = "(()"
// 输出：2
// 解释：最长有效括号子串是 "()"
// 示例 2：

// 输入：s = ")()())"
// 输出：4
// 解释：最长有效括号子串是 "()()"
// 示例 3：

// 输入：s = ""
// 输出：0

#include <algorithm>
#include <cmath>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// wrong answer
// class Solution {
// public:
//     int longestValidParentheses(string s) {
//         std::unordered_map<char,char>  parentMap={{')','('}};
//         std::stack<char> parentStack;
//         int left=0;
//         int length=0;

//         for(int i=0;i<s.size();++i)
//         {
//             if(parentMap.count(s[i]))
//             {
//                 while(!parentStack.empty()&&parentMap.count(s[i])&&parentStack.top()==parentMap[s[i]])
//                 {
//                     parentStack.pop();
//                     length+=2;
//                     ++i;
//                 }
//                 if(parentStack.empty())
//                 {
//                     left=i;
//                 }
//                 else
//                 {
//                     length=std::max(length,i-left);
//                 }
//             }
//             else
//             {
//                 parentStack.push(s[i]);
//             }
//         }
//     }
// };

class Solution2 {
public:
  int longestValidParentheses(string s) {
    int maxans = 0;
    stack<int> stk;
    stk.push(-1);
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '(') {
        stk.push(i);
      } else {
        stk.pop();
        if (stk.empty()) {
          stk.push(i);
        } else {
          maxans = max(maxans, i - stk.top());
        }
      }
    }
    return maxans;
  }
};

// 两次遍历，第一次从左到右，第二次从右到左，通过（）数量来判断
class Solution3 {
public:
  int longestValidParentheses(string s) {
    int left = 0, right = 0, maxlength = 0;
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == '(') {
        left++;
      } else {
        right++;
      }
      if (left == right) {
        maxlength = max(maxlength, 2 * right);
      } else if (right > left) {
        left = right = 0;
      }
    }
    left = right = 0;
    for (int i = (int)s.length() - 1; i >= 0; i--) {
      if (s[i] == '(') {
        left++;
      } else {
        right++;
      }
      if (left == right) {
        maxlength = max(maxlength, 2 * left);
      } else if (left > right) {
        left = right = 0;
      }
    }
    return maxlength;
  }
};

// 动态规划问题
class Solution4 {
public:
  int longestValidParentheses(string s) {
    int maxans = 0, n = s.length();
    vector<int> dp(n, 0);
    for (int i = 1; i < n; i++) {
      if (s[i] == ')') {
        if (s[i - 1] == '(') {
          dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
        } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
          dp[i] = dp[i - 1] +
                  ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
        }
        maxans = max(maxans, dp[i]);
      }
    }
    return maxans;
  }
};