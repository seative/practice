// 给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k
// 的子数组的个数 。

// 子数组是数组中元素的连续非空序列。

// 示例 1：

// 输入：nums = [1,1,1], k = 2
// 输出：2
// 示例 2：

// 输入：nums = [1,2,3], k = 3
// 输出：2

// 提示：

// 1 <= nums.length <= 2 * 104
// -1000 <= nums[i] <= 1000
// -107 <= k <= 107

#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// 前缀和 哈希表
class Solution {
 public:
  int subarraySum(std::vector<int>& nums, int k) {
    int preSum = 0;
    std::unordered_map<int, int> freq;
    freq[0] = 1;
    int cnt = 0;

    for (int v : nums) {
      preSum += v;
      cnt += freq[preSum - k];
      freq[preSum]++;
    }

    return cnt;
  }
};
