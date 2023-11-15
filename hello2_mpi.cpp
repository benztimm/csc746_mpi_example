#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv); // Initialize MPI

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get current process id
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get number of processes

    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    printf("I am rank %d of %d total ranks running on <%s> \n", rank, size, hostname);

    MPI_Finalize(); // Terminate MPI
    return 0;
}
