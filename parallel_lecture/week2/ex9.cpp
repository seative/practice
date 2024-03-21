//OpemMP Testing the single construct
#include <cstdio>
#include <omp.h>

int main()
{
    int n = 6;
    omp_set_num_threads(n);
    int sum1 = 0;
    int sum2 = 0;
    int f = 20;

#pragma omp parallel shared(sum1, sum2)
    {
#pragma omp for
        for (int i = 0; i < f; i++)
        {
            sum1 += 1;
        }
#pragma omp single
        {
            printf("The first sum is %d\n", sum1);
        }
#pragma omp for
        for (int i = 0; i < f; i++)
        {
            sum2 += 2;
        }
#pragma omp single
        {
            printf("The sccond sum is %d\n", sum2);
        }
    }
}