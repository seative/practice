#include "minor_shared_ptr.h"

using namespace minor_stl;

int main() {
  shared_ptr<int> p1(new int(42));
  shared_ptr<int> p2 = p1;

  std::cout << p1.get() << std::endl;
  std::cout << p2.get() << std::endl;
  std::cout << p1.use_count() << std::endl;
  p2.~shared_ptr<int>();
  std::cout << p1.use_count() << std::endl;

  shared_ptr<int> p3 = new int(43);
  p1 = p3;
  std::cout << p1.use_count() << std::endl;
  return 0;
}