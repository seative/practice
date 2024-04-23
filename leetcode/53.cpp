// 给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

// 子数组
// 是数组中的一个连续部分。

 

// 示例 1：

// 输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
// 输出：6
// 解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
// 示例 2：

// 输入：nums = [1]
// 输出：1
// 示例 3：

// 输入：nums = [5,4,-1,7,8]
// 输出：23
 

// 提示：

// 1 <= nums.length <= 105
// -104 <= nums[i] <= 104
 

// 进阶：如果你已经实现复杂度为 O(n) 的解法，尝试使用更为精妙的 分治法 求解。

#include <vector>
using namespace std;

// class Solution {
// public:
//     int maxSubArray(vector<int>& nums) {
//         vector<int> dp(nums.size());
//         vector<int> rightId(nums.size());

//         dp[0]=nums[0];
//         rightId[0]=0;

//         for(size_t i=1;i<nums.size();++i)
//         {
//             if(nums[i]<=0)
//             {
//                 dp[i]=nums[i]<dp[i-1]?dp[i-1]:nums[i];
//             }
//             else{
//                 for(int j=i-1;j>=0;--j)
//                 {
//                     if(dp[j]>=0)
//                     {
//                         dp[i]=dp[j]+nums[i];
//                         break;
//                     }
//                 }
//             }
//         }
//         return dp[nums.size()-1];
//     }
// };

// 简洁又优雅
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int pre = 0, maxAns = nums[0];
        for (const auto &x: nums) {
            pre = max(pre + x, x);
            maxAns = max(maxAns, pre);
        }
        return maxAns;
    }
};

// 分治的解法，线段树
class Solution2 {
public:
    struct Status {
        int lSum, rSum, mSum, iSum;
    };

    Status pushUp(Status l, Status r) {
        int iSum = l.iSum + r.iSum;
        int lSum = max(l.lSum, l.iSum + r.lSum);
        int rSum = max(r.rSum, r.iSum + l.rSum);
        int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
        return (Status) {lSum, rSum, mSum, iSum};
    };

    Status get(vector<int> &a, int l, int r) {
        if (l == r) {
            return (Status) {a[l], a[l], a[l], a[l]};
        }
        int m = (l + r) >> 1;
        Status lSub = get(a, l, m);
        Status rSub = get(a, m + 1, r);
        return pushUp(lSub, rSub);
    }

    int maxSubArray(vector<int>& nums) {
        return get(nums, 0, nums.size() - 1).mSum;
    }
};