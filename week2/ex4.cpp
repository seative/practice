#include <cstdio>
#include <omp.h>

int main(int argc, char *argv[])
{
    int num_threads = 12;
    int i;
    omp_set_num_threads(num_threads);
#ifdef _OPENMP
#pragma omp parallel private(i)
    {
        i = omp_get_thread_num();
        printf("hello world %d\n", i);
    }
#else
    printf("hello world %d\n", i);
#endif
}