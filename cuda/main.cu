#include <cstdio>
#include <cuda_runtime.h>
#include <vector>
#include <chrono>
#include <iostream>

template <typename T>
struct CudaAllocator
{
    using value_type = T;

    T *allocate(size_t size)
    {
        T *ptr = nullptr;
        cudaMallocManaged(&ptr, size * sizeof(T));
        return ptr;
    }

    void deallocate(T *ptr, size_t size = 0)
    {
        cudaFree(ptr);
    }

    template <typename... Args>
    void construct(T *p, Args &&...args)
    {
        if constexpr (!(sizeof...(Args) == 0 && std::is_pod_v<T>))
            ::new ((void *)p) T(std::forward<Args>(args)...);
    }
};

template <int N, class T>
__global__ void kernel(T *arr)
{
    // int i = blockDim.x * blockIdx.x + threadIdx.x;
    // if (i > n)
    //     return;
    // arr[i] = i;
    for (int i = blockDim.x * blockIdx.x + threadIdx.x; i < N; i += blockDim.x * gridDim.x)
    {
        arr[i] = i;
    }
}

template <class Func>
__global__ void parallel_for(int n, Func func)
{
    for (int i = blockDim.x * blockIdx.x + threadIdx.x; i < n; i += blockDim.x * gridDim.x)
    {
        func(i);
    }
}

struct MyFunctor
{
    __device__ void operator()(int i) const
    {
        printf("number %d\n", i);
    }
};

int main()
{
    int n = 1 << 25;
    float a = 3.14f;
    std::vector<float, CudaAllocator<float>> x(n);
    std::vector<float, CudaAllocator<float>> y(n);

    for (int i = 0; i < n; ++i)
    {
        x[i] = std::rand() * (1.f / RAND_MAX);
        y[i] = std::rand() * (1.f / RAND_MAX);
    }

    parallel_for<<<n / 512, 128>>>(n, [a, x = x.data(), y = y.data()] __device__(int i)
                                   { x[i] = a * x[i] + y[i]; });

    cudaDeviceSynchronize();

    for (int i = 0; i < n; ++i)
    {
        printf("x[%d] =%f\n", i, x[i]);
    }
    // int n = 1 << 25;
    // std::vector<float, CudaAllocator<float>> arr(n);
    // std::vector<float> cpu(n);

    // std::chrono::time_point tick1 = std::chrono::system_clock::now();
    // // parallel_for<<<32, 128>>>(n, MyFunctor{});
    // for (int i = 0; i < n; ++i)
    //     cpu[i] = sinf(i);
    // std::chrono::time_point tock1 = std::chrono::system_clock::now();
    // std::cout << (tock1 - tick1).count() << std::endl;

    // std::chrono::system_clock::time_point tick2 = std::chrono::system_clock::now();
    // // parallel_for<<<32, 128>>>(n, MyFunctor{});
    // parallel_for<<<n / 512, 128>>>(n, [arr = arr.data()] __device__(int i)
    //                                { arr[i] = __sinf(i); });
    // cudaDeviceSynchronize();
    // std::chrono::system_clock::time_point tock2 = std::chrono::system_clock::now();
    // std::cout << (tock2 - tick2).count() << std::endl;
    // constexpr int n = 65535;
    // std::vector<int, CudaAllocator<int>> arr(n);
    // // int nthreads = 128;
    // // int nblocks = (n + nthreads - 1) / nthreads;
    // // int *arr;
    // // cudaMallocManaged(arr, n * sizeof(int));
    // kernel<n><<<32, 128>>>(arr.data());
    // cudaDeviceSynchronize();

    // for (int i = 0; i < n; ++i)
    // {
    //     printf("arr[%d]: %d\n", i, arr[i]);
    // }
    // // cudaFree(arr);
    return 0;
}