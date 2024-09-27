
// 309. 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount
// ，表示总金额。

// 计算并返回可以凑成总金额所需的最少的硬币个数.
// 如果没有任何一种硬币组合能组成总金额，返回 -1 。

// 你可以认为每种硬币的数量是无限的。

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 暴力解法
// class Solution {
//  public:
//   int coinChange(vector<int>& coins, int amount) {
//     int num = 0;
//     int minNum = -1;
//     std::sort(coins.begin(), coins.end());
//     backTrack(coins, amount, num, minNum);
//     return minNum;
//   }

//   void backTrack(vector<int>& coins, int amount, int& num, int& minNum) {
//     if (amount < 0) return;
//     if (amount == 0) {
//       minNum = minNum == -1 ? num : min(minNum, num);
//       return;
//     }
//     for (int i = coins.size() - 1; i >= 0; --i) {
//       num++;
//       if (num > minNum && minNum != -1) {
//         num--;
//         return;
//       }
//       backTrack(coins, amount - coins[i], num, minNum);
//       num--;
//     }
//   }
// };

// 记忆化搜索
class Solution {
  vector<int> count;
  int dp(vector<int>& coins, int rem) {
    if (rem < 0) return -1;
    if (rem == 0) return 0;
    if (count[rem - 1] != 0) return count[rem - 1];
    int Min = INT_MAX;
    for (int coin : coins) {
      int res = dp(coins, rem - coin);
      if (res >= 0 && res < Min) {
        Min = res + 1;
      }
    }
    count[rem - 1] = Min == INT_MAX ? -1 : Min;
    return count[rem - 1];
  }

 public:
  int coinChange(vector<int>& coins, int amount) {
    if (amount < 1) return 0;
    count.resize(amount);
    return dp(coins, amount);
  }
};

int main() {
  vector<int> coins = {1, 2, 5};
  int amount = 100;
  Solution s;
  int res = s.coinChange(coins, amount);
  std::cout << res << std::endl;
  return 0;
}