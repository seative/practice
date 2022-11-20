// OpenMP Testing the section construct
#include<cstdio>
#include<omp.h>

void function1()
{
    for(int i=0;i!=1;i++)
    {
        printf("Fuction1 done by thread %d\n",omp_get_thread_num());
    }
}

void function2()
{
    for(int j=0;j!=2;j++)
    {
        printf("Function2 done by thread %d\n",omp_get_thread_num());
    }
}

int main(int argc,char* argv[])
{
    int n=1;
    omp_set_num_threads(n);
    #pragma omp parallel
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                function1();
            }
            #pragma omp section
            {
                function2();
            }
        }
    }
}