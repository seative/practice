// 给你一个按照非递减顺序排列的整数数组 nums，和一个目标值
// target。请你找出给定目标值在数组中的开始位置和结束位置。

// 如果数组中不存在目标值 target，返回 [-1, -1]。

// 你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。

// 示例 1：

// 输入：nums = [5,7,7,8,8,10], target = 8
// 输出：[3,4]
// 示例 2：

// 输入：nums = [5,7,7,8,8,10], target = 6
// 输出：[-1,-1]
// 示例 3：

// 输入：nums = [], target = 0
// 输出：[-1,-1]

#include <algorithm>
#include <vector>
using namespace std;
class Solution {
public:
  vector<int> searchRange(vector<int> &nums, int target) {
    auto begin = std::lower_bound(nums.begin(), nums.end(), target);
    auto end = std::upper_bound(nums.begin(), nums.end(), target);
    return begin == end ? vector<int>{-1, -1}
                        : vector<int>{static_cast<int>(begin - nums.begin()),
                                      static_cast<int>(end - nums.begin() - 1)};
  }
};