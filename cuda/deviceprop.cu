#include <cuda_runtime.h>
#include <iostream>

int main() {
    int deviceCount;
    cudaGetDeviceCount(&deviceCount);

    for (int device = 0; device < deviceCount; ++device) {
        cudaDeviceProp deviceProp;
        cudaGetDeviceProperties(&deviceProp, device);

        std::cout << "Device " << device << ": " << deviceProp.name << std::endl;
        std::cout << "L2 Cache Size: " << deviceProp.l2CacheSize << " bytes" << std::endl;
        std::cout<< "device page-locked memory capabilities: "<<deviceProp.canMapHostMemory<<std::endl;
        std::cout << "The maximum amount of L2 cache that can be set-aside for persisting memory accesses: "<<deviceProp.persistingL2CacheMaxSize<< " bytes" << std::endl;
        std::cout << "The maximum size of the access policy window: "<<deviceProp.accessPolicyMaxWindowSize<< " bytes" << std::endl;
    
        std::cout<<"sharedMemPerBlock: "<<deviceProp.sharedMemPerBlock<< " bytes" << std::endl;
        std::cout<<"sharedMemPerMultiprocessor: "<<deviceProp.sharedMemPerMultiprocessor<< " bytes" << std::endl;
   
    }
    return 0;
}

