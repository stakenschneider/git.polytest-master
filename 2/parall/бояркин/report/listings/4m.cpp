< ... >

#ifdef MPI_ENABLED
#include <mpi.h>
#endif

< ... >

int main (int argc, char** argv) {
#ifdef MPI_ENABLED
    if (int32_t init = MPI_Init(&argc, &argv)) {
        MPI_Abort(MPI_COMM_WORLD, init);
        return 0x1;
    }
    
    int32_t rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    std::cout << "Rank " << rank << " of " << size << "." << std::endl;
    
    if (rank == 0) {
#endif

    long double result = getExponentSimple(100);
    std::cout << "Simple result: " << result << std::endl;

#ifdef MPI_ENABLED
    }

    long double result = getExponentMpi(100);
    
    if (rank == 0) {
        std::cout << "MPI result: " << result << std::endl;
    }

    MPI_Finalize();
#endif

    return 0x0;
}

< ... >
