// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

// 示例 1：
// 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
// 输出：6
// 解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
// 示例 2：

// 输入：height = [4,2,0,3,2,5]
// 输出：9
#include <vector>
using namespace std;
class Solution {
public:
  int trap(vector<int>& height) {
    std::vector<int> dp(height.size(),0);
    for(int i=1;i<height.size();++i)
    {
        if(height[i]<height[i-1])
           dp[i]=dp[i-1];
        else{
            int maxId=i-1;;
            for(int j=i-1; j>=0;--j)
            {
              if(height[j]>=height[i])
               {
                maxId=j;
                 break;
                }
              else 
                maxId =height[j]>height[maxId]? j:maxId; 
            }
        
            int minElem=height[i]>height[maxId]?height[maxId]:height[i];
            int sum=0;
            for(int j=maxId+1;j<i;++j)
            {
                sum+=minElem-height[j];
            }
            dp[i]=dp[maxId]+sum;
            }
        }

    return dp[height.size()-1];
  }
 };

// 双指针解法
class Solution2 {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (height[left] < height[right]) {
                ans += leftMax - height[left];
                ++left;
            } else {
                ans += rightMax - height[right];
                --right;
            }
        }
        return ans;
    }
};