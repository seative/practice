// 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

// 实现 MinStack 类:

// MinStack() 初始化堆栈对象。
// void push(int val) 将元素val推入堆栈。
// void pop() 删除堆栈顶部的元素。
// int top() 获取堆栈顶部的元素。
// int getMin() 获取堆栈中的最小元素。

// 示例 1:

// 输入：
// ["MinStack","push","push","push","getMin","pop","top","getMin"]
// [[],[-2],[0],[-3],[],[],[],[]]

// 输出：
// [null,null,null,null,-3,null,0,-2]

// 解释：
// MinStack minStack = new MinStack();
// minStack.push(-2);
// minStack.push(0);
// minStack.push(-3);
// minStack.getMin();   --> 返回 -3.
// minStack.pop();
// minStack.top();      --> 返回 0.
// minStack.getMin();   --> 返回 -2.

#include <vector>
using namespace std;

// 每次建立元素都要遍历一遍栈，效率很低
class MinStack {
  std::vector<int> stack;

  int minVal;

  void updateMin() {
    minVal = INT_MAX;
    for (int i = 0; i < stack.size(); ++i) {
      minVal = min(minVal, stack[i]);
    }
  }

 public:
  MinStack() {}

  void push(int val) {
    stack.push_back(val);
    updateMin();
  }

  void pop() {
    stack.pop_back();
    updateMin();
  }

  int top() { return stack.back(); }

  int getMin() { return minVal; }
};

class MinStack2 {
  std::vector<int> stack;

  std::vector<int> minStack;

 public:
  MinStack2() {}

  void push(int val) {
    stack.push_back(val);
    minStack.push_back(min(minStack.empty() ? INT_MAX : minStack.back(), val));
  }

  void pop() {
    stack.pop_back();
    MinStack.pop_back();
  }

  int top() { return stack.back(); }

  int getMin() { return minStack.back(); }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */