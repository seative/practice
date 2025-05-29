// 给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。

// 完全平方数
// 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9
// 和 16 都是完全平方数，而 3 和 11 不是。

// 示例 1：

// 输入：n = 12
// 输出：3
// 解释：12 = 4 + 4 + 4
// 示例 2：

// 输入：n = 13
// 输出：2
// 解释：13 = 4 + 9

// 提示：

// 1 <= n <= 104

#include <cmath>
#include <vector>
using namespace std;

// 递归超时
class Solution {
 public:
  int findNearestSqrt(int n) {
    for (int i = 1; i <= n; ++i) {
      if (i * i == n) {
        return i;
      }
      if (i * i > n) {
        return i - 1;
      }
    }
    return 0;
  }

  int numSquares(int n) {
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
      int sq = findNearestSqrt(i);
      int mi = 1000;
      for (int j = 1; j <= sq; ++j) {
        int temp = i - j * j;
        mi = min(dp[temp], mi);
      }
      dp[i] = mi + 1;
    }
    return dp[n];
  }
};