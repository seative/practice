#include <cstdio>
#include <omp.h>

int main(int argc, char *argv[])
{
    int rank;
#ifdef _OPENMP
#pragma omp parallel num_threads(4) private(rank)
    {
        rank = omp_get_thread_num();
        int nr_threads = omp_get_num_threads();
        printf("I am thread %i of %i threads;\n", rank, nr_threads);
    }
#else
    {
        printf("This program is not compiled with OpenMP\n");
    }
#endif
}