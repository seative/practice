#include <cuda_runtime.h>
#include <thrust/device_vector.h>
#include <memory>

#include <iostream>
#include <nvfunctional>
#include <type_traits>

// 定义一个简单的类
// class MyClass {
// public:
//    __host__ __device__ MyClass(int value) : value(value) {}
//     __device__ void doubleValue() {
//         value *= 2;
//     }
//     __host__ __device__ int getValue() const {
//         return value;
//     }
// private:
//     int value;
// };

// CUDA 核函数，用于在设备内存上构造 MyClass 实例并处理
template <typename T>
__global__ void createAndProcessData(nvstd::function<void(int)>* obj, T func) {
  // 使用 placement new 在设备内存上构造 MyClass 实例
  new (obj) nvstd::function<void(int)>(func);
}

 template<typename Func, typename Ret, typename... Args>
    __global__ void create_device_funcWrapper(nvstd::function<Ret(Args...)>* wrapper, Func func)
    {
      // 使用 placement new 在设备内存上构造 nvstd::function 实例
      new (wrapper) nvstd::function<Ret(Args...)>(func);
    }

__global__ void test(nvstd::function<void(int)>* obj) {
  int i = threadIdx.x;
  obj->operator()(i);
}

template <typename T>
__global__ void test2(T func) {
  int i = threadIdx.x;
  func(i);
}

struct Cpu {};
struct Gpu {};

 template<class, class Fnsig>
  class FunctionWrapper
  {
    static_assert(std::is_same_v<Fnsig, Fnsig>, "not a valid function signature");
  };

  template<typename Ret, typename... Args>
  class FunctionWrapperBase
  {
  public:
    FunctionWrapperBase() = default;
    FunctionWrapperBase(const FunctionWrapperBase&) = delete;
    FunctionWrapperBase& operator=(const FunctionWrapperBase&) = delete;

    virtual ~FunctionWrapperBase() = default;
    virtual nvstd::function<Ret(Args...)>* get_function() const = 0;
  };

  template<typename Ret, typename... Args>
  class FunctionWrapper<Ret(Args...), Cpu> : public FunctionWrapperBase<Ret, Args...>
  {
  public:
    FunctionWrapper() = default;

    ~FunctionWrapper() override = default;

    template<typename Func>
    void wrap(Func func)
    {
      if constexpr (std::is_invocable_r_v<Ret, Func, Args...>)
      {
        if (hostFuncPtr)
          hostFuncPtr.reset();
        hostFuncPtr = std::make_unique<nvstd::function<Ret(Args...)>>(func);
      }
      else
      {
        static_assert(std::is_invocable_r_v<Ret, Func, Args...>, "Function signature does not match");
      }
    }

    nvstd::function<Ret(Args...)>* get_function() const override
    {
      return hostFuncPtr.get();
    }

  private:
    std::unique_ptr<nvstd::function<Ret(Args...)>> hostFuncPtr;
  };

  template<typename Ret, typename... Args>
  class FunctionWrapper<Ret(Args...), Gpu> : public FunctionWrapperBase<Ret, Args...>
  {
  public:
    FunctionWrapper() = default;

    ~FunctionWrapper() override
    {
      if (deviceFuncPtr)
      {
        cudaFree(deviceFuncPtr);
      }
    }

    template<typename Func>
    void wrap(Func func)
    {
      if constexpr (std::is_invocable_r_v<Ret, Func, Args...>)
      {
        if (deviceFuncPtr)
        {
          cudaFree(deviceFuncPtr);
          deviceFuncPtr = nullptr;
        }
        cudaError_t err = cudaMalloc(&deviceFuncPtr, sizeof(nvstd::function<Ret(Args...)>));
        if (err != cudaSuccess)
        {
          throw std::runtime_error("Failed to allocate device memory");
        }
        create_device_funcWrapper<<<1, 1>>>(deviceFuncPtr, func);
        err = cudaDeviceSynchronize();
        if (err != cudaSuccess)
        {
          cudaFree(deviceFuncPtr);
          deviceFuncPtr = nullptr;
          throw std::runtime_error("Failed to synchronize device");
        }
      }
      else
      {
        static_assert(std::is_invocable_r_v<Ret, Func, Args...>, "Function signature does not match");
      }
    }

    nvstd::function<Ret(Args...)>* get_function() const override
    {
      return deviceFuncPtr;
    }

  private:
    nvstd::function<Ret(Args...)>* deviceFuncPtr = nullptr;
  };

  __device__ void deviceFunc(int x)
{
  printf("deviceFunc: %d\n", x*2);
}

// int main() {
//   // // 在主机上定义 MyClass 实例
//   // // nvstd::function<void(int)> h_obj
//   // nvstd::function<void(int)>* d_obj;

//   // // 在设备内存上分配 MyClass 实例的空间
//   // cudaMalloc(&d_obj, sizeof(nvstd::function<void(int)>));
//   int a = 5;

//   // // 启动 CUDA 核函数，在设备内存上构造 MyClass 实例并处理
//   // createAndProcessData<<<1, 1>>>(d_obj, [a] __device__(int x) {
//   //   x = a + pow(x * 2, 1.3);
//   //   // printf("Function 2: %d\n", x);
//   // });

//   FunctionWrapper<void(int),Gpu> wrapper;
//   // wrapper.wrap([a] __device__(int x) {
//   //   printf("x: %d\n", x);
//   //   x = a + pow(x * 2, 1.3);
//   //   printf("Function 2: %d\n", x);
//   // });
//   // wrapper.wrap(deviceFunc);

//   FunctionWrapper<void(int),Cpu> wrapperhost;
//   wrapperhost.wrap([a](int x) {
//     x = a + pow(x * 2, 1.3);
//     printf("Function 2 host: %d\n", a);
//   });

//   // wrapperhost.getHostFunction()->operator()(5);

//   // 创建 CUDA 事件
//   float milliseconds = 0;
//   cudaEvent_t start, end;
//   cudaEventCreate(&start);
//   cudaEventCreate(&end);

//   cudaEventRecord(start);
//   test<<<1, 32>>>(wrapper.get_function());
//   cudaEventRecord(end);
//   cudaEventSynchronize(end);
//   cudaEventElapsedTime(&milliseconds, start, end);
//   std::cout << "Kernel 1 execution time: " << milliseconds << " ms"
//             << std::endl;

//   // 同步设备
//   cudaDeviceSynchronize();

//   cudaEventRecord(start);
//   test2<<<1, 32>>>([a] __device__(int x) { x = a + pow(x * 2, 1.3); });
//   cudaEventRecord(end);
//   cudaEventSynchronize(end);

//   cudaEventElapsedTime(&milliseconds, start, end);
//   std::cout << "Kernel 2 execution time: " << milliseconds << " ms"
//             << std::endl;
//   // printf("Function 2: %d\n", x);

//   // // 将结果从设备复制回主机
//   // cudaMemcpy(&h_obj, d_obj, sizeof(MyClass), cudaMemcpyDeviceToHost);

//   // // 输出结果
//   // std::cout << "Processed value: " << h_obj.getValue() << std::endl;

//   // 释放设备内存上的 MyClass 实例
//   // cudaFree(d_obj);

//   return 0;
// }

// __global__ void test3(T func) {
//   int i = threadIdx.x;
//   func(i);
// }


template <typename T>
class base1 {
 protected:
  T b=10;

 public:
  int add(int a) { return a + b; }
};

template<typename T>
class son1 : public base1<T> {
  T x=0;
 public:
  int minus(int a) { return a - this->b; }
};


int main()
{
  son1<int> s;
  std::cout<<s.add(1);

}