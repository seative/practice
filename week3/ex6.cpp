#include <cstdio>

#include "mpi.h"
void my_Bcast(void *data, int count, MPI_Datatype datatype, int root,
              MPI_Comm communicator) {
  int rank, size, i;
  MPI_Comm_rank(communicator, &rank);
  MPI_Comm_size(communicator, &size);

  // If we are the root process, send our data to everyone
  if (rank == root) {
    for (i = 0; i < size; i++) {
      if (i != rank) {
        MPI_Send(data, count, datatype, i, 0, communicator);
      }
    }
  } else {
    // If we are a receiver process, receive the data from the root
    MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
  }
}

int main() {
  int rank, i;
  int num_elements = 10000000;
  int num_trials = 10;
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  double total_my_bcast_time = 0.0;
  double total_mpi_bcast_time = 0.0;
  int *buff = new int[num_elements];
  for (i = 0; i < num_trials; i++) {
    // Time MPI_Bcast
    // Synchronize before starting timing
    MPI_Barrier(MPI_COMM_WORLD);
    total_mpi_bcast_time -= MPI_Wtime();
    MPI_Bcast(buff, num_elements, MPI_INT, 0, MPI_COMM_WORLD);
    // Synchronize again before obtaining final time
    MPI_Barrier(MPI_COMM_WORLD);
    total_mpi_bcast_time += MPI_Wtime();

    // Time my_Bcast
    MPI_Barrier(MPI_COMM_WORLD);
    total_my_bcast_time -= MPI_Wtime();
    my_Bcast(buff, num_elements, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    total_my_bcast_time += MPI_Wtime();
  }

  // Print resulting times
  if (rank == 0) {
    printf("Avg my_Bcast time = %lf\n", total_my_bcast_time / num_trials);
    printf("Avg MPI_Bcast time = %lf\n", total_mpi_bcast_time / num_trials);
  }
  delete[] buff;
  MPI_Finalize();
  return 0;
}