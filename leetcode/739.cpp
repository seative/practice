// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中
// answer[i] 是指对于第 i
// 天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0
// 来代替。

// 示例 1:

// 输入: temperatures = [73,74,75,71,69,72,76,73]
// 输出: [1,1,4,2,1,1,0,0]
// 示例 2:

// 输入: temperatures = [30,40,50,60]
// 输出: [1,1,1,0]
// 示例 3:

// 输入: temperatures = [30,60,90]
// 输出: [1,1,0]

#include <stack>
#include <vector>
using namespace std;

class Solution {
 public:
  vector<int> dailyTemperatures(vector<int>& temperatures) {
    std::stack<int> stk;
    std::vector<int> ans(temperatures.size());

    for (int i = 0; i < temperatures.size(); ++i) {
      while (!stk.empty() && temperatures[stk.top()] < temperatures[i]) {
        int cur = stk.top();
        ans[cur] = i - cur;
        stk.pop();
      }
      stk.push(i);
    }

    while (!stk.empty()) {
      int cur = stk.top();
      ans[cur] = 0;
      stk.pop();
    }

    return ans;
  }
};