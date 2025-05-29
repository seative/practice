// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为
// 1 。

// 求在该柱状图中，能够勾勒出来的矩形的最大面积。

// 示例 1:

// 输入：heights = [2,1,5,6,2,3]
// 输出：10
// 解释：最大的矩形为图中红色区域，面积为 10
// 示例 2：

// 输入： heights = [2,4]
// 输出： 4

// 提示：

// 1 <= heights.length <=105
// 0 <= heights[i] <= 104
#include <vector>
using namespace std;

// bad  answer 使用了暴力解法，但是边界的处理始终有问题
class Solution {
public:
  int largestRectangleArea(vector<int> &heights) {
    int max_area = 0;
    if (heights.size() == 1) {
      return heights[0];
    }
    if (heights.size() == 2) {
      return max(max(heights[0], heights[1]), min(heights[0], heights[1]) * 2);
    }
    for (int i = 0; i < heights.size(); ++i) {
      int left = i == 0 ? 0 : i - 1;
      int right = i == heights.size() - 1 ? heights.size() - 1 : i + 1;
      while (left > 0 && heights[left] > heights[i]) {
        left--;
      }
      while (right < (heights.size() - 1) && heights[right] > heights[i]) {
        right++;
      }
      max_area =
          max(max_area, max(heights[i] * (right - left - 1), heights[i]));
    }
    return max_area;
  }
};

// 这是官方的暴力解法，值得学习边界处理
class Solution2 {
public:
  int largestRectangleArea(vector<int> &heights) {
    int n = heights.size();
    int ans = 0;
    for (int mid = 0; mid < n; ++mid) {
      // 枚举高
      int height = heights[mid];
      int left = mid, right = mid;
      // 确定左右边界
      while (left - 1 >= 0 && heights[left - 1] >= height) {
        --left;
      }
      while (right + 1 < n && heights[right + 1] >= height) {
        ++right;
      }
      // 计算面积
      ans = max(ans, (right - left + 1) * height);
    }
    return ans;
  }
};

class Solution3 {
public:
  int largestRectangleArea(vector<int> &heights) {
    int ans = 0;
    vector<int> st;
    heights.insert(heights.begin(), 0);
    heights.push_back(0);
    for (int i = 0; i < heights.size(); i++) {
      while (!st.empty() && heights[st.back()] > heights[i]) {
        int cur = st.back();
        st.pop_back();
        int left = st.back() + 1;
        int right = i - 1;
        ans = max(ans, (right - left + 1) * heights[cur]);
      }
      st.push_back(i);
    }
    return ans;
  }
};