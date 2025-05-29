// 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

// 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

// // 你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

// 示例 1:

// 输入: [3,2,1,5,6,4], k = 2
// 输出: 5
// 示例 2:

// 输入: [3,2,3,1,2,4,5,5,6], k = 4
// 输出: 4

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;
class Solution {
 public:
  void quickSoft(vector<int>& nums, int l, int r, int k) {
    if (l >= r) return;
    int begin = l;
    int end = r;
    int random = rand() % (r - l + 1) + l;
    int privot = nums[random];
    swap(nums[begin], nums[random]);
    while (l < r) {
      while (l < r && nums[r] >= privot) r--;
      while (l < r && nums[l] <= privot) l++;
      swap(nums[l], nums[r]);
    }
    swap(nums[begin], nums[l]);
    if (k <= nums.size() - l) return quickSoft(nums, l + 1, end, k);
    return quickSoft(nums, begin, l - 1, k);
  }

  int findKthLargest(vector<int>& nums, int k) {
    quickSoft(nums, 0, nums.size() - 1, k);
    return nums[nums.size() - k];
  }

  //   int findKthLargest(vector<int>& nums, int k) {
  //     std::sort(nums.begin(), nums.end());
  //     return nums[nums.size() - k];
  //   }
};

// class Solution {
//  public:
//   int findKthLargest(vector<int>& nums, int k) {
//     priority_queue<int, vector<int>, less<int>> q;
//     for (int i : nums) q.push(i);
//     for (int i = 0; i < k - 1; i++) q.pop();
//     return q.top();
//   }
// };

// 大顶堆
class Solution2 {
 public:
  void maxHeapify(vector<int>& a, int i, int heapSize) {
    int l = i * 2 + 1, r = i * 2 + 2, largest = i;
    if (l < heapSize && a[l] > a[largest]) {
      largest = l;
    }
    if (r < heapSize && a[r] > a[largest]) {
      largest = r;
    }
    if (largest != i) {
      swap(a[i], a[largest]);
      maxHeapify(a, largest, heapSize);
    }
  }

  void buildMaxHeap(vector<int>& a, int heapSize) {
    for (int i = heapSize / 2; i >= 0; --i) {
      maxHeapify(a, i, heapSize);
    }
  }

  int findKthLargest(vector<int>& nums, int k) {
    int heapSize = nums.size();
    buildMaxHeap(nums, heapSize);
    for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i) {
      swap(nums[0], nums[i]);
      --heapSize;
      maxHeapify(nums, 0, heapSize);
    }
    return nums[0];
  }
};