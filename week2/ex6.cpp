//OpemMP Testing the for construct
#include <cstdio>
#include <cstdlib>
#include <omp.h>

int main(int argc, char * argv[])
{
    int n=5;
    omp_set_num_threads(n);

    int * iterations;
    iterations=(int*) malloc (n*sizeof(int));

    int f=150;

    for(int loop=0;loop<n;loop++)
    {
        iterations[loop]=0;
    }
    #pragma omp parallel shared(iterations,f) 
    {
        #pragma omp for
        for(int i=0;i<f;i++)
        {
            iterations[omp_get_thread_num()]++;
        }
    }
    for(int loop=0;loop<n;loop++)
    {
        printf("%d",iterations[loop]);
    }
    free(iterations);
}