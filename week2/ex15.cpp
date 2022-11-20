#include <cstdio>
#include <omp.h>

double generate_pepple(int i, int j)
{
    return (2 * i + 3 * j);
}

int main(int argc, char *argv[])
{
    int num_threads = 4;
    omp_set_num_threads(num_threads);

    int num = 10;
    int people = 0;
    int apples = 5000;

#pragma omp parallel for reduction(+:people) reduction(-:apples) 
    for (int i = 0; i < num; i++)
    {
        for (int j = i+1; j < num; j++)
        {
            int ppl = generate_pepple(i, j);
            people += ppl;
            apples -= ppl;
        }
    }
    printf("people = %d\n", people);
    printf("apples = %d", apples);
}