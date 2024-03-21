#include "ScalarFieldOp.h"
#include <typeinfo>
#include <vector>
#include <iostream>
#include <cxxabi.h>

namespace tf
{
  template <typename T>
  class ScalarFieldTest : public ScalarFieldOp<T, ScalarFieldTest<T>>
  {
  public:
    T operator()(size_t id) const
    {
      return value[id];
    }

  public:
    std::vector<T> value;
  };
}

int main()
{
  tf::ScalarFieldTest<double> sf;
  sf.value = {1, 3, 6, 7, 9, 11};

  auto r1 = sf + sf;
  // EXPECT_DOUBLE_EQ(r1(2), 12);
  // EXPECT_DOUBLE_EQ(r1(4), 18);

  auto r2 = sf + static_cast<double>(3);
  // EXPECT_DOUBLE_EQ(r2(1), 6);
  // EXPECT_DOUBLE_EQ(r2(3), 10);

  auto r3 = static_cast<double>(4) + sf;
  // EXPECT_DOUBLE_EQ(r3(0), 5);
  // EXPECT_DOUBLE_EQ(r3(2), 10);

  auto r4 = r1 + r3 + r2 + r3;
  // int status;
  // const std::type_info &ti = typeid(r4);
  // char *realname = abi::__cxa_demangle(ti.name(), 0, 0, &status);
  // std::cout << "\t=> " << realname << "\t: " << '\n';
  // free(realname);
  std::cout << r4(0) << std::endl;
  std::cout << r4(2) << std::endl;
  std::cout << r4(5) << std::endl;
  // EXPECT_DOUBLE_EQ(r4(0), 11);
  // EXPECT_DOUBLE_EQ(r4(2), 31);
  // EXPECT_DOUBLE_EQ(r4(5), 51);
}