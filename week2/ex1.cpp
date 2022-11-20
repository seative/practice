#include <stdio.h>
#include <omp.h>

int main()
{
    int num_threads = 5;
    omp_set_num_threads(num_threads);
    int rank;
#pragma omp parallel
    {
        rank = omp_get_thread_num();
        int nr_threads = omp_get_num_threads();
        printf("I am thread %i of %i threads\n", rank, nr_threads);
    }
    getchar();
}