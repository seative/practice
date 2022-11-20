//OpenMP testing task construct
#include <cstdio>
#include <omp.h>

int main()
{
    int n=2;
    omp_set_num_threads(n);

    #pragma omp parallel
    {
        #pragma omp single
        {
            printf("A");
            #pragma omp task
            {printf("race");}
            #pragma omp task
            {printf("car1 ");}
        }
    }
}