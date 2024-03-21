//OpenMP testing reduction clause
#include <cstdio>
#include<omp.h>

int main(int argc, char* argv[])
{
    int sum=0;
    #pragma omp parallel for reduction(+:sum)
    for (int i =0;i<20;i++)
    {
        sum=sum+i;
    }
    printf("sum is %d",sum);
}