// 给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的
// 子集
// （幂集）。

// 解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

// 示例 1：

// 输入：nums = [1,2,3]
// 输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
// 示例 2：

// 输入：nums = [0]
// 输出：[[],[0]]

// 提示：

// 1 <= nums.length <= 10
// -10 <= nums[i] <= 10
// nums 中的所有元素 互不相同

#include <vector>
using namespace std;

// 回溯法
class Solution {
 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> path;
    backTrack(res, nums, path, 0);
    return res;
  }

  void backTrack(vector<vector<int>>& res, vector<int>& nums, vector<int>& path,
                 int index) {
    res.push_back(path);

    for (size_t i = index; i < nums.size(); ++i) {
      path.push_back(nums[i]);
      backTrack(res, nums, path, i + 1);
      path.pop_back();
    }
  }
};

// 迭代法实现子集枚举
class Solution2 {
 public:
  vector<int> t;
  vector<vector<int>> ans;

  vector<vector<int>> subsets(vector<int>& nums) {
    int n = nums.size();
    for (int mask = 0; mask < (1 << n); ++mask) {
      t.clear();
      for (int i = 0; i < n; ++i) {
        if (mask & (1 << i)) {
          t.push_back(nums[i]);
        }
      }
      ans.push_back(t);
    }
    return ans;
  }
};

// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/subsets/solutions/420294/zi-ji-by-leetcode-solution/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。