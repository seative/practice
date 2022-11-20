#include <cstdio>
#include <cstdlib>
#include <omp.h>
#define CHUNKSIZE 202
#define N 2021

int main(int argc, char *argv[])
{
    int i, chunk;
    float a[N], b[N], c[N];
    for (i = 1; i <= N; i++)
    {
        a[i] = i * 1.0;
        b[i] = 2020.0 - a[i];
    }
    chunk = CHUNKSIZE;
#pragma omp parallel shared(a, b, c, chunk) private(i)
    {
#pragma omp for schedule(dynamic, chunk) nowait
        for (i = 1; i <= N; i++)
            c[i] = a[i] + b[i];
    }
    for (i = 1; i <= N; i++)
    {
        if (i % 101 == 0)
            printf("%.5f+%.5f=%.5f\n", a[i], b[i], c[i]);
    }
    return 0;
}