#include <cstdio>
#include <cstdlib>
#include <omp.h>

#define N 5
#define FS 38

struct node
{
    int data;
    int fibdata;
    struct node *next;
};
int fib(int n)
{
    int x, y;
    if (n < 2)
    {
        return (n);
    }
    else
    {
        x = fib(n - 1);
        y = fib(n - 2);
        return x + y;
    }
}

void processwork(struct node *p)
{
    int n;
    n = p->data;
    p->fibdata = fib(n);
}

struct node *init_list(struct node *p)
{
    struct node *head = nullptr;
    struct node *temp = nullptr;
    head = (struct node *)malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
    for (int i = 0; i < N; i++)
    {
        temp = (struct node *)malloc(sizeof(struct node));
        p->next = temp;
        p = temp;
        p->data = FS + i + 1;
        p->fibdata = i + 1;
    }
    p->next = nullptr;
    return head;
}

int main(int argc, char *argv[])
{
    double start, end;
    omp_set_num_threads(4);
    struct node *p = nullptr;
    struct node *temp = nullptr;
    struct node *head = nullptr;
    p = init_list(p);
    head = p;
    start = omp_get_wtime();
#pragma omp parallel
    {
#pragma omp master
        printf("Threads:      %d\n", omp_get_num_threads());
#pragma omp single
        while (p != nullptr)
        {
#pragma omp task firstprivate(p)
            processwork(p);
            p = p->next;
        }
    }
    end = omp_get_wtime();
    p = head;
    while (p != nullptr)
    {
        printf("%d : %d\n", p->data, p->fibdata);
        temp = p->next;
        free(p);
        p = temp;
    }
    free(p);
    printf("Compute Time: %f seconds\n", end - start);
}