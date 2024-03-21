#include <iostream>
#include <type_traits>

template <typename T>
concept always_satisfied = true;

// 一个约束T只能是整数类型的concept，整数类型包括 char, unsigned char, short,
// ushort, int, unsinged int, long等。
template <typename T>
concept integral = std::is_integral_v<T>;

// 一个约束T只能是整数类型，并且是有符号的concept
template <typename T>
concept signed_integral = integral<T> && std::is_signed_v<T>;

template <signed_integral c> int func(c c1) { return 1; }

template <typename T, std::enable_if_t<std::is_integral_v<T>, T> = 0>
T add_original(T a, T b) {
  return a + b;
}

int main() {
  std::cout << func(1) << std::endl;

  std::vector<int> bb;
  std::cout << add_original(1, 1) << std::endl;
}