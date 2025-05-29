// 编写一个函数来查找字符串数组中的最长公共前缀。

// 如果不存在公共前缀，返回空字符串 ""。

// 示例 1：

// 输入：strs = ["flower","flow","flight"]
// 输出："fl"
// 示例 2：

// 输入：strs = ["dog","racecar","car"]
// 输出：""
// 解释：输入不存在公共前缀。
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        string ans;
        int i = 0;
        while (1)
        {
            char temp = strs[0][i];
            for (auto &str : strs)
            {
                if (str[i] != temp && str.size() == i)
                    return ans;
            }
            ans.insert(ans.end(), temp);
            ++i;
        }
    }
};