// 有 n 个气球，编号为0 到 n - 1，每个气球上都标有一个数字，这些数字存在数组
// nums 中。

// 现在要求你戳破所有的气球。戳破第 i 个气球，你可以获得 nums[i - 1] * nums[i] *
// nums[i + 1] 枚硬币。 这里的 i - 1 和 i + 1 代表和 i
// 相邻的两个气球的序号。如果 i - 1或 i + 1
// 超出了数组的边界，那么就当它是一个数字为 1 的气球。

// 求所能获得硬币的最大数量。

// 示例 1：
// 输入：nums = [3,1,5,8]
// 输出：167
// 解释：
// nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
// coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
// 示例 2：

// 输入：nums = [1,5]
// 输出：10

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<vector<int>> rec;
  vector<int> val;

 public:
  int solve(int left, int right) {
    if (left >= right - 1) {
      return 0;
    }
    if (rec[left][right] != -1) {
      return rec[left][right];
    }
    for (int i = left + 1; i < right; i++) {
      int sum = val[left] * val[i] * val[right];
      sum += solve(left, i) + solve(i, right);
      rec[left][right] = max(rec[left][right], sum);
    }
    return rec[left][right];
  }

  int maxCoins(vector<int>& nums) {
    int n = nums.size();
    val.resize(n + 2);
    for (int i = 1; i <= n; i++) {
      val[i] = nums[i - 1];
    }
    val[0] = val[n + 1] = 1;
    rec.resize(n + 2, vector<int>(n + 2, -1));
    return solve(0, n + 1);
  }
};

// dp解法
class Solution2 {
 public:
  int maxCoins(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> rec(n + 2, vector<int>(n + 2));
    vector<int> val(n + 2);
    val[0] = val[n + 1] = 1;
    for (int i = 1; i <= n; i++) {
      val[i] = nums[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
      for (int j = i + 2; j <= n + 1; j++) {
        for (int k = i + 1; k < j; k++) {
          int sum = val[i] * val[k] * val[j];
          sum += rec[i][k] + rec[k][j];
          rec[i][j] = max(rec[i][j], sum);
        }
      }
    }
    return rec[0][n + 1];
  }
};