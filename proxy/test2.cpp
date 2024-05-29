#include <iostream>
#include <vector>

#include "proxy.h"

// 声明一个代理类，最终会通过这个代理类去调用真正的类对象的成员函数
struct draw : pro::dispatch<void()> {
  template <class T>
  void operator()(T& self) {
    self.draw();
  }
};

struct shape : pro::facade<draw> {};

// 不需要派生，不需要virtual虚函数
struct rectangle {
  void draw() { std::cout << "rectangle" << std::endl; }
};

// 不需要派生，不需要virtual虚函数
struct circle {
  void draw() { std::cout << "circle" << std::endl; }
};

int main() {
  // 这里容器元素的类型是个proxy的代理类型
  std::vector<pro::proxy<shape>> shapes;

  shapes.emplace_back(pro::make_proxy<shape>(rectangle()));
  shapes.emplace_back(pro::make_proxy<shape>(circle()));

  // 注意这里的调用方式和virtual动态多态的调用方式不同
  for (auto& p : shapes) {
    p.invoke<draw>();
  }

  // 输出：
  // rectangle
  // circle
}
