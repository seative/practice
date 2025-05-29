// 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i,
// 0) 和 (i, height[i]) 。

// 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

// 返回容器可以储存的最大水量。

// 说明：你不能倾斜容器。

// 输入：[1,8,6,2,5,4,8,3,7]
// 输出：49
// 解释：图中垂直线代表输入数组
// [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为
// 49。 示例 2：

// 输入：height = [1,1]
// 输出：1
#include <vector>
using namespace std;

// 双指针解法 ，O(n)复杂度，优于暴力解法
class Solution {
 public:
  int maxArea(vector<int>& height) {
    int index1 = 0;
    int index2 = height.size() - 1;

    int maxArea = 0;

    while (index1 < index2) {
      int area = (index2 - index1) * min(height[index1], height[index2]);
      maxArea = max(maxArea, area);

      if (height[index1] < height[index2]) {
        index1++;
      } else {
        index2--;
      }
    }
  }
};