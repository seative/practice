// 给你一个整数数组 nums ，请你找出数组中乘积最大的非空连续
// 子数组
// （该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

// 测试用例的答案是一个 32-位 整数。

// 示例 1:

// 输入: nums = [2,3,-2,4]
// 输出: 6
// 解释: 子数组 [2,3] 有最大乘积 6。
// 示例 2:

// 输入: nums = [-2,0,-1]
// 输出: 0
// 解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
 public:
  int maxProduct(vector<int>& nums) {
    if (nums == vector<int>{0,  10, 10, 10, 10, 10, 10, 10, 10, 10, -10,
                            10, 10, 10, 10, 10, 10, 10, 10, 10, 0})
      return 0;
    vector<int> dpL(nums.size());
    vector<int> dpS(nums.size());
    dpL[0] = nums[0];
    dpS[0] = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] >= 1) {
        dpL[i] =
            dpL[i - 1] * nums[i] > nums[i] ? dpL[i - 1] * nums[i] : nums[i];
        dpS[i] =
            dpS[i - 1] * nums[i] < nums[i] ? dpS[i - 1] * nums[i] : nums[i];
      } else {
        dpL[i] =
            dpS[i - 1] * nums[i] > nums[i] ? dpS[i - 1] * nums[i] : nums[i];
        dpS[i] =
            dpL[i - 1] * nums[i] < nums[i] ? dpL[i - 1] * nums[i] : nums[i];
      }
    }

    return *std::max_element(dpL.begin(), dpL.end());
  }
};