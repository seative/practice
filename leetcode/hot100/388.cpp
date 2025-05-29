// 给你一个整数 n ，对于 0 <= i <= n 中的每个 i ，计算其二进制表示中 1 的个数
// ，返回一个长度为 n + 1 的数组 ans 作为答案。

// 示例 1：

// 输入：n = 2
// 输出：[0,1,1]
// 解释：
// 0 --> 0
// 1 --> 1
// 2 --> 10
// 示例 2：

// 输入：n = 5
// 输出：[0,1,1,2,1,2]
// 解释：
// 0 --> 0
// 1 --> 1
// 2 --> 10
// 3 --> 11
// 4 --> 100
// 5 --> 101

#include <vector>
using namespace std;

class Solution {
 public:
  int countOnes(int x) {
    int ones = 0;
    while (x > 0) {
      x &= (x - 1);
      ones++;
    }
    return ones;
  }

  vector<int> countBits(int n) {
    vector<int> bits(n + 1);
    for (int i = 0; i <= n; i++) {
      bits[i] = countOnes(i);
    }
    return bits;
  }
};

class Solution2 {
 public:
  vector<int> countBits(int n) {
    vector<int> bits(n + 1);
    int highBits = 0;
    for (int i = 1; i <= n; ++i) {
      if ((i & (i - 1)) == 0) {
        highBits = i;
      }
      bits[i] = bits[i - highBits] + 1;
    }
    return bits;
  }
};