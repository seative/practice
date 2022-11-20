#include <mpi.h>
#include <stdio.h>

int main() {
  int rank, size;
  int snd_buf, rcv_buf;
  int right, left;
  int sum, i;
  MPI_Status status;

  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  right = (rank + 1) % size;
  left = (rank - 1 + size) % size;

  sum = 0;
  snd_buf = rank;  // store rank value in send buffer

  for (i = 0; i < size; i++) {
    // if (rank == 0) {
    //   MPI_Ssend(&snd_buf, 1, MPI_INT, right, 17, MPI_COMM_WORLD);
    //   MPI_Recv(&rcv_buf, 1, MPI_INT, left, 17, MPI_COMM_WORLD, &status);
    // } else {
    //   MPI_Recv(&rcv_buf, 1, MPI_INT, left, 17, MPI_COMM_WORLD, &status);
    //   MPI_Ssend(&snd_buf, 1, MPI_INT, right, 17, MPI_COMM_WORLD);
    // }
    // correct   one send ,rest of them recv ,then loop serialization

    // MPI_Recv(&rcv_buf, 1, MPI_INT, left, 17, MPI_COMM_WORLD, &status);
    // MPI_Send(&snd_buf, 1, MPI_INT, right, 17, MPI_COMM_WORLD);
    // error  you cant recv first ,should send first,even not Ssend

    MPI_Send(&snd_buf, 1, MPI_INT, right, 17, MPI_COMM_WORLD);
    MPI_Recv(&rcv_buf, 1, MPI_INT, left, 17, MPI_COMM_WORLD, &status);
    // correct even not two buffer ,you can just use one buffer
    snd_buf = rcv_buf;  // prepare send buffer for next iteration
    sum += snd_buf;     // sum of all received values
  }
  printf("PE%i:\tSum = %i\n", rank, sum);

  MPI_Finalize();
}