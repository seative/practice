#include <cstdio>

#include "mpi.h"
int main(int argc, char *argv[]) {
  int rank, size;
  float buffer[1];
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  if (rank == 0) {
    printf("I am %i before send ping \n", rank);
    MPI_Send(buffer, 1, MPI_FLOAT, 1, 17, MPI_COMM_WORLD);
  } else if (rank == 1) {
    MPI_Recv(buffer, 1, MPI_FLOAT, 0, 17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    printf("I am %i after  recv ping \n", rank);
  }
  MPI_Finalize();
  return 0;
}
