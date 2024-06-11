// 给定一个未排序的整数数组 nums
// ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

// 请你设计并实现时间复杂度为 O(n) 的算法解决此问题。

// 示例 1：

// 输入：nums = [100,4,200,1,3,2]
// 输出：4
// 解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。
// 示例 2：

// 输入：nums = [0,3,7,2,5,8,4,6,0,1]
// 输出：9

#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
  int longestConsecutive(vector<int> &nums) {
    std::unordered_set<int> num_set;
    for (auto num : nums) {
      num_set.insert(num);
    }

    int longest_streak = 0;

    for (auto num : nums) {
      if (num_set.count(num - 1))
        continue;
      int current_num = num;
      while (num_set.count(num + 1)) {
        num++;
      }
      longest_streak = max(longest_streak, num - current_num + 1);
    }

    return longest_streak;
  }
};