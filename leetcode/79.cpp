// 给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word
// 存在于网格中，返回 true ；否则，返回 false 。

// 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

// 示例 1：

// 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
// "ABCCED" 输出：true 示例 2：

// 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
// "SEE" 输出：true 示例 3：

// 输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
// "ABCB" 输出：false

// 提示：

// m == board.length
// n = board[i].length
// 1 <= m, n <= 6
// 1 <= word.length <= 15
// board 和 word 仅由大小写英文字母组成

#include <string>
#include <vector>
using namespace std;

class Solution {
 public:
  bool exist(vector<vector<char>>& board, string word) {
    // vector<vector<bool>> regis(board.size(),
    //                            vector<bool>(board[0].size(), false));
    for (size_t i = 0; i < board.size(); ++i) {
      for (size_t j = 0; j < board[i].size(); ++j) {
        if (dfs(board, word, i, j, 0)) {
          return true;
        }
      }
    }
    return false;
  }

  bool dfs(vector<vector<char>>& board, string& word, int i, int j, int num) {
    if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size() ||
        board[i][j] != word[num])
      return false;
    if (num == word.size() - 1) return true;
    board[i][j] = '\0';
    bool res = dfs(board, word, i - 1, j, num + 1) ||
               dfs(board, word, i + 1, j, num + 1) ||
               dfs(board, word, i, j - 1, num + 1) ||
               dfs(board, word, i, j + 1, num + 1);
    board[i][j] = word[num];
    return res;
  }
};