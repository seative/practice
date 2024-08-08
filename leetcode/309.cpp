
// 309. 买卖股票的最佳时机含冷冻期
// 给定一个整数数组prices，其中第  prices[i] 表示第 i 天的股票价格
// 。​

// 设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

// 卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
// 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

#include <vector>
using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    if (prices.empty()) {
      return 0;
    }

    int n = prices.size();
    // f[i][0]: 手上持有股票的最大收益
    // f[i][1]: 手上不持有股票，并且处于冷冻期中的累计最大收益
    // f[i][2]: 手上不持有股票，并且不在冷冻期中的累计最大收益
    vector<vector<int>> f(n, vector<int>(3));
    f[0][0] = -prices[0];
    for (int i = 1; i < n; ++i) {
      f[i][0] = max(f[i - 1][0], f[i - 1][2] - prices[i]);
      f[i][1] = f[i - 1][0] + prices[i];
      f[i][2] = max(f[i - 1][1], f[i - 1][2]);
    }
    return max(f[n - 1][1], f[n - 1][2]);
  }
};