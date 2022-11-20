//OpemMP Testing the critical construct
#include <cstdio>
#include <cstdlib>
#include <omp.h>

#define SIZE 10
int main()
{
    int i;
    int max;
    int a[SIZE];
#pragma omp parallel for num_threads(2)
    for (i = 0; i < SIZE; i++)
    {
        a[i] = rand();
        int k=omp_get_thread_num();
        printf("%d,belongs to thread %d\n", a[i],k);
    }
    max = a[0];
#pragma omp parallel for num_threads(4)
    for (i = 1; i < SIZE; i++)
    {
        if (a[i] > max)
        {
#pragma omp critical
            {
                if (a[i] > max)
                    max = a[i];
            }
        }
    }
    printf("max=%d\n",max);
}