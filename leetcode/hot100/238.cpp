// 给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除
// nums[i] 之外其余各元素的乘积 。

// 题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位
// 整数范围内。

// 请 不要使用除法，且在 O(n) 时间复杂度内完成此题。

// 示例 1:

// 输入: nums = [1,2,3,4]
// 输出: [24,12,8,6]
// 示例 2:

// 输入: nums = [-1,1,0,-3,3]
// 输出: [0,0,9,0,0]
#include <stack>
#include <vector>
using namespace std;

// O(n) 空间复杂度
class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    std::vector<int> left(nums.size(), 1);
    std::vector<int> right(nums.size(), 1);
    std::vector<int> res(nums.size(), 1);

    for (int i = 0; i < nums.size(); ++i) {
      left[i] = i == 0 ? nums[0] : left[i - 1] * nums[i];
      right[nums.size() - i - 1] =
          i == 0 ? nums[nums.size() - 1]
                 : right[nums.size() - i] * nums[nums.size() - i - 1];
    }
    for (int i = 1; i < nums.size() - 1; ++i) {
      res[i] = left[i - 1] * right[i + 1];
    }
    res[0] = right[1];
    res[nums.size() - 1] = left[nums.size() - 2];
    return res;
  }
};

// O(1) 空间复杂度，很巧妙
class Solution2 {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    std::vector<int> ans(nums.size(), 1);
    int before = 1;
    int after = 1;

    for (int i = 0, j = nums.size() - 1; i < nums.size(); ++i, --j) {
      ans[i] *= before;
      ans[j] *= after;
      before *= nums[i];
      after *= nums[j];
    }
    return ans;
  }
};
