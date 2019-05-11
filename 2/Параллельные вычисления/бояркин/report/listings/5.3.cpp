< ... >

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

< ... >
