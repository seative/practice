// 给你一个 只包含正整数 的 非空 数组 nums
// 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

// 示例 1：

// 输入：nums = [1,5,11,5]
// 输出：true
// 解释：数组可以分割成 [1, 5, 5] 和 [11] 。
// 示例 2：

// 输入：nums = [1,2,3,5]
// 输出：false
// 解释：数组不能分割成两个元素和相等的子集。

#include <cmath>
#include <vector>
using namespace std;

// 0-1背包问题
class Solution {
 public:
  bool canPartition(vector<int>& nums) {
    int sum = 0, n = nums.size();
    for (int& num : nums) sum += num;
    if (sum % 2) return false;

    int capacity = sum / 2;
    vector<bool> dp(capacity + 1, false);
    dp[0] = true;
    for (int i = 0; i < n; i++)
      for (int j = capacity; j >= nums[i]; j--)
        dp[j] = dp[j] || dp[j - nums[i]];

    return dp[capacity];
  }
};