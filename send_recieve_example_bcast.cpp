#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv); // Initialize MPI

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get current process id
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get number of processes

    int the_number = -1;
    if(rank == 0){
        the_number = 42;
    }
    
    int sender_rank = 0;
    MPI_Bcast(&the_number, 1, MPI_INT, sender_rank, MPI_COMM_WORLD);

    if(rank != 0){
    printf("I am rank %d of %d total ranks, and I received %d from rank zero \n", rank, size, the_number);

    the_number += rank;
    MPI_Send(&the_number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }else{

    int return_values[size];
    MPI_Status status;

    return_values[0] = 0;
    for(int i = 1; i < size; i++){
        MPI_Recv(&return_values[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        printf(" Primary rank received %d from rank %d \n", return_values[i], i);
    }
    MPI_Finalize(); // Terminate MPI
    return 0;
}
