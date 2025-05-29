// 647. 回文子串
// 给你一个字符串 s ，请你统计并返回这个字符串中 回文子串 的数目。

// 回文字符串 是正着读和倒过来读一样的字符串。

// 子字符串 是字符串中的由连续字符组成的一个序列。

// 示例 1：

// 输入：s = "abc"
// 输出：3
// 解释：三个回文子串: "a", "b", "c"
// 示例 2：

// 输入：s = "aaa"
// 输出：6
// 解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"

// 提示：

// 1 <= s.length <= 1000
// s 由小写英文字母组成

#include <string>
using namespace std;

class Solution {
 public:
  int countSubstrings(string s) {
    int num = 0;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
      int left = i;
      int right = i;
      while (left >= 0 && right < n && s[left] == s[right]) {
        --left;
        ++num;
      }

      left = i;
      right = i;
      while (left >= 0 && right < n && s[left] == s[right]) {
        ++right;
        ++num;
      }

      left = i;
      right = i;
      while (left >= 0 && right < n && s[left] == s[right]) {
        --left;
        ++right;
        ++num;
      }
    }
    return num;
  }
};