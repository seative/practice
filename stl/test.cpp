#include "std_shared_ptr.h"
#include "std_weak_ptr.h"

#include <iostream>
#include <memory>

int main() {
  shared_ptr<int> a(new int(1));
  shared_ptr<int> b(new int(2));
  shared_ptr<int> c(new int(2));
  shared_ptr<int> d;

  a = b;
  a = c;
  std::cout << a.use_count() << "\n";
  std::cout << b.use_count() << "\n";
  d = a;
  std::cout << a.use_count() << "\n";
  std::cout << d.use_count() << "\n";

  weak_ptr<int> e(d);
  std::cout << e.use_count() << "\n";
  std::cout << e.expired() << "\n";

  e.lock();
  std::cout << e.use_count() << "\n";
  return 0;
}