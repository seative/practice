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

__global__ void parallel_sum1(int *sum, int const *arr, int n)
{
    for (int i = blockDim.x * blockIdx.x + threadIdx.x; i < n; i += blockDim.x * gridDim.x)
    {
        sum[0] += arr[i];
        // atomicAdd(&sum[0], arr[i]);
    }
}

__global__ void parallel_sum2(int *sum, int const *arr, int n)
{
    int local_sum = 0;
    for (int i = blockDim.x * blockIdx.x + threadIdx.x; i < n; i += blockDim.x * gridDim.x)
    {
        local_sum += arr[i];
    }
    atomicAdd(&sum[0], local_sum);
}

__global__ void parallel_filter(int *sum, int *res, int const *arr, int n)
{
    for (int i = blockDim.x * blockIdx.x + threadIdx.x; i < n; i += blockDim.x * gridDim.x)
    {
        if (arr[i] >= 2)
        {
            int loc = atomicAdd(&sum[0], 1);
            res[loc] = arr[i];
        }
    }
}

__device__ __inline__ int my_atomic_add(int *dst, int src)
{
    int old = *dst, expect;
    do
    {
        expect = old;
        old = atomicCAS(dst, expect, expect + src);
    } while (expect != old);
    return old;
}

__global__ void parallel_sum3(int *sum, int const *arr, int n)
{
    int local_sum = 0;
    for (int i = blockDim.x * blockIdx.x + threadIdx.x; i < n; i += blockDim.x * gridDim.x)
    {
        local_sum += arr[i];
    }
    my_atomic_add(&sum[0], local_sum);
}

__global__ void parallel_sum4(int *sum, int const *arr, int n)
{
    for (int i = blockDim.x * blockIdx.x + threadIdx.x; i < n / 1024; i += blockDim.x * gridDim.x)
    {
        int local_sum = 0;
        for (int j = i * 1024; j < i * 1024 + 1024; j++)
        {
            local_sum += arr[j];
        }
        sum[i] = local_sum;
    }
}

__global__ void parallel_sum5(int *sum, int const *arr, int n)
{
    for (int i = blockDim.x * blockIdx.x + threadIdx.x; i < n / 1024; i += blockDim.x * gridDim.x)
    {
        int local_sum[1024];
        for (int j = 0; j < 1024; j++)
        {
            local_sum[j] = arr[i * 1024 + j];
        }
        for (int j = 0; j < 512; j++)
        {
            local_sum[j] += local_sum[j + 512];
        }
        for (int j = 0; j < 256; j++)
        {
            local_sum[j] += local_sum[j + 256];
        }
        for (int j = 0; j < 128; j++)
        {
            local_sum[j] += local_sum[j + 128];
        }
        for (int j = 0; j < 64; j++)
        {
            local_sum[j] += local_sum[j + 64];
        }
        for (int j = 0; j < 32; j++)
        {
            local_sum[j] += local_sum[j + 32];
        }
        for (int j = 0; j < 16; j++)
        {
            local_sum[j] += local_sum[j + 16];
        }
        for (int j = 0; j < 8; j++)
        {
            local_sum[j] += local_sum[j + 8];
        }
        for (int j = 0; j < 4; j++)
        {
            local_sum[j] += local_sum[j + 4];
        }
        for (int j = 0; j < 2; j++)
        {
            local_sum[j] += local_sum[j + 2];
        }
        for (int j = 0; j < 1; j++)
        {
            local_sum[j] += local_sum[j + 1];
        }
        sum[i] = local_sum[0];
    }
}

__global__ void parallel_sum6(int *sum, int const *arr, int n)
{
    __shared__ volatile int local_sum[1024];
    int j = threadIdx.x;
    int i = blockIdx.x;
    int temp_sum = 0;

    for (int t = i * 1024 + j; t < n; t += 1024 * gridDim.x)
    {
        temp_sum += arr[t];
    }

    local_sum[j] = temp_sum;
    __syncthreads();
    if (j < 512)
    {
        local_sum[j] += local_sum[j + 512];
    }
    __syncthreads();
    if (j < 256)
    {
        local_sum[j] += local_sum[j + 256];
    }
    __syncthreads();
    if (j < 128)
    {
        local_sum[j] += local_sum[j + 128];
    }
    __syncthreads();
    if (j < 64)
    {
        local_sum[j] += local_sum[j + 64];
    }
    __syncthreads();
    if (j < 32)
    {
        local_sum[j] += local_sum[j + 32];
        local_sum[j] += local_sum[j + 16];
        local_sum[j] += local_sum[j + 8];
        local_sum[j] += local_sum[j + 4];
        local_sum[j] += local_sum[j + 2];
        if (j == 0)
        {
            sum[i] = local_sum[0] + local_sum[1];
        }
    }
}

int main()
{
    int n = 1 << 24;
    std::vector<int, CudaAllocator<int>> arr(n);
    std::vector<int, CudaAllocator<int>> sum(n / 1024);

    for (int i = 0; i < n; ++i)
    {
        arr[i] = std::rand() % 4;
    }

    std::chrono::time_point tick1 = std::chrono::system_clock::now();
    // parallel_sum5<<<n / 1024, 1024>>>(sum.data(), arr.data(), n);
    parallel_sum6<<<n / 4096, 1024>>>(sum.data(), arr.data(), n);
    cudaDeviceSynchronize();

    int final_sum = 0;
    for (int i = 0; i < n / 1024; ++i)
    {
        final_sum += sum[i];
    }
    std::chrono::time_point tick2 = std::chrono::system_clock::now();
    printf("result:%d\n", final_sum);
    std::cout << (double)std::chrono::duration_cast<std::chrono::microseconds>(tick2 - tick1).count() / 1e6 << " sec" << std::endl;
    return 0;
}