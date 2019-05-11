< ... >

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

< ... >
