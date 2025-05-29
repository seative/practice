// 给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums
// ，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

// 我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

// 必须在不使用库内置的 sort 函数的情况下解决这个问题。

// 示例 1：

// 输入：nums = [2,0,2,1,1,0]
// 输出：[0,0,1,1,2,2]
// 示例 2：

// 输入：nums = [2,0,1]
// 输出：[0,1,2]

// 提示：

// n == nums.length
// 1 <= n <= 300
// nums[i] 为 0、1 或 2

// 进阶：

// 你能想出一个仅使用常数空间的一趟扫描算法吗？

#include <vector>
using namespace std;

// 快排解法
class Solution {
public:
  void sortColors(vector<int> &nums) { quickSoft(nums, 0, nums.size() - 1); }

  void quickSoft(vector<int> &nums, int l, int r) {
    if (l < r) {
      int base = nums[l];
      int left = l;
      int right = r;
      while (left < right) {
        while (left < right && nums[right] >= base) {
          right--;
        }
        nums[left] = nums[right];
        while (left < right && nums[left] <= base) {
          left++;
        }
        nums[right] = nums[left];
      }
      nums[left] = base;
      quickSoft(nums, l, left - 1);
      quickSoft(nums, right + 1, r);
    }
  }
};

// 官方解 单指针
class Solution1 {
public:
  void sortColors(vector<int> &nums) {
    int n = nums.size();
    int ptr = 0;
    for (int i = 0; i < n; ++i) {
      if (nums[i] == 0) {
        swap(nums[i], nums[ptr]);
        ++ptr;
      }
    }
    for (int i = ptr; i < n; ++i) {
      if (nums[i] == 1) {
        swap(nums[i], nums[ptr]);
        ++ptr;
      }
    }
  }
};

// 官方解 双指针
class Solution2 {
public:
  void sortColors(vector<int> &nums) {
    int n = nums.size();
    int p0 = 0, p1 = 0;
    for (int i = 0; i < n; ++i) {
      if (nums[i] == 1) {
        swap(nums[i], nums[p1]);
        ++p1;
      } else if (nums[i] == 0) {
        swap(nums[i], nums[p0]);
        if (p0 < p1) {
          swap(nums[i], nums[p1]);
        }
        ++p0;
        ++p1;
      }
    }
  }
};

// 官方解 双指针二
class Solution3 {
public:
  void sortColors(vector<int> &nums) {
    int n = nums.size();
    int p0 = 0, p2 = n - 1;
    for (int i = 0; i <= p2; ++i) {
      while (i <= p2 && nums[i] == 2) {
        swap(nums[i], nums[p2]);
        --p2;
      }
      if (nums[i] == 0) {
        swap(nums[i], nums[p0]);
        ++p0;
      }
    }
  }
};