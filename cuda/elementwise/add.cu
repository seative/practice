
#include <cuda_runtime.h>
#include <stdio.h>

#define CEIL(a, b) ((a + b - 1) / (b))

#define FLOAT4(value) (reinterpret_cast<float4*>(&(value))[0])

int N=1<<20;
int block_size = 1024;
int grid_size  = CEIL(N, block_size);

// 函数定义
__global__ void elementwise_add(float* a, float* b, float *c, int N) {
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    if (idx < N) {
        c[idx] = a[idx] + b[idx];
    }
    // printf("1");
}

__global__ void elementwise_add_float4(float* a, float* b, float *c, int N) {
    int idx = (blockDim.x * blockIdx.x + threadIdx.x) * 4;

    if (idx < N) {
        float4 tmp_a = FLOAT4(a[idx]);
        float4 tmp_b = FLOAT4(b[idx]);
        float4 tmp_c;
        tmp_c.x = tmp_a.x + tmp_b.x;
        tmp_c.y = tmp_a.y + tmp_b.y;
        tmp_c.z = tmp_a.z + tmp_b.z;
        tmp_c.w = tmp_a.w + tmp_b.w;
        FLOAT4(c[idx]) = tmp_c;
    }
}

int main()
{
  // 创建 CUDA 事件
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  float milliseconds = 0;

  float* a, *b, *c;
  cudaMalloc(&a, N*sizeof(float));
  cudaMalloc(&b, N*sizeof(float));
  cudaMalloc(&c, N*sizeof(float));


  cudaEventRecord(start);
  elementwise_add<<<grid_size, block_size>>>(a, b, c, N);
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&milliseconds, start, stop);
  printf("Native Kernel execution time: %f ms\n", milliseconds);

  cudaEventRecord(start);
  elementwise_add_float4<<<grid_size / 4, block_size>>>(a, b, c, N);
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&milliseconds, start, stop);
  printf("Float4 Kernel execution time: %f ms\n", milliseconds);
}