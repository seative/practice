// 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和
// n），可知至少存在一个重复的整数。

// 假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。

// 你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。

// 示例 1：

// 输入：nums = [1,3,4,2,2]
// 输出：2
// 示例 2：

// 输入：nums = [3,1,3,4,2]
// 输出：3
// 示例 3 :

// 输入：nums = [3,3,3,3,3]
// 输出：3

// 提示：

// 1 <= n <= 105
// nums.length == n + 1
// 1 <= nums[i] <= n
// nums 中 只有一个整数 出现 两次或多次 ，其余整数均只出现 一次
#include <bitset>
#include <vector>
using namespace std;

class Solution {
 public:
  int findDuplicate(vector<int>& nums) {
    int a = nums.size();
    vector<char> arr(a / 8 + 1, 0);
    for (int i = 0; i < a; ++i) {
      int m = nums[i] / 8;
      int n = nums[i] % 8;
      if (arr[m] & (1 << n)) {
        return nums[i];
      }
      arr[m] |= 1 << n;
    }
    return 0;
  }
};

// 二分法
class Solution2 {
 public:
  int findDuplicate(vector<int>& nums) {
    int l = 1;
    int r = nums.size() - 1;
    int ans = -1;
    while (l <= r) {
      int mid = (l + r) >> 1;
      int cnt = 0;
      for (int i = 0; i < nums.size(); ++i) {
        if (nums[i] <= mid) {
          cnt++;
        }
      }
      if (cnt <= mid) {
        l = mid + 1;
      } else {
        r = mid - 1;
        ans = mid;
      }
    }
    return ans;
  }
};

// 二进制

class Solution3 {
  int findDuplicate(vector<int>& nums) {
    int n = nums.size();
    int bit_max = 31;
    while ((n - 1) & (1 << bit_max)) --bit_max;
    int ans = 0;

    for (int i = 0; i < bit_max; ++i) {
      int x = 0;
      int y = 0;
      for (int j = 0; j < n; ++j) {
        if (nums[j] & (1 << i)) x++;
      }
      for (int j = 0; j < n - 1; ++j) {
        if (j & (1 << i)) y++;
      }
      if (x > y) {
        ans |= 1 << i;
      }
    }
    return ans;
  }
};
// 环形链表