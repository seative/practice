// 给你一个整数数组 nums ，你需要找出一个 连续子数组
// ，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。

// 请你找出符合题意的 最短 子数组，并输出它的长度。

// 示例 1：

// 输入：nums = [2,6,4,8,10,9,15]
// 输出：5
// 解释：你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。
// 示例 2：

// 输入：nums = [1,2,3,4]
// 输出：0
// 示例 3：

// 输入：nums = [1]
// 输出：0

// 提示：

// 1 <= nums.length <= 104
// -105 <= nums[i] <= 105

// 进阶：你可以设计一个时间复杂度为 O(n) 的解决方案吗

#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
 public:
  int findUnsortedSubarray(vector<int>& nums) {
    vector<int> temp(nums);
    std::sort(temp.begin(), temp.end());

    int l = 0;
    for (int i = 0; i < temp.size(); ++i) {
      if (temp[i] != nums[i]) {
        l = i;
        break;
      }
    }

    int r = 0;
    for (int i = temp.size() - 1; i >= 0; --i) {
      if (temp[i] != nums[i]) {
        r = i + 1;
        break;
      }
    }
    return r - l;
  }
};

class Solution2 {
 public:
  int findUnsortedSubarray(vector<int>& nums) {
    int maxLeft = INT_MIN;
    int right = -1;
    int n = nums.size();

    int minRight = INT_MAX;
    int left = -1;

    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] < maxLeft)
        right = i;
      else
        maxLeft = nums[i];

      if (nums[n - i - 1] > minRight)
        left = n - i - 1;
      else
        minRight = nums[n - i - 1];
    }
    return right == -1 ? 0 : right - left + 1;
  }
};