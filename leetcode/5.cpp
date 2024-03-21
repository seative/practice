// 给你一个字符串 s，找到 s 中最长的回文子串

// 如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。

// 示例 1：

// 输入：s = "babad"
// 输出："bab"
// 解释："aba" 同样是符合题意的答案。
// 示例 2：

// 输入：s = "cbbd"
// 输出："bb"

#include <string>
#include <vector>
using namespace std;

class Solution {
public:
  string longestPalindrome(string s) {

    int maxLen = 0;
    int maxStart = 0;
    for (size_t i = 0, len = 1; i < s.size(); ++i) {
      int left = i - 1;
      int right = i + 1;

      while (left >= 0 && s.at(left) == s.at(i)) {
        len++;
        left--;
      }
      while (right < s.size() && s.at(right) == s.at(i)) {
        len++;
        right++;
      }

      while (left >= 0 && right < s.size() && s.at(right) == s.at(left)) {
        len = len + 2;
        left--;
        right++;
      }
      if (len > maxLen) {
        maxLen = len;
        maxStart = left;
      }
      len = 1;
    }
    return s.substr(maxStart + 1, maxLen);
  }
};