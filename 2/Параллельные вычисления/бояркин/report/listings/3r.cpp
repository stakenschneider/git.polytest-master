< ... >

tree::node tree::node::getPthreadCyclicSumSubNode() const {
    tree::node result = tree::node(*this);

#ifdef POOL_ENABLED
    std::mutex threadsMutex;
    uint8_t threadsLimit = (uint8_t) std::thread::hardware_concurrency();
    uint8_t threadsCount = 0;
#endif
    
    std::mutex valuesMutex;
    std::mutex stackNodesMutex;
    std::stack<std::pair<tree::node*, tree::node*>> stackNodes;
    stackNodes.push(std::pair<tree::node*, tree::node*>(nullptr, &result));
    
    struct tree::node::parg pargument;
    pargument.valuesMutex = &valuesMutex;
    pargument.stackNodesMutex = &stackNodesMutex;
    
#ifdef POOL_ENABLED
    pargument.threadsMutex = &threadsMutex;
    pargument.threadsLimit = &threadsLimit;
    pargument.threadsCount = &threadsCount;
#endif
    
    pargument.stackNodes = &stackNodes;
    
    pthread_t thread;
    pthread_create(&thread, nullptr, &tree::node::getPthreadCyclicSumSubNodeHandler, (void*) &pargument);
    pthread_join(thread, nullptr);
    return result;
}

void* tree::node::getPthreadCyclicSumSubNodeHandler(void* argument) {
    struct tree::node::parg pargument = *((parg*) argument);
    
#ifdef POOL_ENABLED
    pargument.threadsMutex->lock();
    ++(*(pargument.threadsCount));
    pargument.threadsMutex->unlock();
#endif
    
    bool retry = true;
    
    std::vector<pthread_t> threads;
    while (retry) {
        retry = false;
        
        // Get last stack pair.

        pargument.stackNodesMutex->lock();

        if (pargument.stackNodes->empty()) {
            pargument.stackNodesMutex->unlock();
            continue;
        }

        std::pair<tree::node*, tree::node*> currentPair = pargument.stackNodes->top();
        pargument.stackNodes->pop();

        pargument.stackNodesMutex->unlock();

        tree::node* parentNodePtr = currentPair.first;
        tree::node* currentNodePtr = currentPair.second;

        // Set values for current and parent nodes.
        
        pargument.valuesMutex->lock();

        if (parentNodePtr != nullptr) {
            parentNodePtr->mValue += currentNodePtr->mValue;
        }

        currentNodePtr->mValue = 0;

        pargument.valuesMutex->unlock();

        if (currentNodePtr->mChilds.empty()) {
            // Set new task for this thread.
            retry = true;
            continue;
        }

        // Push child to vector.

        pargument.stackNodesMutex->lock();

        for (auto currentChild = currentNodePtr->mChilds.end() - 1; currentChild >= currentNodePtr->mChilds.begin(); --currentChild) {
            pargument.stackNodes->push(std::pair<tree::node*, tree::node*>(currentNodePtr, &(*currentChild)));
        }

        pargument.stackNodesMutex->unlock();

        // Create N-1 new threads to resolve task.
        for (uint32_t threadIndex = 0; threadIndex < currentNodePtr->mChilds.size() - 1; ++threadIndex) {
#ifdef POOL_ENABLED
            pargument.threadsMutex->lock();
            if (*(pargument.threadsCount) >= (*(pargument.threadsLimit))) {
                pargument.threadsMutex->unlock();
                break;
            }
            pargument.threadsMutex->unlock();
#endif

            pthread_t thread;
            pthread_create(&thread, nullptr, &tree::node::getPthreadCyclicSumSubNodeHandler, (void*) &pargument);
            threads.push_back(thread);
        }

        // Set new task for this thread.
        retry = true;
    }
    
    // Wait other threads to continue.
    for (const auto& currentThread : threads) {
        pthread_join(currentThread, nullptr);
    }

#ifdef POOL_ENABLED    
    pargument.threadsMutex->lock();
    --(*(pargument.threadsCount));
    pargument.threadsMutex->unlock();
#endif
    return nullptr;
}

< ... >
