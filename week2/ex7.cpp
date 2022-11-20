//OpemMP Testing the critical construct
#include <cstdio>
#include <omp.h>

int main(int argc, char *argv[])
{
    int a = 0, b = 0;
#pragma omp parallel num_threads(4)
    {
#pragma omp single
        a++;
#pragma omp ctitical
        b++;
    }
    printf("single:%d,ctitical:%d\n", a, b);
}