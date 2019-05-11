< ... >

long double getExponentSimple(int32_t presision) {
    long double result = 0;
    for (int32_t indexStep = 0; indexStep <= presision; ++indexStep) {
        long double factorial = 1;
        if (indexStep > 1) {
            for (int32_t indexFact = 1; indexFact <= indexStep; ++indexFact) {
                factorial *= indexFact;
            }
        }
        
        long double value = 1 / factorial;
        result += value;
    }

    return result;
}

< ... >

#ifdef MPI_ENABLED

long double getExponentMpi(int32_t presision) {
    int32_t rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Bcast(&presision, 1, MPI_INT, 0, MPI_COMM_WORLD);

    long double sum = 0;
    for (int32_t indexStep = rank; indexStep <= presision; indexStep += size) {
        long double factorial = 1;
        if (indexStep > 1) {
            for (int32_t indexFact = 1; indexFact <= indexStep; ++indexFact) {
                factorial *= indexFact;
            }
        }
        
        long double value = 1 / factorial;
        sum += value;
    }

    long double result;
    MPI_Reduce(&sum, &result, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    return result;
}

#endif

< ... >
