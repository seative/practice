// 给你一个 非空 整数数组 nums
// ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

// 你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。

// 示例 1 ：

// 输入：nums = [2,2,1]
// 输出：1
// 示例 2 ：

// 输入：nums = [4,1,2,1,2]
// 输出：4
// 示例 3 ：

// 输入：nums = [1]
// 输出：1

// 提示：

// 1 <= nums.length <= 3 * 104
// -3 * 104 <= nums[i] <= 3 * 104
// 除了某个元素只出现一次以外，其余每个元素均出现两次。
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// 暴力解法
class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    std::unordered_map<int, int> s;
    for (auto num : nums) s[num]++;
    for (auto elem : s) {
      if (elem.second == 1) {
        return elem.first;
      }
    }
    return 0;
  }
};

class Solution2 {
 public:
  int singleNumber(vector<int>& nums) {
    int res = 0;
    for (auto num : nums) {
      res ^= num;
    }
    return res;
  }
};