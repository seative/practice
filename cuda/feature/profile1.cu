#include <cuda_runtime.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>

__global__ void test1(float* C, int max)
{
 int threadId=blockIdx.x*blockDim.x+threadIdx.x;
 if(threadId<max)
 {
   C[threadId]=(float)(threadId);
 }
}

__global__ void test2(float* C, int max)
{
 int threadId=blockIdx.x*blockDim.x+threadIdx.x;
 if(threadId<max)
 {
   C[threadId*129]=(float)(threadId);
 }
}

__global__ void test3(float* C, int max)
{
 int threadId=blockIdx.x*blockDim.x+threadIdx.x;
 if(threadId<max)
 {
   C[threadId*7]=(float)(threadId);
 }
}


int main()
{
  thrust::device_vector<float>  d_c(16*256*129); 
  test1<<<16,256>>>(thrust::raw_pointer_cast(d_c.data()),16*256);
  test2<<<16,256>>>(thrust::raw_pointer_cast(d_c.data()),16*256);
  test3<<<16,256>>>(thrust::raw_pointer_cast(d_c.data()),16*256);
  cudaDeviceSynchronize();
}