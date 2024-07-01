// 给你一个由 '1'（陆地）和
// '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

// 此外，你可以假设该网格的四条边均被水包围。

// 示例 1：

// 输入：grid = [
//   ["1","1","1","1","0"],
//   ["1","1","0","1","0"],
//   ["1","1","0","0","0"],
//   ["0","0","0","0","0"]
// ]
// 输出：1
// 示例 2：

// 输入：grid = [
//   ["1","1","0","0","0"],
//   ["1","1","0","0","0"],
//   ["0","0","1","0","0"],
//   ["0","0","0","1","1"]
// ]
// 输出：3
#include <stack>
#include <vector>
using namespace std;

class Solution {
 public:
  int numIslands(vector<vector<char>>& grid) {
    std::stack<std::pair<int, int>> stk;

    int num = 0;
    int m = grid.size();
    int n = grid[0].size();
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (grid[i][j] == '1') {
          grid[i][j] = '0';
          stk.emplace(i, j);

          while (!stk.empty()) {
            auto [i, j] = stk.top();
            stk.pop();
            if (i + 1 < m && grid[i + 1][j] == '1') {
              grid[i + 1][j] = '0';
              stk.emplace(i + 1, j);
            }
            if (i - 1 >= 0 && grid[i - 1][j] == '1') {
              grid[i - 1][j] = '0';
              stk.emplace(i - 1, j);
            }
            if (j + 1 < n && grid[i][j + 1] == '1') {
              grid[i][j + 1] = '0';
              stk.emplace(i, j + 1);
            }
            if (j - 1 >= 0 && grid[i][j - 1] == '1') {
              grid[i][j - 1] = '0';
              stk.emplace(i, j - 1);
            }
          }
          ++num;
        }
      }
    }
    return num;
  }
};