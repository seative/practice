#include <iostream>

using namespace std;

class B {
public:
  int value;
};

class A {
public:
  int x = 1;
  A() {
    std::cout << "A 构造函数" << std::endl;
    std::cout << " static y" << A::y.value << std::endl;
  }
  static B y;

public:
  void foo() {
    auto lam = [*this]() mutable {
      x = 2;
      std::cout << x << std::endl;
    };
    lam();
  }
};

B A::y;

A b;

int main() {
  std::cout << "---------------" << std::endl;
  A a;
  a.foo();
  static A testA;
  std::cout << a.x;
  return 0;
}