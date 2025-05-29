// 给你一个整数数组 nums，有一个大小为 k
// 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k
// 个数字。滑动窗口每次只向右移动一位。

// 返回 滑动窗口中的最大值 。

// 示例 1：

// 输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
// 输出：[3,3,5,5,6,7]
// 解释：
// 滑动窗口的位置                最大值
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7
// 示例 2：

// 输入：nums = [1], k = 1
// 输出：[1]

#include <queue>
#include <vector>
using namespace std;

// slow 解法
class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int l = 0;
    int r = k - 1;
    int max = -10001, maxId = -1;
    std::vector<int> res;
    while (r < nums.size()) {
      if (l > maxId) {
        max = -10001;
        for (int i = r; i >= l; i--) {
          if (nums[i] > max) {
            max = nums[i];
            maxId = i;
          }
        }
      } else if (nums[r] >= max) {
        max = nums[r];
        maxId = r;
      }
      res.push_back(nums[maxId]);
      l++;
      r++;
    }
    return res;
  }
};

// 优先队列
class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    priority_queue<pair<int, int>> q;
    for (int i = 0; i < k; ++i) {
      q.emplace(nums[i], i);
    }
    vector<int> ans = {q.top().first};
    for (int i = k; i < n; ++i) {
      q.emplace(nums[i], i);
      while (q.top().second <= i - k) {
        q.pop();
      }
      ans.push_back(q.top().first);
    }
    return ans;
  }
};

// 单调队列
class Solution {
 public:
  vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> q;
    for (int i = 0; i < k; ++i) {
      while (!q.empty() && nums[i] >= nums[q.back()]) {
        q.pop_back();
      }
      q.push_back(i);
    }

    vector<int> ans = {nums[q.front()]};
    for (int i = k; i < n; ++i) {
      while (!q.empty() && nums[i] >= nums[q.back()]) {
        q.pop_back();
      }
      q.push_back(i);
      while (q.front() <= i - k) {
        q.pop_front();
      }
      ans.push_back(nums[q.front()]);
    }
    return ans;
  }
};