#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <sys/time.h>

int main()
{
    int rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int number_amount;
    if (rank == 0) {
        const int MAX_NUMBERS = 100;
        int numbers[MAX_NUMBERS];
        // Pick a random amount of integers to send to process 1
        srand(time(NULL));
        number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;

        // Send the amount of integers to process 1
        MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("I am %i and I sent %d numbers to 1\n", rank, number_amount);
    }
    else if (rank == 1) {
        MPI_Status status;
        // Probe for an incoming message from process 0
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);

        // Get the size of the message
        MPI_Get_count(&status, MPI_INT, &number_amount);
        // Allocate a buffer just big enough
        int* number_buf = (int*)malloc(sizeof(int) * number_amount);

        // Receive the message
        MPI_Recv(number_buf, number_amount, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("I am %i and I dynamically received %d numbers from 0.\n", rank, number_amount);
        free(number_buf);
    }

    MPI_Finalize();
}