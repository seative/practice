// 给你一个非负整数数组 nums 和一个整数 target 。

// 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式
// ：

// 例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-'
// ，然后串联起来得到表达式 "+2-1" 。 返回可以通过上述方法构造的、运算结果等于
// target 的不同 表达式 的数目。

// 示例 1：

// 输入：nums = [1,1,1,1,1], target = 3
// 输出：5
// 解释：一共有 5 种方法让最终目标和为 3 。
// -1 + 1 + 1 + 1 + 1 = 3
// +1 - 1 + 1 + 1 + 1 = 3
// +1 + 1 - 1 + 1 + 1 = 3
// +1 + 1 + 1 - 1 + 1 = 3
// +1 + 1 + 1 + 1 - 1 = 3
// 示例 2：

// 输入：nums = [1], target = 1
// 输出：1

// dfs解法
class Solution {
 public:
  int findTargetSumWays(vector<int>& nums, int target) {
    return dfs(nums, 0, target);
  }

  int dfs(vector<int>& nums, int i, int target) {
    if (i == nums.size()) {
      if (target == 0)
        return 1;
      else
        return 0;
    }
    int a = dfs(nums, i + 1, target - nums[i]);
    int b = dfs(nums, i + 1, target + nums[i]);

    return a + b;
  }
};

// 动态规划 -> 01背包问题
#include <vector>
using namespace std;
class Solution2 {
 public:
  int findTargetSumWays(vector<int>& nums, int target) {
    int numsAll = 0;
    for (auto& elem : nums) {
      numsAll += elem;
    }

    int diff = numsAll - target;
    if (diff < 0 || diff % 2 != 0) {
      return 0;
    }

    int res = diff / 2;

    vector<int> dp(res + 1);
    dp[0] = 1;
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = res; j >= nums[i]; --j) {
        dp[j] += dp[j - nums[i]];
      }
    }
    return dp[res];
  }
};