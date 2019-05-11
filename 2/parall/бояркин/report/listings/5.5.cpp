< ... >

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

< ... >

tree::node tree::node::getSimpleRecursiveSumSubNode() const {
    < ... >

    for (const auto& currentChild : mChilds) {
        delay(); // <---------
        
        sum += currentChild.mValue;

        < ... >
    }
    
    < ... >
}

< ... >

tree::node tree::node::getSimpleCyclicSumSubNode() const {
    < ... >
    
    while (!stackNodes.empty()) {
        < ... >
        
        if (parentNodePtr != nullptr) {
            delay(); // <---------
            
            parentNodePtr->mValue += currentNodePtr->mValue;
        }
        
        < ... >
    }
    
    < ... >
}

< ... >

void* tree::node::getPthreadCyclicSumSubNodeHandler(void* argument) {
    < ... >

    while (retry) {
        < ... >

        // Set values for current and parent nodes.
        
        delay(); // <---------
        
        pargument.valuesMutex->lock();

        if (parentNodePtr != nullptr) {
            parentNodePtr->mValue += currentNodePtr->mValue;
        }

        currentNodePtr->mValue = 0;

        pargument.valuesMutex->unlock();

        < ... >
    
    < ... >
}

< ... >
