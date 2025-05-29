// 给定一个大小为 n 的数组 nums
// ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

// 你可以假设数组是非空的，并且给定的数组总是存在多数元素。

// 示例 1：

// 输入：nums = [3,2,3]
// 输出：3
// 示例 2：

// 输入：nums = [2,2,1,1,1,2,2]
// 输出：2

// 提示：
// n == nums.length
// 1 <= n <= 5 * 104
// -109 <= nums[i] <= 109

// 进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。
#include <cstdio>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
 public:
  int majorityElement(vector<int>& nums) {
    std::unordered_map<int, int> count;
    for (auto num : nums) {
      count[num]++;
      if (count[num] > nums.size() / 2) {
        return num;
      }
    }
    return -1;
  }
};

// Boyer-Moore 投票算法
class Solution2 {
 public:
  int majorityElement(vector<int>& nums) {
    int candidate = -1;
    int count = 0;
    for (int num : nums) {
      if (num == candidate)
        ++count;
      else if (--count < 0) {
        candidate = num;
        count = 1;
      }
    }
    return candidate;
  }
};

// 位运算
class Solution3 {
 public:
  int majorityElement(vector<int>& nums) {
    vector<int> a(32);
    int n = nums.size() >> 1;
    for (unsigned int i : nums) {
      for (int j = 0; j < 32; j++) {
        a[j] += (i >> j) & 1;
      }
    }
    int ans = 0;
    for (int i = 0; i < 32; i++) {
      ans += a[i] <= n ? 0 : 1 << i;
    }
    return ans;
  }
};
