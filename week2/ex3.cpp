#include<cstdio>
#include<omp.h>

int main(int argc,char* argv[])
{
    int num_threads=4;
    omp_set_num_threads(num_threads);

    int private_var=1000;
    int shared_var=5000;
    int rank;
    #pragma omp parallel private(private_var,rank) shared(shared_var)
    {
        rank=omp_get_thread_num();
        printf("Thread ID is: %d\n",rank);
        private_var=private_var+num_threads;
        printf("Value of private_var is: %d\n",private_var);
        shared_var=shared_var+num_threads;
        printf("Value of shared_var is: %d\n",shared_var);
    }
}