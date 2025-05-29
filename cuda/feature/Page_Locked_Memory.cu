#include <iostream>
#include <cuda_runtime.h>

#define gpuErrChk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true) {
    if (code != cudaSuccess) {
        fprintf(stderr, "GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
        if (abort) exit(code);
    }
}

__global__ void kernel(int* data, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    if (idx < size) {
        data[idx] = idx;
    }
}

int main() {
    const int size = 1024;
    int* h_data = nullptr;
    int* d_data = nullptr;

    // 启用页锁定内存映射
    gpuErrChk(cudaSetDeviceFlags(cudaDeviceMapHost));

    // 分配页锁定内存，并映射到设备地址空间
    gpuErrChk(cudaHostAlloc(&h_data, size * sizeof(int), cudaHostAllocMapped));

    // 获取设备指针
    gpuErrChk(cudaHostGetDevicePointer(&d_data, h_data, 0));

    // 初始化页锁定内存
    for (int i = 0; i < size; ++i) {
        h_data[i] = 0;
    }

    // 启动 CUDA 内核
    kernel<<<(size + 255) / 256, 256>>>(d_data, size);

    // 检查内核启动错误
    gpuErrChk(cudaGetLastError());

    // 同步设备，确保内核执行完成
    gpuErrChk(cudaDeviceSynchronize());

    // 输出结果
    for (int i = 0; i < size; ++i) {
        std::cout << h_data[i] << " ";
    }
    std::cout << std::endl;

    // 释放内存
    gpuErrChk(cudaFreeHost(h_data));

    return 0;
}
