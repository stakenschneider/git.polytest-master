#include "test.h"
#include <stdlib.h>
#include <iostream>
#include <stdint.h>
#include <chrono>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef MPI_ENABLED
#include <mpi.h>
#endif

int initTests(int argc, char** argv) {
    // setSingleCoreCpuMode();
    
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
    
    std::cout << "%SUITE_STARTING% treetests" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;
    
#ifdef MPI_ENABLED
    std::cout << "%TEST_STARTED% testMpiPerformance (treetests)" << std::endl;
    }
    
    testMpiPerformance();
    
    if (rank == 0) {
    std::cout << "%TEST_FINISHED% time=0 testMpiPerformance (treetests)" << std::endl;
    std::cout << "%TEST_STARTED% testMpiStatistics (treetests)" << std::endl;
    }
    
    testMpiStatistics();
    
    if (rank == 0) {
    std::cout << "%TEST_FINISHED% time=0 testMpiStatistics (treetests)" << std::endl;
#endif
    
    std::cout << "%TEST_STARTED% testSmallTreeSingleEquality (treetests)" << std::endl;
    testSmallTreeSingleEquality();
    std::cout << "%TEST_FINISHED% time=0 testSmallTreeSingleEquality (treetests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testAverageTreeSingleEquality (treetests)" << std::endl;
    testAverageTreeSingleEquality();
    std::cout << "%TEST_FINISHED% time=0 testAverageTreeSingleEquality (treetests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testBigTreeSingleEquality (treetests)" << std::endl;
    testBigTreeSingleEquality();
    std::cout << "%TEST_FINISHED% time=0 testBigTreeSingleEquality (treetests)" << std::endl;

    std::cout << "%TEST_STARTED% testSmallTreeDoubleEquality (treetests)" << std::endl;
    testSmallTreeDoubleEquality();
    std::cout << "%TEST_FINISHED% time=0 testSmallTreeDoubleEquality (treetests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testAverageTreeDoubleEquality (treetests)" << std::endl;
    testAverageTreeDoubleEquality();
    std::cout << "%TEST_FINISHED% time=0 testAverageTreeDoubleEquality (treetests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testBigTreeDoubleEquality (treetests)" << std::endl;
    testBigTreeDoubleEquality();
    std::cout << "%TEST_FINISHED% time=0 testBigTreeDoubleEquality (treetests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testSmallTreePerformance (treetests)\n" << std::endl;
    testSmallTreePerformance();
    std::cout << "%TEST_FINISHED% time=0 testSmallTreePerformance (treetests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testAverageTreePerformance (treetests)\n" << std::endl;
    testAverageTreePerformance();
    std::cout << "%TEST_FINISHED% time=0 testAverageTreePerformance (treetests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testBigTreePerformance (treetests)\n" << std::endl;
    testBigTreePerformance();
    std::cout << "%TEST_FINISHED% time=0 testBigTreePerformance (treetests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testSmallTreeStatistics (treetests)\n" << std::endl;
    testSmallTreeStatistics();
    std::cout << "%TEST_FINISHED% time=0 testSmallTreeStatistics (treetests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testAverageTreeStatistics (treetests)\n" << std::endl;
    testAverageTreeStatistics();
    std::cout << "%TEST_FINISHED% time=0 testAverageTreeStatistics (treetests)" << std::endl;
    
    std::cout << "%TEST_STARTED% testBigTreeStatistics (treetests)\n" << std::endl;
    testBigTreeStatistics();
    std::cout << "%TEST_FINISHED% time=0 testBigTreeStatistics (treetests)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

#ifdef MPI_ENABLED
    }
    
    MPI_Finalize();
#endif
    
    return (EXIT_SUCCESS);
}

#ifdef MPI_ENABLED

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

void testMpiStatistics() {
    int32_t rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    std::ofstream file;
    std::chrono::system_clock::time_point timeBefore, timeAfter;
    
    if (rank == 0) {
        std::cout << "treetests testMpiStatistics" << std::endl;
        
        file.open(EXPONENT_STATISTICS);

        for (uint32_t retryIndex = 0; retryIndex < EXPONENT_PERFORMANSE_RETRIES; ++retryIndex) {
            timeBefore = std::chrono::high_resolution_clock::now();
            getExponentSimple(EXPONENT_PRESISION);
            timeAfter = std::chrono::high_resolution_clock::now();

            auto resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
            file << resultTime << std::endl;
        }

        file.close();

        std::cout << std::endl << "Simple exponent algorithm statistics:" << std::endl;
        printStatistics(EXPONENT_STATISTICS);

        remove(EXPONENT_STATISTICS);
        
        file.open(EXPONENT_STATISTICS);
    }
    
    for (uint32_t retryIndex = 0; retryIndex < EXPONENT_PERFORMANSE_RETRIES; ++retryIndex) {
        if (rank == 0) {
            timeBefore = std::chrono::high_resolution_clock::now();
        }
        
        getExponentMpi(EXPONENT_PRESISION);
        
        if (rank == 0) {
           timeAfter = std::chrono::high_resolution_clock::now();
           auto resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
           file << resultTime << std::endl;
        }
    }
    
    if (rank == 0) {
        file.close();

        std::cout << std::endl << "MPI exponent algorithm statistics:" << std::endl;
        printStatistics(EXPONENT_STATISTICS);

        remove(EXPONENT_STATISTICS);
    }
}

#endif

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

void setSingleCoreCpuMode() {
    cpu_set_t cpuSet;
    CPU_ZERO(&cpuSet);
    CPU_SET(0, &cpuSet);
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &cpuSet);
}

void delay() {
    double temp = 1;
    for (uint32_t delayIndex = 1; delayIndex < 1000; ++delayIndex) {
        if (delayIndex % 2 == 0) {
            temp *= 10;
        } else {
            temp /= 10;
        }
    }
}

tree parseTreeFromResourceFile(const char* filename) {
    std::string line;
    std::ifstream myfile(filename);
    if (myfile.is_open()) {
        while (myfile.good()) {
            std::getline(myfile, line);
        }
        
        myfile.close();
    } else {
        throw std::invalid_argument("No such file.");
    }
    
    return tree::parseTree(line.c_str());
}

void printStatistics(const char* statisticsFile) {
    std::string command = "python3.6 statistics.py ";
    command += statisticsFile;
    FILE *file = popen(command.c_str(), "r");
    
    char output[1024];
    while (fgets(output, sizeof(output) - 1, file) != NULL) {
        std::cout << output;
    }
    
    pclose(file);
}

void testSmallTreeSingleEquality() {
    std::cout << "treetests testSmallTreeSingleEquality" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(SMALL_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    // Simple recursive algorithm.
    
    std::string simpleRecursiveStringTree = testTree.getSimpleRecursiveSumSubTree().toString();
    
    // Simple cyclic algorithm.
    
    std::string simpleCyclicStringTree = testTree.getSimpleCyclicSumSubTree().toString();
    
    // Pthread cyclic algorithm.
    
    std::string pthreadCyclicStringTree = testTree.getPthreadCyclicSumSubTree().toString();
    
    if (simpleRecursiveStringTree != simpleCyclicStringTree || simpleRecursiveStringTree != pthreadCyclicStringTree) {
        std::cout << "%TEST_FAILED% time=0 testname=testSmallTreeSingleEquality (treetests) message=(" 
                  << std::to_string(simpleRecursiveStringTree == simpleCyclicStringTree) << ", " << std::to_string(simpleRecursiveStringTree == pthreadCyclicStringTree)
                  << ")" << std::endl;
    }
}

void testAverageTreeSingleEquality() {
    std::cout << "treetests testAverageTreeSingleEquality" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(AVERAGE_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    // Simple recursive algorithm.
    
    std::string simpleRecursiveStringTree = testTree.getSimpleRecursiveSumSubTree().toString();
    
    // Simple cyclic algorithm.
    
    std::string simpleCyclicStringTree = testTree.getSimpleCyclicSumSubTree().toString();
    
    // Pthread cyclic algorithm.
    
    std::string pthreadCyclicStringTree = testTree.getPthreadCyclicSumSubTree().toString();
    
    if (simpleRecursiveStringTree != simpleCyclicStringTree || simpleRecursiveStringTree != pthreadCyclicStringTree) {
        std::cout << "%TEST_FAILED% time=0 testname=testAverageTreeSingleEquality (treetests) message=(" 
                  << std::to_string(simpleRecursiveStringTree == simpleCyclicStringTree) << ", " << std::to_string(simpleRecursiveStringTree == pthreadCyclicStringTree)
                  << ")" << std::endl;
    }
}

void testBigTreeSingleEquality() {
    std::cout << "treetests testBigTreeSingleEquality" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(BIG_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    // Simple recursive algorithm.
    
    std::string simpleRecursiveStringTree = testTree.getSimpleRecursiveSumSubTree().toString();
    
    // Simple cyclic algorithm.
    
    std::string simpleCyclicStringTree = testTree.getSimpleCyclicSumSubTree().toString();
    
    // Pthread cyclic algorithm.
    
    std::string pthreadCyclicStringTree = testTree.getPthreadCyclicSumSubTree().toString();
    
    if (simpleRecursiveStringTree != simpleCyclicStringTree || simpleRecursiveStringTree != pthreadCyclicStringTree) {
        std::cout << "%TEST_FAILED% time=0 testname=testBigTreeSingleEquality (treetests) message=(" 
                  << std::to_string(simpleRecursiveStringTree == simpleCyclicStringTree) << ", " << std::to_string(simpleRecursiveStringTree == pthreadCyclicStringTree)
                  << ")" << std::endl;
    }
}

void testSmallTreeDoubleEquality() {
    std::cout << "treetests testSmallTreeDoubleEquality" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(SMALL_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    // Simple recursive algorithm.
    
    std::string simpleRecursiveStringTree = testTree.getSimpleRecursiveSumSubTree().getSimpleRecursiveSumSubTree().toString();
    
    // Simple cyclic algorithm.
    
    std::string simpleCyclicStringTree = testTree.getSimpleCyclicSumSubTree().getSimpleCyclicSumSubTree().toString();
    
    // Pthread cyclic algorithm.
    
    std::string pthreadCyclicStringTree = testTree.getPthreadCyclicSumSubTree().getPthreadCyclicSumSubTree().toString();
    
    if (simpleRecursiveStringTree != simpleCyclicStringTree || simpleRecursiveStringTree != pthreadCyclicStringTree) {
        std::cout << "%TEST_FAILED% time=0 testname=testSmallTreeDoubleEquality (treetests) message=(" 
                  << std::to_string(simpleRecursiveStringTree == simpleCyclicStringTree) << ", " << std::to_string(simpleRecursiveStringTree == pthreadCyclicStringTree)
                  << ")" << std::endl;
    }
}

void testAverageTreeDoubleEquality() {
    std::cout << "treetests testAverageTreeDoubleEquality" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(AVERAGE_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    // Simple recursive algorithm.
    
    std::string simpleRecursiveStringTree = testTree.getSimpleRecursiveSumSubTree().getSimpleRecursiveSumSubTree().toString();
    
    // Simple cyclic algorithm.
    
    std::string simpleCyclicStringTree = testTree.getSimpleCyclicSumSubTree().getSimpleCyclicSumSubTree().toString();
    
    // Pthread cyclic algorithm.
    
    std::string pthreadCyclicStringTree = testTree.getPthreadCyclicSumSubTree().getPthreadCyclicSumSubTree().toString();
    
    if (simpleRecursiveStringTree != simpleCyclicStringTree || simpleRecursiveStringTree != pthreadCyclicStringTree) {
        std::cout << "%TEST_FAILED% time=0 testname=testAverageTreeDoubleEquality (treetests) message=(" 
                  << std::to_string(simpleRecursiveStringTree == simpleCyclicStringTree) << ", " << std::to_string(simpleRecursiveStringTree == pthreadCyclicStringTree)
                  << ")" << std::endl;
    }
}

void testBigTreeDoubleEquality() {
    std::cout << "treetests testBigTreeDoubleEquality" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(BIG_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    // Simple recursive algorithm.
    
    std::string simpleRecursiveStringTree = testTree.getSimpleRecursiveSumSubTree().getSimpleRecursiveSumSubTree().toString();
    
    // Simple cyclic algorithm.
    
    std::string simpleCyclicStringTree = testTree.getSimpleCyclicSumSubTree().getSimpleCyclicSumSubTree().toString();
    
    // Pthread cyclic algorithm.
    
    std::string pthreadCyclicStringTree = testTree.getPthreadCyclicSumSubTree().getPthreadCyclicSumSubTree().toString();
    
    if (simpleRecursiveStringTree != simpleCyclicStringTree || simpleRecursiveStringTree != pthreadCyclicStringTree) {
        std::cout << "%TEST_FAILED% time=0 testname=testBigTreeDoubleEquality (treetests) message=(" 
                  << std::to_string(simpleRecursiveStringTree == simpleCyclicStringTree) << ", " << std::to_string(simpleRecursiveStringTree == pthreadCyclicStringTree)
                  << ")" << std::endl;
    }
}

void testSmallTreePerformance() {
    std::cout << "treetests testSmallTreePerformance" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(SMALL_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    // Simple recursive algorithm.
    
    auto timeBefore = std::chrono::high_resolution_clock::now();
    for (uint32_t retryIndex = 0; retryIndex < SMALL_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        testTree.getSimpleRecursiveSumSubTree();
    }
    auto timeAfter = std::chrono::high_resolution_clock::now();
    
    double resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
    std::cout << "Simple recursive algorithm duration: " << resultTime << " milliseconds." << std::endl;
    
    // Simple cyclic algorithm.
    
    timeBefore = std::chrono::high_resolution_clock::now();
    for (uint32_t retryIndex = 0; retryIndex < SMALL_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        testTree.getSimpleCyclicSumSubTree();
    }
    timeAfter = std::chrono::high_resolution_clock::now();
    
    resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
    std::cout << "Simple cyclic algorithm duration: " << resultTime << " milliseconds." << std::endl;
    
    // Pthread cyclic algorithm.
    
    timeBefore = std::chrono::high_resolution_clock::now();
    for (uint32_t retryIndex = 0; retryIndex < SMALL_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        testTree.getPthreadCyclicSumSubTree();
    }
    timeAfter = std::chrono::high_resolution_clock::now();
    
    resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
    std::cout << "Pthread cyclic algorithm duration: " << resultTime << " milliseconds." << std::endl;
}

void testAverageTreePerformance() {
    std::cout << "treetests testAverageTreePerformance" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(AVERAGE_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    // Simple recursive algorithm.
    
    auto timeBefore = std::chrono::high_resolution_clock::now();
    for (uint32_t retryIndex = 0; retryIndex < AVERAGE_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        testTree.getSimpleRecursiveSumSubTree();
    }
    auto timeAfter = std::chrono::high_resolution_clock::now();
    
    double resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
    std::cout << "Simple recursive algorithm duration: " << resultTime << " milliseconds." << std::endl;
    
    // Simple cyclic algorithm.
    
    timeBefore = std::chrono::high_resolution_clock::now();
    for (uint32_t retryIndex = 0; retryIndex < AVERAGE_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        testTree.getSimpleCyclicSumSubTree();
    }
    timeAfter = std::chrono::high_resolution_clock::now();
    
    resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
    std::cout << "Simple cyclic algorithm duration: " << resultTime << " milliseconds." << std::endl;
    
    // Pthread cyclic algorithm.
    
    timeBefore = std::chrono::high_resolution_clock::now();
    for (uint32_t retryIndex = 0; retryIndex < AVERAGE_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        testTree.getPthreadCyclicSumSubTree();
    }
    timeAfter = std::chrono::high_resolution_clock::now();
    
    resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
    std::cout << "Pthread cyclic algorithm duration: " << resultTime << " milliseconds." << std::endl;
}

void testBigTreePerformance() {
    std::cout << "treetests testBigTreePerformance" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(BIG_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    // Simple recursive algorithm.
    
    auto timeBefore = std::chrono::high_resolution_clock::now();
    for (uint32_t retryIndex = 0; retryIndex < BIG_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        testTree.getSimpleRecursiveSumSubTree();
    }
    auto timeAfter = std::chrono::high_resolution_clock::now();
    
    double resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
    std::cout << "Simple recursive algorithm duration: " << resultTime << " milliseconds." << std::endl;
    
    // Simple cyclic algorithm.
    
    timeBefore = std::chrono::high_resolution_clock::now();
    for (uint32_t retryIndex = 0; retryIndex < BIG_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        testTree.getSimpleCyclicSumSubTree();
    }
    timeAfter = std::chrono::high_resolution_clock::now();
    
    resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
    std::cout << "Simple cyclic algorithm duration: " << resultTime << " milliseconds." << std::endl;
    
    // Pthread cyclic algorithm.
    
    timeBefore = std::chrono::high_resolution_clock::now();
    for (uint32_t retryIndex = 0; retryIndex < BIG_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        testTree.getPthreadCyclicSumSubTree();
    }
    timeAfter = std::chrono::high_resolution_clock::now();
    
    resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
    std::cout << "Pthread cyclic algorithm duration: " << resultTime << " milliseconds." << std::endl;
}

void testSmallTreeStatistics() {
    std::cout << "treetests testSmallTreeStatistics" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(SMALL_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    std::ofstream file;
    file.open(SMALL_TREE_STATISTICS);
    
    for (uint32_t retryIndex = 0; retryIndex < SMALL_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        auto timeBefore = std::chrono::high_resolution_clock::now();
        testTree.getSimpleRecursiveSumSubTree();
        auto timeAfter = std::chrono::high_resolution_clock::now();
        
        auto resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
        file << resultTime << std::endl;
    }
    
    file.close();
    
    std::cout << std::endl << "Simple recursive algorithm statistics:" << std::endl;
    printStatistics(SMALL_TREE_STATISTICS);
    
    remove(SMALL_TREE_STATISTICS);
    
    file.open(SMALL_TREE_STATISTICS);
    
    for (uint32_t retryIndex = 0; retryIndex < SMALL_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        auto timeBefore = std::chrono::high_resolution_clock::now();
        testTree.getSimpleCyclicSumSubTree();
        auto timeAfter = std::chrono::high_resolution_clock::now();
        
        auto resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
        file << resultTime << std::endl;
    }
    
    file.close();
    
    std::cout << std::endl << "Simple cyclic algorithm statistics:" << std::endl;
    printStatistics(SMALL_TREE_STATISTICS);
    
    remove(SMALL_TREE_STATISTICS);
    
    file.open(SMALL_TREE_STATISTICS);
    
    for (uint32_t retryIndex = 0; retryIndex < SMALL_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        auto timeBefore = std::chrono::high_resolution_clock::now();
        testTree.getPthreadCyclicSumSubTree();
        auto timeAfter = std::chrono::high_resolution_clock::now();
        
        auto resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
        file << resultTime << std::endl;
    }
    
    file.close();
    
    std::cout << std::endl << "Pthread cyclic algorithm statistics:" << std::endl;
    printStatistics(SMALL_TREE_STATISTICS);
    
    remove(SMALL_TREE_STATISTICS);
}

void testAverageTreeStatistics() {
    std::cout << "treetests testAverageTreeStatistics" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(AVERAGE_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    std::ofstream file;
    file.open(AVERAGE_TREE_STATISTICS);
    
    for (uint32_t retryIndex = 0; retryIndex < AVERAGE_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        auto timeBefore = std::chrono::high_resolution_clock::now();
        testTree.getSimpleRecursiveSumSubTree();
        auto timeAfter = std::chrono::high_resolution_clock::now();
        
        auto resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
        file << resultTime << std::endl;
    }
    
    file.close();
    
    std::cout << std::endl << "Simple recursive algorithm statistics:" << std::endl;
    printStatistics(AVERAGE_TREE_STATISTICS);
    
    remove(AVERAGE_TREE_STATISTICS);
    
    file.open(AVERAGE_TREE_STATISTICS);
    
    for (uint32_t retryIndex = 0; retryIndex < AVERAGE_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        auto timeBefore = std::chrono::high_resolution_clock::now();
        testTree.getSimpleCyclicSumSubTree();
        auto timeAfter = std::chrono::high_resolution_clock::now();
        
        auto resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
        file << resultTime << std::endl;
    }
    
    file.close();
    
    std::cout << std::endl << "Simple cyclic algorithm statistics:" << std::endl;
    printStatistics(AVERAGE_TREE_STATISTICS);
    
    remove(AVERAGE_TREE_STATISTICS);
    
    file.open(AVERAGE_TREE_STATISTICS);
    
    for (uint32_t retryIndex = 0; retryIndex < AVERAGE_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        auto timeBefore = std::chrono::high_resolution_clock::now();
        testTree.getPthreadCyclicSumSubTree();
        auto timeAfter = std::chrono::high_resolution_clock::now();
        
        auto resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
        file << resultTime << std::endl;
    }
    
    file.close();
    
    std::cout << std::endl << "Pthread cyclic algorithm statistics:" << std::endl;
    printStatistics(AVERAGE_TREE_STATISTICS);
    
    remove(AVERAGE_TREE_STATISTICS);
}

void testBigTreeStatistics() {
    std::cout << "treetests testBigTreeStatistics" << std::endl;
    
    tree testTree = parseTreeFromResourceFile(BIG_TREE_FILENAME);
    std::cout << "Parsing finished." << std::endl;
    
    std::ofstream file;
    file.open(BIG_TREE_STATISTICS);
    
    for (uint32_t retryIndex = 0; retryIndex < BIG_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        auto timeBefore = std::chrono::high_resolution_clock::now();
        testTree.getSimpleRecursiveSumSubTree();
        auto timeAfter = std::chrono::high_resolution_clock::now();
        
        auto resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
        file << resultTime << std::endl;
    }
    
    file.close();
    
    std::cout << std::endl << "Simple recursive algorithm statistics:" << std::endl;
    printStatistics(BIG_TREE_STATISTICS);
    
    remove(BIG_TREE_STATISTICS);
    
    file.open(BIG_TREE_STATISTICS);
    
    for (uint32_t retryIndex = 0; retryIndex < BIG_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        auto timeBefore = std::chrono::high_resolution_clock::now();
        testTree.getSimpleCyclicSumSubTree();
        auto timeAfter = std::chrono::high_resolution_clock::now();
        
        auto resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
        file << resultTime << std::endl;
    }
    
    file.close();
    
    std::cout << std::endl << "Simple cyclic algorithm statistics:" << std::endl;
    printStatistics(BIG_TREE_STATISTICS);
    
    remove(BIG_TREE_STATISTICS);
    
    file.open(BIG_TREE_STATISTICS);
    
    for (uint32_t retryIndex = 0; retryIndex < BIG_TREE_PERFORMANSE_RETRIES; ++retryIndex) {
        auto timeBefore = std::chrono::high_resolution_clock::now();
        testTree.getPthreadCyclicSumSubTree();
        auto timeAfter = std::chrono::high_resolution_clock::now();
        
        auto resultTime = std::chrono::duration_cast<std::chrono::duration<double>>(timeAfter - timeBefore).count() * 1000;
        file << resultTime << std::endl;
    }
    
    file.close();
    
    std::cout << std::endl << "Pthread cyclic algorithm statistics:" << std::endl;
    printStatistics(BIG_TREE_STATISTICS);
    
    remove(BIG_TREE_STATISTICS);
}