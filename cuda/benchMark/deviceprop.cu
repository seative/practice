#include <cuda_runtime.h>
#include <iostream>

#define BLOCK_SIZE 256
__global__ void dummyKernel() {
    // 空内核函数
}

int main() {
    int deviceCount;
    cudaGetDeviceCount(&deviceCount);

    for (int device = 0; device < deviceCount; ++device) {
        cudaDeviceProp deviceProp;
        cudaGetDeviceProperties(&deviceProp, device);

        std::cout << "Device " << device << ": " << deviceProp.name << std::endl;
        std::cout << "Compute Capability: " << deviceProp.major << "." << deviceProp.minor << std::endl;
        std::cout << "L2 Cache Size: " << deviceProp.l2CacheSize << " bytes" << std::endl;
        std::cout<<  "device page-locked memory capabilities: "<<deviceProp.canMapHostMemory<<std::endl;
        std::cout << "The maximum amount of L2 cache that can be set-aside for persisting memory accesses: "<<deviceProp.persistingL2CacheMaxSize<< " bytes" << std::endl;
        std::cout << "The maximum size of the access policy window: "<<deviceProp.accessPolicyMaxWindowSize<< " bytes" << std::endl;
    
        std::cout<<"sharedMemPerBlock: "<<deviceProp.sharedMemPerBlock<< " bytes" << std::endl;
        std::cout<<"sharedMemPerMultiprocessor: "<<deviceProp.sharedMemPerMultiprocessor<< " bytes" << std::endl;

         // 计算Occupancy
        int maxActiveBlocks;
        cudaOccupancyMaxActiveBlocksPerMultiprocessor(&maxActiveBlocks, dummyKernel, BLOCK_SIZE, 0);
        int maxWarpsPerMultiprocessor = deviceProp.maxThreadsPerMultiProcessor / 32;
        std::cout << "Max active blocks: " << maxActiveBlocks << "  max warps per multiprocessor: " << maxWarpsPerMultiprocessor << std::endl;
        float occupancy = (maxActiveBlocks * (BLOCK_SIZE / 32)) / (float)maxWarpsPerMultiprocessor;
        std::cout << "Occupancy: " << occupancy * 100 << "%" << std::endl;

        // 查询内存带宽
        float memoryBandwidth = (deviceProp.memoryClockRate * 2 * (deviceProp.memoryBusWidth / 8)) / 1.0e6;
        std::cout << "Memory Bandwidth: " << memoryBandwidth << " GB/s" << std::endl;
   
    }
    return 0;
}

