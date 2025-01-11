#include <cuda_runtime.h>

#include <cassert>
#include <cmath>
#include <iostream>

struct Matrix {
  int width;
  int height;
  float* elements;
};

#define BLOCK_SIZE 16

__global__ void matMul_origin(Matrix A, Matrix B, Matrix C) {
  // Each thread computes one element of C
  // by accumulating results into Cvalue
  for (int row = blockIdx.y * blockDim.y + threadIdx.y; row < A.height;
       row += blockDim.y * gridDim.y) {
    for (int col = blockIdx.x * blockDim.x + threadIdx.x; col < B.width;
         col += blockDim.x * gridDim.x) {
      float Cvalue = 0;
      for (int e = 0; e < A.width; ++e)
        Cvalue += A.elements[row * A.width + e] * B.elements[e * B.width + col];
      C.elements[row * C.width + col] = Cvalue;
    }
  }
}

__global__ void matMul_shared(Matrix A, Matrix B, Matrix C) {
  __shared__ float As[BLOCK_SIZE][BLOCK_SIZE];
  __shared__ float Bs[BLOCK_SIZE][BLOCK_SIZE];

  int bx = blockIdx.x;
  int by = blockIdx.y;

  int tx = threadIdx.x;
  int ty = threadIdx.y;

  float Cvalue = 0;
  for (int m = 0; m < (A.width+BLOCK_SIZE-1) / BLOCK_SIZE; ++m) {
    int aRow = by * BLOCK_SIZE + ty;
    int aCol = m * BLOCK_SIZE + tx;
    int bRow = m * BLOCK_SIZE + ty;
    int bCol = bx * BLOCK_SIZE + tx;

    if (aRow < A.height && aCol < A.width) {
      As[ty][tx] = A.elements[aRow * A.width + aCol];
    } else {
      As[ty][tx] = 0.0f;
    }

    if (bRow < B.height && bCol < B.width) {
      Bs[ty][tx] = B.elements[bRow * B.width + bCol];
    } else {
      Bs[ty][tx] = 0.0f;
    }
    __syncthreads();

    for (int k = 0; k < BLOCK_SIZE; ++k) {
      Cvalue += As[ty][k] * Bs[k][tx];
    }
    __syncthreads();
  }
  // 将结果写入全局内存
  int cRow = by * BLOCK_SIZE + ty;
  int cCol = bx * BLOCK_SIZE + tx;
  if (cRow < C.height && cCol < C.width) {
    C.elements[cRow * C.width + cCol] = Cvalue;
  }
}

const int BLOCK_SIZE_M=128;  // height of block of C that each  block calculate
const int BLOCK_SIZE_K =8 ;// width of block of A that each  block load into shared memory
const int BLOCK_SIZE_N=128;  // width of block of C that each  block calculate
const int THREAD_SIZE_Y=8; // height of block of C that each thread calculate
const int THREAD_SIZE_X=8;  // width of block of C that each thread calculate
const bool ENABLE_DOUBLE_BUFFER=0; // whether enable double buffering or not


__global__ void matMul_register(Matrix A,Matrix B,Matrix C)
{
  __shared__ float As[BLOCK_SIZE_M][BLOCK_SIZE_K];
  __shared__ float Bs[BLOCK_SIZE_K][BLOCK_SIZE_N];

  int bx=blockIdx.x;
  int by=blockIdx.y;

  int tx=threadIdx.x;
  int ty=threadIdx.y;
  int tid=ty*blockDim.x+tx;
  int tNum=BLOCK_SIZE_M*BLOCK_SIZE_K/(blockDim.x*blockDim.y); 

  int stride= BLOCK_SIZE_M/tNum;

  // tNum/8

  float Cvalue = 0;
  for(int k=0;k< A.width/BLOCK_SIZE_K;++k)
  {
    int aCol= tid % BLOCK_SIZE_K+ k * BLOCK_SIZE_K;
    int aRow= tid / BLOCK_SIZE_K+ by * BLOCK_SIZE_M;

    int bRow= tid % BLOCK_SIZE_K+ k * BLOCK_SIZE_K;
    int bCol= tid / BLOCK_SIZE_K+ bx * BLOCK_SIZE_N;

    for(int i=0;i<tNum;++i)
    {
      As[tid/BLOCK_SIZE_K+i*stride][tid%BLOCK_SIZE_K]= A.elements[(aRow+i*stride) * A.width + aCol];
      Bs[tid%BLOCK_SIZE_K][tid/BLOCK_SIZE_K+i*stride]= B.elements[(bRow+i*stride) * B.width + bCol];
    }
    __syncthreads();
    for (int k = 0; k < BLOCK_SIZE; ++k) 
    {
      Cvalue += As[ty][k] * Bs[k][tx];
    }
    __syncthreads();
  }
}

void matMul(const Matrix d_A, const Matrix d_B, Matrix d_C) {
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);
  // Invoke kernel
  dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
  dim3 dimGrid(d_B.width / dimBlock.x, d_A.height / dimBlock.y);

  // 记录开始时间
  cudaEventRecord(start);
  matMul_origin<<<dimGrid, dimBlock>>>(d_A, d_B, d_C);
  cudaEventRecord(stop);
  // 等待事件完成
  cudaEventSynchronize(stop);
  // 计算时间差
  float milliseconds = 0;
  cudaEventElapsedTime(&milliseconds, start, stop);
  // 打印执行时间
  std::cout << "Origin Kernel execution time: " << milliseconds << " ms"
            << std::endl;

  cudaEventRecord(start);
  matMul_shared<<<dimGrid, dimBlock>>>(d_A, d_B, d_C);
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&milliseconds, start, stop);
  std::cout << "Shared Kernel execution time: " << milliseconds << " ms"
            << std::endl;

  // 销毁 CUDA 事件
  cudaEventDestroy(start);
  cudaEventDestroy(stop);
}

int main() {
  int M = 1024;
  int K = 1024;
  int N = 521;
  // 分配主机内存
  Matrix A, B, C;
  A.height = M;
  A.width = K;
  B.height = K;
  B.width = N;
  C.height = M;
  C.width = N;

  A.elements = (float*)malloc(M * K * sizeof(float));
  B.elements = (float*)malloc(K * N * sizeof(float));
  C.elements = (float*)malloc(M * N * sizeof(float));

  // 初始化矩阵 A 和 B
  for (int i = 0; i < M * K; ++i) {
    A.elements[i] = static_cast<float>(rand()) / RAND_MAX;
  }
  for (int i = 0; i < K * N; ++i) {
    B.elements[i] = static_cast<float>(rand()) / RAND_MAX;
  }

  // 创建 CUDA 事件
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  Matrix d_A;
  d_A.width = A.width;
  d_A.height = A.height;
  size_t size = A.width * A.height * sizeof(float);
  cudaMalloc(&d_A.elements, size);
  cudaMemcpy(d_A.elements, A.elements, size, cudaMemcpyHostToDevice);
  Matrix d_B;
  d_B.width = B.width;
  d_B.height = B.height;
  size = B.width * B.height * sizeof(float);
  cudaMalloc(&d_B.elements, size);
  cudaMemcpy(d_B.elements, B.elements, size, cudaMemcpyHostToDevice);

  // Allocate C in device memory
  Matrix d_C;
  d_C.width = C.width;
  d_C.height = C.height;
  size = C.width * C.height * sizeof(float);
  cudaMalloc(&d_C.elements, size);

  matMul(d_A, d_B, d_C);

  // Read C from device memory
  cudaMemcpy(C.elements, d_C.elements, size, cudaMemcpyDeviceToHost);

  // check the result
  Matrix C_cpu;
  C_cpu.height = M;
  C_cpu.width = N;
  C_cpu.elements = (float*)malloc(M * N * sizeof(float));
  for (int i = 0; i < M; ++i) {
    for (int j = 0; j < N; ++j) {
      float sum = 0;
      for (int k = 0; k < K; ++k) {
        sum += A.elements[i * K + k] * B.elements[k * N + j];
      }
      C_cpu.elements[i * N + j] = sum;
      assert(fabs(C.elements[i * N + j] - C_cpu.elements[i * N + j]) < 1e-4);
    }
  }

  // Free device memory
  cudaFree(d_A.elements);
  cudaFree(d_B.elements);
  cudaFree(d_C.elements);

  // 释放主机内存
  free(A.elements);
  free(B.elements);
  free(C.elements);
  free(C_cpu.elements);
}
