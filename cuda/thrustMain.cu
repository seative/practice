#include <cstdio>
#include <cuda_runtime.h>
#include <vector>
#include <chrono>
#include <iostream>

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

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
__global__ void parallel_sum(int *sum, int const *arr, int n)
{
    for (int i = blockDim.x * blockIdx.x + threadIdx.x; i < n; i += blockDim.x * gridDim.x)
    {
        // sum[0] += arr[i];
        atomicAdd(&sum[0], arr[i]);
    }
}

int main()
{
    int n = 65536;
    std::vector<int, CudaAllocator<int>> arr(n);
    std::vector<int, CudaAllocator<int>> sum(1);
    // thrust::device_vector<int> arr(n);
    // thrust::device_vector<int> sum(1);

    for (int i = 0; i < n; ++i)
    {
        arr[i] = std::rand() % 4;
    }

    std::chrono::time_point tick1 = std::chrono::system_clock::now();
    parallel_sum<<<n / 128, 128>>>(sum.data(), arr.data(), n);
    cudaDeviceSynchronize();
    std::chrono::time_point tick2 = std::chrono::system_clock::now();
    printf("result:%d\n", sum[0]);
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tick2 - tick1).count() << std::endl;
    // float a = 3.14f;
    // thrust::host_vector<float> x_host(n);
    // thrust::device_vector<float> x_dev(n);

    // thrust::for_each(x_host.begin(), x_host.end(), [](float &x)
    //                  { x = std::rand() * (1.f / RAND_MAX); });
    // thrust::for_each(x_dev.begin(), x_dev.end(), [] __device__(float &x)
    //                  { x += 100.f; });

    // thrust::for_each(thrust::make_counting_iterator(0), thrust::make_counting_iterator(10), [] __device__(int i)
    //                  { printf("%d", i); });
    // for (int i = 0; i < n; ++i)
    // {
    //     x_host[i] = std::rand() * (1.f / RAND_MAX);
    //     y_host[i] = std::rand() * (1.f / RAND_MAX);
    // }

    // thrust::device_vector<float> x_dev = x_host;
    // thrust::device_vector<float> y_dev = y_host;

    // parallel_for<<<n / 512, 128>>>(n, [a, x = x_dev.data(), y = y_dev.data()] __device__(int i)
    //                                { x[i] = a * x[i] + y[i]; });

    // x_host = x_dev;

    // for (int i = 0; i < n; ++i)
    // {
    //     printf("x[%d] =%f\n", i, x_host[i]);
    // }
    // cudaDeviceSynchronize();
    return 0;
}