#include <cstdio>

#include "mpi.h"
int main(int argc, char *argv[]) {
  int rank;
  float token[1] = {12};
  MPI_Status status;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) {
    while (token[0] > 6) {
      printf("I am %i before send ping \n", rank);
      token[0]--;
      MPI_Ssend(token, 1, MPI_FLOAT, 1, 17, MPI_COMM_WORLD);
      MPI_Recv(token, 1, MPI_FLOAT, 1, 23, MPI_COMM_WORLD, &status);
      printf("I am %i after recv pong \n", rank);
    }
  } else if (rank == 1) {
    while (token[0] > 6) {
      MPI_Recv(token, 1, MPI_FLOAT, 0, 17, MPI_COMM_WORLD, &status);
      printf("I am %i after recv ping \n", rank);
      printf("I am %i before send pong \n", rank);
      token[0]--;
      MPI_Ssend(token, 1, MPI_FLOAT, 0, 23, MPI_COMM_WORLD);
    }
  }

  MPI_Finalize();
  return 0;
}