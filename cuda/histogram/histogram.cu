#include <cuda_runtime.h>
#include <iostream>



__global__ void hist_kernel(int *bins, const int nbins, const int *__restrict__ input, size_t array_size)
{
    extern __shared__ int shared_bins[];
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    for(int i=threadIdx.x; i<nbins; i+=blockDim.x)
    {
        shared_bins[i]=0;
    }
    __syncthreads();
    for (int i = tid; i < array_size; i += stride)
    {
        int bin = input[i];
        if (bin < 0 || bin >= nbins)
        {
            printf("bin %d out of range\n", bin);
        }
        atomicAdd(&shared_bins[bin], 1);
    }
    __syncthreads();

    for(int i=threadIdx.x;i<nbins;i+=blockDim.x)
    {
        atomicAdd(&bins[i],shared_bins[i]);
    }
}

int main()
{
    int arraysize=1<<8;
    int * input=(int *)malloc(arraysize*sizeof(int));

    for(int i=0;i<arraysize;i++)
    {
        input[i]=rand()%256;
    }
    
    int * bins;
    cudaMallocManaged(&bins,256*sizeof(int));
    hist_kernel<<<1,256,256*sizeof(int)>>>(bins,256,input,arraysize);
}