// 给你一个字符串 s 和一个字符串列表 wordDict
// 作为字典。如果可以利用字典中出现的一个或多个单词拼接出 s 则返回 true。

// 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。

// 示例 1：

// 输入: s = "leetcode", wordDict = ["leet", "code"]
// 输出: true
// 解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。
// 示例 2：

// 输入: s = "applepenapple", wordDict = ["apple", "pen"]
// 输出: true
// 解释: 返回 true 因为 "applepenapple" 可以由 "apple" "pen" "apple" 拼接成。
//      注意，你可以重复使用字典中的单词。
// 示例 3：

// 输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
// 输出: false

// 提示：

// 1 <= s.length <= 300
// 1 <= wordDict.length <= 1000
// 1 <= wordDict[i].length <= 20
// s 和 wordDict[i] 仅由小写英文字母组成
// wordDict 中的所有字符串 互不相同

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// 动态规划
class Solution {
 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;

    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());

    for (size_t i = 0; i < s.size(); ++i) {
      for (size_t j = 0; j <= i; ++j) {
        if (dp[j] && wordSet.count(s.substr(j, i - j + 1))) {
          dp[i + 1] = true;
          break;
        }
      }
    }
    return dp[s.size()];
  }
};

// DFS，记忆化搜索
class Solution2 {
 public:
  bool backTrack(string s, unordered_set<string>& wordDict, vector<int>& temp,
                 int i) {
    if (i == s.size()) return true;
    if (temp[i] == 0 || temp[i] == 1) return temp[i];

    for (size_t j = i; j < s.size(); ++j) {
      if (wordDict.count(s.substr(i, j - i + 1)) &&
          backTrack(s, wordDict, temp, j + 1)) {
        temp[i] = 1;
        return true;
      }
    }
    temp[i] = 0;
    return false;
  }

  bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> wordSet(wordDict.begin(), wordDict.end());

    vector<int> temp(s.size(), 3);
    return backTrack(s, wordSet, temp, 0);
  }
};