//OpenMP testing combined directives and reduction clause
//calculate pi

#include <cstdio>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#define f(A) (4.0 / (1.0 + A * A))

int main()
{
    int num_threads = 8;
    omp_set_num_threads(num_threads);

    const int n = 10000000;
    int i;
    double w, x, sum, summ, pi;
    clock_t t1, t2;
    struct timeval tv1, tv2;
    struct timezone tz;
    double wt1, wt2;
    gettimeofday(&tv1, &tz);
    wt1 = omp_get_wtime();
    t1 = clock();

    /* calculate pi = integral [0..1] 4/(1+x**2) dx */
    w = 1.0 / n;
    sum = 0.0;
#pragma omp parallel for reduction(+:sum)
        for (i = 1; i <= n; i++)
        {
            x = w * ((double)i - 0.5);
            sum = sum + f(x);
        }
    pi = w * sum;

    t2 = clock();
    wt2 = omp_get_wtime();
    gettimeofday(&tv2, &tz);
    printf("computed pi = %24.16g\n", pi);
    printf("CPU time (clock)                = %12.4g sec\n", (t2 - t1) / 1000000.0);
    printf("wall clock time (omp_get_wtime) = %12.4g sec\n", wt2 - wt1);
    printf("wall clock time (gettimeofday)  = %12.4g sec\n", (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec) * 1e-6);
}