#include <iostream>
#include <map>
#include <string>
#include <variant>
#include <vector>

class A {};

using var_t = std::variant<int, long, double, std::string>;

// helper constant for the visitor #3
template <class>
inline constexpr bool always_false_v = false;

// helper type for the visitor #4
template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
// explicit deduction guide (not needed as of C++20)
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

template <typename T>
using vardoubleint = std::variant<T, double, int>;

constexpr std::array<std::pair<std::string_view, int>, 3> createMap() {
  return {{{"int", 1}, {"double", 2}, {"string", 3}}};
}

constexpr int getValue(std::string_view key) {
  constexpr auto map = createMap();
  for (const auto &pair : map) {
    if (pair.first == key) {
      return pair.second;
    }
  }
  throw std::runtime_error("Key not found");
}

class Field {
  class Functor1 {
   public:
    void operator()(int value) const {
      std::cout << "Functor1 called with value: " << value << std::endl;
    }
  };

  class Functor2 {
   public:
    void operator()(double value) const {
      std::cout << "Functor2 called with value: " << value << std::endl;
    }
  };

  class Functor3 {
   public:
    void operator()(const std::string &value) const {
      std::cout << "Functor3 called with value: " << value << std::endl;
    }
  };

 public:
  auto get_functorMap() { return m_functorMap; }
  void init() {
    m_functorMap["int"] = Functor1();
    m_functorMap["double"] = Functor2();
    m_functorMap["string"] = Functor3();
  };
  std::map<std::string, std::variant<Functor1, Functor2, Functor3>>
      m_functorMap;
};

class Consumer {
 public:
  Field m_field;
  Consumer(Field &field) : m_field(field) {}
  void consume(const std::string &key,
               const std::variant<int, double, std::string> &value) {
    std::visit(m_field.get_functorMap()[key], value);
  }
}

int main() {
  std::variant<int, double, std::string> x, y;
  x = 1;
  std::cout << x.index() << std::endl;
  std::cout << std::get<0>(x) << std::endl;
  std::cout << std::get<int>(x) << std::endl;
  y = "cache";
  x.swap(y);
  y = "chche";
  std::cout << std::get<std::string>(x) << std::endl;
  x.emplace<0>(10);
  std::cout << std::get<int>(x) << std::endl;
  int c = 3;
  x.emplace<int>(c);
  std::cout << std::get<int>(x) << std::endl;
  double d = 5;
  x.emplace<1>(d);
  std::cout << std::get<double>(x) << std::endl;
  x.emplace<std::string>(*std::get_if<std::string>(&y));
  std::cout << x.index();
  std::cout << std::get<2>(x) << std::endl;

  std::variant<double, bool, std::string> var;
  var = true;
  var = "cache";
  struct {
    void operator()(bool) { std::cout << "bool!\n"; }
    void operator()(const std::string &) { std::cout << "string!\n"; }
  } visitor;

  std::vector<var_t> vec = {10, 15l, 1.5, "hello"};

  for (auto &v : vec) {
    // 1. void visitor, only called for side-effects (here, for I/O)
    std::visit([](auto &&arg) { std::cout << arg; }, v);

    // 2. value-returning visitor, demonstrates the idiom of returning another
    // variant
    var_t w = std::visit([](auto &&arg) -> var_t { return arg + arg; }, v);

    // 3. type-matching visitor: a lambda that handles each type differently
    std::cout << ". After doubling, variant holds ";
    std::visit(
        [](auto &&arg) {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, int>)
            std::cout << "int with value " << arg << '\n';
          else if constexpr (std::is_same_v<T, long>)
            std::cout << "long with value " << arg << '\n';
          else if constexpr (std::is_same_v<T, double>)
            std::cout << "double with value " << arg << '\n';
          else if constexpr (std::is_same_v<T, std::string>)
            std::cout << "std::string with value " << arg << '\n';
          else
            static_assert(always_false_v<T>, "non-exhaustive visitor!");
        },
        w);
  }

  for (auto &v : vec) {
    // 4. another type-matching visitor: a class with 3 overloaded operator()'s
    // Note: The `(auto arg)` template operator() will bind to `int` and `long`
    //       in this case, but in its absence the `(double arg)` operator()
    //       *will also* bind to `int` and `long` because both are implicitly
    //       convertible to double. When using this form, care has to be taken
    //       that implicit conversions are handled correctly.
    std::visit(
        overloaded{[](auto arg) { std::cout << arg << ' '; },
                   [](double arg) { std::cout << std::fixed << arg << ' '; },
                   [](const std::string &arg) { std::cout << arg << ' '; }},
        v);
  }
}