// 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。

// 判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。

 

// 示例 1：

// 输入：nums = [2,3,1,1,4]
// 输出：true
// 解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
// 示例 2：

// 输入：nums = [3,2,1,0,4]
// 输出：false
// 解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。
 

// 提示：

// 1 <= nums.length <= 104
// 0 <= nums[i] <= 105

#include<vector>
using namespace std;

// Dp做法，超出时间限制，但可行
class Solution {
public:
    bool canJump(vector<int>& nums) {

    vector<bool> dp(nums.size(),false);
    dp[0]=true;

    for(int i=1;i<nums.size();++i)
    {
        vector<int> mark;
        for(int j=0;j<i;++j)
        {
            if(nums[j]>=i-j)
            {
                mark.push_back(j);
            }
        }
        for(int k=0;k<mark.size();++k)
        {
            if(dp[mark[k]])
            {
                dp[i]=true;
                break;
            }
        }
    }
    return dp[nums.size()-1];
    }
};

class Solution2 {
public:
    bool canJump(vector<int>& nums) {
      return canJumpIndex(nums,nums.size()-1);
    }

    bool canJumpIndex(vector<int>& nums,size_t index)
    {
        if(index==0)
        {
            return true;
        }

        int maxDist= index;
        for(int i=index-1;i>=0;--i)
        {
            if(nums[i]>=index-i)
            {
                maxDist=i;
            }
        }
        if(maxDist==index)
        {
            return false;
        }
        return canJumpIndex(nums,maxDist);
    }
};


// 也是一种动态规划思路，但是不需要额外的空间，维护每个下标所能到达的最远距离
class Solution3 {
public:
    bool canJump(vector<int>& nums) {
        int k = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i > k) return false;
            k = max(k, i + nums[i]);
        }
        return true;
    }
};