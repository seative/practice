// #include <sys/time.h>
// #include <cstdlib>
// #include <cstdio>
// #include <ctime>

// #include "mpi.h"
// int main()
// {
//     int number_amount, MAX_NUMBERS = 100;
//     int max_number = 10000;
//     srand(time(NULL));
//     number_amount = rand() % MAX_NUMBERS;
//     MPI_Init(NULL, NULL);
//     int rank, size;
//     MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//     MPI_Comm_size(MPI_COMM_WORLD, &size);
//     int *sendbuff, *recbuff;
//     if (rank == 0)
//     {
//         int *sendbuff = new int[number_amount];
//         // int *beg = begin(sendbuff);
//         // int *last = end(sendbuff);
//         // while (beg != last)
//         // {
//         //     *beg = rand() % (max_number + 1);
//         //     ++beg;
//         // }
//         for (int i = 0; i < number_amount; ++i)
//         {
//             sendbuff[i] = rand() % (max_number + 1);
//         }
//     }
//     recbuff = new int[number_amount];
//     MPI_Scatter(sendbuff, number_amount / size, MPI_INT, recbuff, number_amount / size, MPI_INT, 0, MPI_COMM_WORLD);

//     MPI_Finalize();
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <mpi.h>

int main()
{
    int i, rank, size;
    int num_elements_per_proc = 3;
    int num_elements;
    // seed the random number generator
    srand(time(NULL));

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // create a random array of elements on the root process
    // total size will be the number of elements per process times the number of processes
    float *rand_nums = NULL;
    if (rank == 0)
    {
        num_elements = num_elements_per_proc * size;
        rand_nums = (float *)malloc(sizeof(float) * num_elements);
        for (i = 0; i < num_elements; i++)
        {
            rand_nums[i] = (rand() / (float)RAND_MAX);
        }
    }

    // for each process, create a buffer that will hold a subset of the array
    float *sub_rand_nums = (float *)malloc(sizeof(float) * num_elements_per_proc);

    // scatter the random numbers from the root process to all other processes
    MPI_Scatter(rand_nums, num_elements_per_proc, MPI_FLOAT, sub_rand_nums,
                num_elements_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // compute the average of your subset
    float sub_avg = 0.f;
    for (i = 0; i < num_elements_per_proc; i++)
    {
        sub_avg += sub_rand_nums[i];
    }
    sub_avg = sub_avg / num_elements_per_proc;
    printf("I am process %i out of %i, average result = %f \n", rank, size, sub_avg);

    // gather all partial averages down to the root process
    float *sub_avgs = NULL;
    if (rank == 0)
    {
        // memory allocation needed only on root process
        sub_avgs = (float *)malloc(sizeof(float) * size);
    }
    MPI_Gather(&sub_avg, 1, MPI_FLOAT, sub_avgs, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    // compute the total average of all numbers from the partial averages
    if (rank == 0)
    {
        float avg = 0.f;
        for (i = 0; i < size; i++)
        {
            avg += sub_avgs[i];
        }
        avg = avg / size;
        printf("Avg of all elements is %f\n", avg);

        // compute average across the original data for comparison
        float original_data_avg = 0.f;
        for (i = 0; i < num_elements; i++)
        {
            original_data_avg += rand_nums[i];
        }
        original_data_avg = original_data_avg / num_elements;
        printf("Avg computed across original data is %f\n", original_data_avg);
    }

    // Clean up
    if (rank == 0)
    {
        free(rand_nums);
        free(sub_avgs);
    }
    free(sub_rand_nums);

    MPI_Finalize();
}