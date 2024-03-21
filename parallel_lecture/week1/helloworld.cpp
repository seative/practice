#include <cstdio>
#include <omp.h>
int main(int argc, char *argv[])
{
#pragma omp parallel num_threads(2)
    {
        printf("Hello World!\n");
    }
    return 0;
}