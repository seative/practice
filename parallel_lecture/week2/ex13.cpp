//OpenMP testing private and shared variables
#include <cstdio>
#include <omp.h>

int main(int argc ,char * argv[])
{
    int num_threads=4;
    omp_set_num_threads(num_threads);

    int var_shared=-777;
    int var_private=-777;
    int var_firstprivate=-777;
    int var_lastprivate=-777;
    #pragma omp parallel shared(var_shared) private(var_private) firstprivate(var_firstprivate) 
    {
        #pragma omp for lastprivate(var_lastprivate)
        for(int i=0;i<1000;i++)
        {
            var_shared=i;
            var_private=i;
            var_firstprivate=i;
            var_lastprivate=i;
        }
    }
    printf("after parallel region : %d %d %d %d",var_shared,var_private,
    var_firstprivate,var_lastprivate);
}