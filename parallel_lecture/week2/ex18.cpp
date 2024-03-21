// OpenMP testing task construct
// task 适用于不规则的循环或者说动态循环以及嵌套结构中

#include <cstdio>
#include <cstdlib>
#include <omp.h>

int fib(int n)
{
    if (n < 2)
        return n;
    int x, y;
#pragma omp task shared(x) firstprivate(n)
    {
        x = fib(n - 1);
    }
#pragma omp task shared(y) firstprivate(n)
    {
        y = fib(n - 2);
    }
#pragma omp taskwait
    return x + y;
}
int main(int argc, char *argv[])
{
    omp_set_num_threads(4);
    int n = 8;
#pragma omp parallel shared(n)
    {
#pragma omp single
        printf("fib(%d)=%d\n", n, fib(n));
    }
}