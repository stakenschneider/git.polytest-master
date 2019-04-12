< ... >

static const int32_t EXPONENT_PRESISION = 10000;
static const int32_t EXPONENT_PERFORMANSE_RETRIES = 2;

< ... >

void testMpiPerformance() {
    int32_t rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    std::chrono::system_clock::time_point timeBefore, timeAfter;
    long double result;
    
    if (rank == 0) {
        std::cout << "treetests testMpiPerformance" << std::endl;

        timeBefore = std::chrono::high_resolution_clock::now();
        for (uint32_t retryIndex = 0; retryIndex < EXPONENT_PERFORMANSE_RETRIES; ++retryIndex) {
            result = getExponentSimple(EXPONENT_PRESISION);
        }
        timeAfter = std::chrono::high_resolution_clock::now();

        double resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
        std::cout << "Simple exponent algorithm duration: " << resultTime << " milliseconds." << std::endl;

        auto presision = std::cout.precision();
        std::cout.precision(30);
        std::cout << "Simple exponent algorithm result: " << result << std::endl;
        std::cout.precision(presision);

        timeBefore = std::chrono::high_resolution_clock::now();
    }
    
    for (uint32_t retryIndex = 0; retryIndex < EXPONENT_PERFORMANSE_RETRIES; ++retryIndex) {
        result = getExponentMpi(EXPONENT_PRESISION);
    }
    
    if (rank == 0) {
        timeAfter = std::chrono::high_resolution_clock::now();

        double resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
        std::cout << "MPI exponent algorithm duration: " << resultTime << " milliseconds." << std::endl;

        double presision = std::cout.precision();
        std::cout.precision(30);
        std::cout << "MPI exponent algorithm result: " << result << std::endl;
        std::cout.precision(presision);
    }
}

< ... >
