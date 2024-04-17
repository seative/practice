//46. 全排列

// 给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

// 示例 1：

// 输入：nums = [1,2,3]
// 输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
// 示例 2：

// 输入：nums = [0,1]
// 输出：[[0,1],[1,0]]
// 示例 3：

// 输入：nums = [1]
// 输出：[[1]]
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {

        vector<vector<int>> res;
        vector<int> permute;
        back_track(res,nums,permute,0);
        return res;
    }

        void back_track(vector<vector<int>>& ans, vector<int>& nums,vector<int>& permute,int index)
        {
            if(index==nums.size())
            {
                ans.push_back(permute);
                return;
            }

            for(int i=0;i<nums.size();++i)
            {
                if(find(permute.begin(),permute.end(),nums[i])!=permute.end())
                {
                    continue;
                }
                else
                {
                    permute.push_back(nums[i]);
                    back_track(ans,nums,permute,index+1);
                    permute.pop_back();
                }
            }
        }
};

//官方题解，也是一种回溯思路
class Solution2 {
public:
    void backtrack(vector<vector<int>>& res, vector<int>& output, int first, int len){
        // 所有数都填完了
        if (first == len) {
            res.emplace_back(output);
            return;
        }
        for (int i = first; i < len; ++i) {
            // 动态维护数组
            swap(output[i], output[first]);
            // 继续递归填下一个数
            backtrack(res, output, first + 1, len);
            // 撤销操作
            swap(output[i], output[first]);
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > res;
        backtrack(res, nums, 0, (int)nums.size());
        return res;
    }
};