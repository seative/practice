#include <benchmark/benchmark.h>

#include <cmath>
#include <functional>
#include <iostream>

// 定义一个简单的函数
void simpleFunction(int x) {
  double y = std::sin(x) * std::cos(x);
  double z = std::exp(y) + std::log(x + 1);
  double k = std::sqrt(z) * std::tan(y);
  double result = k + y - z;
}

// 基准测试：直接调用
static void BM_DirectCall(benchmark::State& state) {
  for (auto _ : state) {
    for (int i = 0; i < 1000000; ++i) {
      simpleFunction(i);
    }
  }
}
BENCHMARK(BM_DirectCall);

// 基准测试：单层 std::function 调用
static void BM_SingleLayer(benchmark::State& state) {
  std::function<void(int)> func = simpleFunction;
  for (auto _ : state) {
    for (int i = 0; i < 1000000; ++i) {
      func(i);
    }
  }
}
BENCHMARK(BM_SingleLayer);

// 基准测试：双层 std::function 调用
static void BM_DoubleLayer(benchmark::State& state) {
  std::function<void(int)> func = simpleFunction;
  std::function<void(int)> func2 = [func](int x) { func(x); };
  for (auto _ : state) {
    for (int i = 0; i < 1000000; ++i) {
      func2(i);
    }
  }
}
BENCHMARK(BM_DoubleLayer);

// 基准测试：三层 std::function 调用
static void BM_TripleLayer(benchmark::State& state) {
  std::function<void(int)> func = simpleFunction;
  std::function<void(int)> func2 = [func](int x) { func(x); };
  std::function<void(int)> func3 = [func2](int x) { func2(x); };
  for (auto _ : state) {
    for (int i = 0; i < 1000000; ++i) {
      func3(i);
    }
  }
}
BENCHMARK(BM_TripleLayer);

int main(int argc, char** argv) {
  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
  return 0;
}

// int main()
// {
//     auto a = [](int a) {};
//     std::function<void(int)> b = a;

//     void(*func)(int) = [](int a) {};

//     std::cout << sizeof(a) << std::endl;
//     std::cout << sizeof(b) << std::endl;
// }