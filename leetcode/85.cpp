// 给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1
// 的最大矩形，并返回其面积。

// 示例 1：

// 输入：matrix =
// [['1','0','1','0','0'],['1','0','1','1','1'],['1','1','1','1','1'],['1','0','0','1','0']]
// 输出：6
// 解释：最大矩形如上图所示。
// 示例 2：

// 输入：matrix = [['0']]
// 输出：0
// 示例 3：

// 输入：matrix = [['1']]
// 输出：1

#include <iostream>
#include <vector>
using namespace std;

class Solution {
 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    vector<vector<int>> leftWidth(matrix.size(),
                                  vector<int>(matrix[0].size(), 0));
    // for (size_t i = 0; i < matrix.size(); ++i) {
    //   for (size_t j = 0; j < matrix[0].size(); ++j) {
    //     for (int k = j; k >= 0; --k) {
    //       if (matrix[i][k] == '0') break;
    //       leftWidth[i][j] += 1;
    //     }
    //   }
    // }

    for (size_t i = 0; i < matrix.size(); ++i) {
      for (size_t j = 0; j < matrix[0].size(); ++j) {
        if (matrix[i][j] == '1')
          leftWidth[i][j] = (j == 0 ? 0 : leftWidth[i][j - 1]) + 1;
      }
    }

    int maxArea = 0;
    for (size_t j = 0; j < matrix[0].size(); ++j) {
      vector<int> heights;

      for (size_t i = 0; i < matrix.size(); ++i) {
        heights.push_back(leftWidth[i][j]);
      }
      maxArea = max(maxArea, longestarea(heights));
    }
    return maxArea;
  }

  int longestarea(vector<int> heights) {
    heights.push_back(0);
    heights.insert(heights.begin(), 0);
    int maxArea = 0;

    vector<int> stack;
    for (size_t i = 0; i < heights.size(); ++i) {
      while (!stack.empty() && heights[i] < heights[stack.back()]) {
        int cur = heights[stack.back()];
        stack.pop_back();
        int left = stack.back() + 1;
        int right = i - 1;
        maxArea = max(maxArea, (right - left + 1) * cur);
      }
      stack.push_back(i);
    }
    return maxArea;
  }
};

int main() {
  vector<vector<char>> a{{'1', '0', '1', '0', '0'},
                         {'1', '0', '1', '1', '1'},
                         {'1', '1', '1', '1', '1'},
                         {'1', '0', '0', '1', '0'}};

  Solution test;
  std::cout << test.maximalRectangle(a) << std::endl;
}