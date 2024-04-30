// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s
// 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

// 注意：

// 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
// 如果 s 中存在这样的子串，我们保证它是唯一的答案。

// 示例 1：

// 输入：s = "ADOBECODEBANC", t = "ABC"
// 输出："BANC"
// 解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
// 示例 2：

// 输入：s = "a", t = "a"
// 输出："a"
// 解释：整个字符串 s 是最小覆盖子串。
// 示例 3:

// 输入: s = "a", t = "aa"
// 输出: ""
// 解释: t 中两个字符 'a' 均应包含在 s 的子串中，
// 因此没有符合条件的子字符串，返回空字符串。
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// 错误解法 未完成
// class Solution {
// public:
//   string minWindow(string s, string t) {
//     std::unordered_multiset<char> t_set(t.begin(), t.end());
//     string res;
//     int left, right;
//     for (size_t i = 0; i < s.size(); i++) {
//       if (t_set.find(s[i]) != t_set.end()) {
//         left = i;
//         t_set.erase(s[i]);
//         for (size_t j = i + 1; j < s.size(); j++) {
//           if (t_set.find(s[j]) != t_set.end()) {
//             t_set.erase(s[j]);
//             right = j;
//           }
//           if (t_set.empty())
//             break;
//         }
//         if (!t_set.empty())
//           return "";
//         break;
//       }
//     }

//     std::unordered_set<char> tmp;
//     for (int k = right + 1; k < s.size(); k++) {
//       tmp.insert(s[k]);
//       while (tmp.find(s[left]) != tmp.end()) {
//         left++;
//       }
//     }
//   }
// };

class Solution {
public:
  //定义两个哈希表，tstr用来存放t中元素的出现次数信息，sstr用来存放滑动窗口中元素的出现次数信息
  unordered_map<char, int> tstr, sstr;

  //检查当前的窗口是否是合格的窗口，即：
  //检查当前滑动窗口中元素是否完全覆盖了字符串t中的所有元素（重点是某元素的出现次数必须不小于t中对应元素的出现次数）
  bool check() {
    for (auto tchar : tstr) {
      if (tchar.second > sstr[tchar.first])
        return false; //注意这里的判断条件是大于
      //只要sstr中元素的second值不小于tchar中对应元素的second值就行
    }
    return true;
  }

  string minWindow(string s, string t) {
    int n1 = s.size(), n2 = t.size();
    if (n1 < n2)
      return ""; //如果t串比s串还长，s中肯定不能找到相应的子串
    int len = INT_MAX; //最小窗口的长度
    int ans_left = -1; //最小窗口的左边界指针
    //构造哈希表
    for (auto tchar : t)
      ++tstr[tchar];

    int left = 0, right = 0; //窗口的左右两端指针
    //滑动窗口右端指针遍历整个s串
    for (int right = 0; right < n1; right++) {
      //每遍历一个元素，更新sstr中的元素信息
      ++sstr[s[right]];
      //如果当前遍历到的元素在tstr中也有，说明此次遍历的更新是有效的更新，否则不用管，直接继续遍历
      if (tstr.find(s[right]) != tstr.end()) {
        //对于每一次有效的更新，检查当前窗口中的子串是否是一个合格的子串
        while (check() && left <= right) {
          //如果当前子串是合格的，那么判断是否是最小的窗口
          if (len > right - left + 1) {
            //如果是最小的窗口，那么更新窗口信息
            ans_left = left;
            len = right - left + 1;
          }

          //当前子串如果是合格的，那么尝试移进窗口的左边界缩短窗口的长度
          --sstr[s[left]]; //窗口左边界的元素信息从哈希表sstr中删除
          left++;          //移进窗口左边界

          //移进之后，继续while判断移进后的子串是否是合格的，如果是合格的，继续重复同样的操作，更新窗口的信息
        }

        //一旦窗口不合格，窗口右边界的指针就继续往后遍历，拓宽窗口的长度
      }
    }
    if (ans_left == -1)
      return "";
    else
      return s.substr(ans_left, len);
  }
};
