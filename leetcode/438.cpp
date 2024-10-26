// 给定两个字符串 s 和 p，找到 s 中所有 p 的
// 异位词
//  的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

// 示例 1:

// 输入: s = "cbaebabacd", p = "abc"
// 输出: [0,6]
// 解释:
// 起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
// 起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
//  示例 2:

// 输入: s = "abab", p = "ab"
// 输出: [0,1,2]
// 解释:
// 起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
// 起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
// 起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。

#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> findAnagrams(string s, string p) {
    vector<int> ans;
    std::unordered_map<char, int> res;
    std::unordered_map<char, int> temp;
    if (s.size() < p.size()) return ans;
    for (int i = 0; i < p.size(); ++i) {
      res[p[i]]++;
      temp[s[i]]++;
    }

    int size = p.size();
    if (temp == res) ans.push_back(0);
    for (int i = 0; i < (int)s.size() - size; ++i) {
      --temp[s[i]];
      if (temp[s[i]] == 0) temp.erase(s[i]);
      ++temp[s[i + size]];

      if (temp == res) ans.push_back(i + 1);
    }
    return ans;
  }
};