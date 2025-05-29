#include <cuda_runtime.h>
#include <cublas_v2.h>

#include <cassert>
#include <cmath>
#include <iostream>

struct Matrix {
  int width;
  int height;
  float* elements;
};

#define BLOCK_SIZE 16

__global__ void clear(Matrix C)
{
  int row=blockIdx.y*blockDim.y+threadIdx.y;
  int col=blockIdx.x*blockDim.x+threadIdx.x;
  if(row<C.height && col<C.width)
  {
    C.elements[row*C.width+col]=0;
  }
}

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

__global__ void matMul_shared2(Matrix A, Matrix B, Matrix C) {
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

    // if (aRow < A.height && aCol < A.width) {
    //   As[ty][tx] = A.elements[aRow * A.width + aCol];
    // } else {
    //   As[ty][tx] = 0.0f;
    // }
    As[ty][tx] = A.elements[aRow * A.width + aCol];

    // if (bRow < B.height && bCol < B.width) {
    //   Bs[tx][ty] = B.elements[bRow * B.width + bCol];
    // } else {
    //   Bs[tx][ty] = 0.0f;
    // }
    Bs[ty][tx] = B.elements[bRow * B.width + bCol];
    __syncthreads();

    for (int k = 0; k < BLOCK_SIZE; ++k) {
      Cvalue += As[ty][k] * Bs[k][tx];
    }
    __syncthreads();
  }
  // 将结果写入全局内存
  int cRow = by * BLOCK_SIZE + ty;
  int cCol = bx * BLOCK_SIZE + tx;
  // if (cRow < C.height && cCol < C.width) 
  {
    C.elements[cRow * C.width + cCol] = Cvalue;
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
    int bRow = m * BLOCK_SIZE + tx;
    int bCol = bx * BLOCK_SIZE + ty;

    // if (aRow < A.height && aCol < A.width) {
    //   As[ty][tx] = A.elements[aRow * A.width + aCol];
    // } else {
    //   As[ty][tx] = 0.0f;
    // }
    As[ty][tx] = A.elements[aRow * A.width + aCol];

    // if (bRow < B.height && bCol < B.width) {
    //   Bs[tx][ty] = B.elements[bRow * B.width + bCol];
    // } else {
    //   Bs[tx][ty] = 0.0f;
    // }
    Bs[tx][ty] = B.elements[bRow * B.width + bCol];
    __syncthreads();

    for (int k = 0; k < BLOCK_SIZE; ++k) {
      Cvalue += As[ty][k] * Bs[k][tx];
    }
    __syncthreads();
  }
  // 将结果写入全局内存
  int cRow = by * BLOCK_SIZE + ty;
  int cCol = bx * BLOCK_SIZE + tx;
  // if (cRow < C.height && cCol < C.width) 
  {
    C.elements[cRow * C.width + cCol] = Cvalue;
  }
}

const int BLOCK_SIZE_M=128;  // height of block of C that each  block calculate
const int BLOCK_SIZE_K =8 ;// width of block of A that each  block load into shared memory
const int BLOCK_SIZE_N=128;  // width of block of C that each  block calculate
const int THREAD_SIZE_Y=8; // height of block of C that each thread calculate
const int THREAD_SIZE_X=8;  // width of block of C that each thread calculate
// const bool ENABLE_DOUBLE_BUFFER=0; // whether enable double buffering or not


__global__ void matMul_register(Matrix A,Matrix B,Matrix C)
{
  __shared__ float As[BLOCK_SIZE_M][BLOCK_SIZE_K];
  __shared__ float Bs[BLOCK_SIZE_K][BLOCK_SIZE_N];
  float accum[THREAD_SIZE_Y][THREAD_SIZE_X] = {0};

  int bx=blockIdx.x;
  int by=blockIdx.y;

  int tx=threadIdx.x;
  int ty=threadIdx.y;
  int tid=ty*blockDim.x+tx;

  int tNum=BLOCK_SIZE_M*BLOCK_SIZE_K/(blockDim.x*blockDim.y); 
  int stride= BLOCK_SIZE_M/tNum;

  int mapTx= tid%BLOCK_SIZE_K;
  int mapTy= tid/BLOCK_SIZE_K;

  for(int k=0;k< A.width/BLOCK_SIZE_K;++k)
  {
    int aRow= mapTy + by * BLOCK_SIZE_M;
    int aCol= mapTx + k * BLOCK_SIZE_K;
   
    int bRow= mapTx + k * BLOCK_SIZE_K;
    int bCol= mapTy + bx * BLOCK_SIZE_N;

    for(int i=0;i<tNum;++i)
    {
      As[mapTy+i*stride][mapTx]= A.elements[(aRow+i*stride) * A.width + aCol];
      Bs[mapTx][mapTy+i*stride]= B.elements[bRow * B.width + bCol + i*stride];
    }
    __syncthreads();

  // float regisM[THREAD_SIZE_Y][BLOCK_SIZE_K];
  // float regisN[BLOCK_SIZE_K][THREAD_SIZE_X];
  //   for(int j=0; j< THREAD_SIZE_Y; ++j)
  //   {
  //     for(int i=0; i< BLOCK_SIZE_K; ++i)
  //     {
  //        regisM[j][i]= As[ty*THREAD_SIZE_Y+j][i];
  //     }
  //   }

  //   for(int j=0; j< THREAD_SIZE_X; ++j)
  //   {
  //     for(int i=0; i< BLOCK_SIZE_K; ++i)
  //     {
  //        regisN[i][j]= Bs[i][tx*THREAD_SIZE_X+j];
  //     }
  //   }

  //   for(int j=0; j< THREAD_SIZE_Y; ++j)
  //   {
  //     for(int i=0; i< THREAD_SIZE_X; ++i)
  //     {
  //       for(int l=0; l< BLOCK_SIZE_K; ++l)
  //       {
  //         accum[j][i]+= regisM[j][l]*regisN[l][i];
  //       }
  //     }
  //   }

  float regisM[THREAD_SIZE_Y];
  float regisN[THREAD_SIZE_X];

  for(int k=0;k<BLOCK_SIZE_K;++k)
  {
    for(int i=0; i< THREAD_SIZE_Y; ++i)
    {
      regisM[i]= As[ty*THREAD_SIZE_Y+i][k];
    }

    for(int i=0; i< THREAD_SIZE_X; ++i)
    {
      regisN[i]= Bs[k][tx*THREAD_SIZE_X+i];
    }

    for(int i=0; i< THREAD_SIZE_Y; ++i)
    {
      for(int j=0; j< THREAD_SIZE_X; ++j)
      {
        accum[i][j]+= regisM[i]*regisN[j];
      }
    }
  }

    __syncthreads();
  }

  int cRowF= by * BLOCK_SIZE_M + ty*THREAD_SIZE_Y ;
  int cColF= bx * BLOCK_SIZE_N + tx*THREAD_SIZE_X ;

  for(int j=0; j< THREAD_SIZE_Y; ++j)
  {
    for(int i=0; i< THREAD_SIZE_X; ++i)
    {
        int cRow= cRowF+j;
        int cCol= cColF+i;
        if(cRow < C.height && cCol < C.width)
        {
          C.elements[cRow * C.width + cCol] = accum[j][i];
        }
    }
  }
}


void matMulCublas(cublasHandle_t& handle, Matrix d_A,Matrix d_B, Matrix d_C,float alpha=1.0f,float beta=0.0f)
 {
    // 调用 cuBLAS 函数进行矩阵乘法
    cublasSgemm(handle,
                CUBLAS_OP_N, CUBLAS_OP_N,
                d_C.width, d_C.height, d_A.width,
                &alpha,
                d_B.elements, d_B.width,
                d_A.elements, d_A.width,
                &beta,
                d_C.elements, d_C.width);
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

  clear<<<dimGrid, dimBlock>>>(d_C);
  cudaEventRecord(start);
  matMul_shared<<<dimGrid, dimBlock>>>(d_A, d_B, d_C);
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&milliseconds, start, stop);
  std::cout << "Shared Kernel execution time: " << milliseconds << " ms"
            << std::endl;

  clear<<<dimGrid, dimBlock>>>(d_C);
  cudaEventRecord(start);
  matMul_shared2<<<dimGrid, dimBlock>>>(d_A, d_B, d_C);
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&milliseconds, start, stop);
  std::cout << "Shared2 Kernel execution time: " << milliseconds << " ms"
            << std::endl;

  dimGrid.x=d_A.width/BLOCK_SIZE_M;
  dimGrid.y=d_B.width/BLOCK_SIZE_N;

  dimBlock.x=BLOCK_SIZE_M/THREAD_SIZE_X;
  dimBlock.y=BLOCK_SIZE_N/THREAD_SIZE_Y;
  clear<<<dimGrid, dimBlock>>>(d_C);
  cudaEventRecord(start);
  matMul_register<<<dimGrid, dimBlock>>>(d_A, d_B, d_C);
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&milliseconds, start, stop);
  std::cout << "Register Kernel execution time: " << milliseconds << " ms"
            << std::endl;

  clear<<<dimGrid, dimBlock>>>(d_C);
  cublasHandle_t handle;
  cublasCreate(&handle);
  cudaEventRecord(start);
  matMulCublas(handle,d_A, d_B, d_C);
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&milliseconds, start, stop);
  std::cout << "Cublas Kernel execution time: " << milliseconds << " ms"
            << std::endl;
  cublasDestroy(handle);

  // 销毁 CUDA 事件
  cudaEventDestroy(start);
  cudaEventDestroy(stop);
  cudaDeviceSynchronize();
}

int main() {
  int M = 2048;
  int K = 2048;
  int N = 2048;
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
      // std::cout<<i * N + j<<" "<<C.elements[i * N + j]<<" "<<C_cpu.elements[i * N + j]<<std::endl;
      assert(fabs(C.elements[i * N + j] - C_cpu.elements[i * N + j]) < 1e-2);
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
