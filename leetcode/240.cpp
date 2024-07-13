// 编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target
// 。该矩阵具有以下特性：

// 每行的元素从左到右升序排列。
// 每列的元素从上到下升序排列。

// 示例 1：

// 输入：matrix =
// [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]],
// target = 5 输出：true 示例 2：

// 输入：matrix =
// [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]],
// target = 20 输出：false
#include <vector>
using namespace std;

// 递归 太慢了
class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int s0, int s1, int m, int n,
                    int target) {
    if (s0 >= m || s1 >= n) {
      return false;
    }
    if (matrix[s0][s1] == target) {
      return true;
    } else if (matrix[s0][s1] < target) {
      if (searchMatrix(matrix, s0 + 1, s1 + 1, m, n, target)) {
        return true;
      }
      if (searchMatrix(matrix, s0 + 1, s1, m, n, target)) {
        return true;
      }
      if (searchMatrix(matrix, s0, s1 + 1, m, n, target)) {
        return true;
      }
      return false;
    }
    return false;
  }
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    int n = matrix[0].size();
    return searchMatrix(matrix, 0, 0, m, n, target);
  }
};

// 消去法，左下或右上元素和target对比可消去一行或一列
class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int i = matrix.size() - 1, j = 0;
    while (i >= 0 && j < matrix[0].size()) {
      if (matrix[i][j] > target)
        i--;
      else if (matrix[i][j] < target)
        j++;
      else
        return true;
    }
    return false;
  }
};