#include "tree.h"
#include "test.h"
#include <string>
#include <stack>
#include <mutex>
#include <stdexcept>
#include <stdint.h>
#include <pthread.h>
#include <thread>
#include <stdio.h>
#include <unistd.h>

#ifdef MPI_ENABLED
#include <mpi.h>
#endif

tree::node::node() {
    mValue = 0;
}

tree::node::node(const double value) {
    mValue = value;
}

tree::node tree::node::parseNode(const char* value) {
    tree::node result = tree::node();
    
    std::stack<std::pair<tree::node*, std::string>> stackStringNodes;
    stackStringNodes.push(std::pair<tree::node*, std::string>(nullptr, std::string(value)));
    
    while (!stackStringNodes.empty()) {
        std::pair<tree::node*, std::string> currentPair = stackStringNodes.top();
        stackStringNodes.pop();
        tree::node* parentNodePtr = currentPair.first;
        std::string currentStringNodePtr = currentPair.second;
        
        std::size_t openBracketIndex = currentStringNodePtr.find_first_of(tree::OPEN_BRACKET);
        if (openBracketIndex == std::string::npos || openBracketIndex == 0) {
            throw std::invalid_argument("No open bracket or no value.");
        }

        std::size_t closeBracketIndex = currentStringNodePtr.find_last_of(tree::CLOSE_BRACKET);
        if (closeBracketIndex == std::string::npos || openBracketIndex >= closeBracketIndex || closeBracketIndex != currentStringNodePtr.length() - 1) {
            throw std::invalid_argument("No close bracket or close bracket isn't last symbol.");
        }

        std::string valueString = currentStringNodePtr.substr(0, openBracketIndex);
        double parsedValue = std::stod(valueString);

        std::string childsString = currentStringNodePtr.substr(openBracketIndex + 1, closeBracketIndex - (openBracketIndex + 1));
        std::vector<std::string> childNodes;
        std::string buffer;
        int64_t bracketEquality = 0;
        for(const auto& currentSymbol : childsString) {
            if (currentSymbol == tree::OPEN_BRACKET) {
                ++bracketEquality;
            } else if (currentSymbol == tree::CLOSE_BRACKET) {
                --bracketEquality;
            }

            if (bracketEquality < 0) {
                throw std::invalid_argument("Invalid brackets.");
            }

            if (bracketEquality == 0 && currentSymbol == tree::DELIMITER) {
                childNodes.push_back(buffer);
                buffer.clear();
            } else {
                buffer += currentSymbol;  
            }
        }

        if (bracketEquality != 0) {
            throw std::invalid_argument("Invalid brackets.");
        }

        if (!buffer.empty()) {
            childNodes.push_back(buffer);
            buffer.clear();
        }

        tree::node* parsedNodePtr = nullptr;
        if (parentNodePtr == nullptr) {
            parsedNodePtr = &result;
            parsedNodePtr->mValue = parsedValue;
        } else {
            parentNodePtr->mChilds.insert(parentNodePtr->mChilds.begin(), tree::node(parsedValue));
            parsedNodePtr = &(parentNodePtr->mChilds.front());
        }
        
        if (childNodes.empty()) {
            continue;
        }
        
        for(auto& currentChildNode : childNodes) {
            stackStringNodes.push(std::pair<tree::node*, std::string>(parsedNodePtr, currentChildNode));
        }
    }
    
    return result;
}

std::string tree::node::toString() const {
    std::string result = std::to_string(mValue);
    result += tree::OPEN_BRACKET;
    
    for (const auto& currentChild : mChilds) {
        result += currentChild.toString();
        result += tree::DELIMITER;
    }
    
    if (!mChilds.empty()) {
        result.pop_back();
    }
    
    result += tree::CLOSE_BRACKET;
    return result;
}

void tree::node::setValue(const double value) {
    mValue = value;
}

double tree::node::getValue() const {
    return mValue;
}

void tree::node::addChild(const tree::node& child) {
    mChilds.push_back(std::move(child));
}

std::vector<tree::node> tree::node::getChilds() const {
    return mChilds;
}

tree::node tree::node::getSimpleRecursiveSumSubNode() const {
    double sum = 0;
    tree::node result = tree::node();
    for (const auto& currentChild : mChilds) {
#ifdef DELAY_ENABLED    
        delay();
#endif
        
        sum += currentChild.mValue;
        result.addChild(currentChild.getSimpleRecursiveSumSubNode());
    }
    
    result.mValue = sum;
    return result;
}

tree::node tree::node::getSimpleCyclicSumSubNode() const {
    tree::node result = tree::node(*this);
    
    std::stack<std::pair<tree::node*, tree::node*>> stackNodes;
    stackNodes.push(std::pair<tree::node*, tree::node*>(nullptr, &result));
    
    while (!stackNodes.empty()) {
        std::pair<tree::node*, tree::node*> currentPair = stackNodes.top();
        stackNodes.pop();
        tree::node* parentNodePtr = currentPair.first;
        tree::node* currentNodePtr = currentPair.second;
        
        if (parentNodePtr != nullptr) {
#ifdef DELAY_ENABLED    
            delay();
#endif
            
            parentNodePtr->mValue += currentNodePtr->mValue;
        }
        
        currentNodePtr->mValue = 0;
        
        if (currentNodePtr->mChilds.empty()) {
            continue;
        }
        
        for (auto currentChild = currentNodePtr->mChilds.end() - 1; currentChild >= currentNodePtr->mChilds.begin(); --currentChild) {
            stackNodes.push(std::pair<tree::node*, tree::node*>(currentNodePtr, &(*currentChild)));
        }
    }
    
    return result;
}

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
        
#ifdef DELAY_ENABLED    
        delay();
#endif
        
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

#ifdef MPI_ENABLED

tree::node tree::node::getMpiCyclicSumSubNode() const {
    int32_t rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // It makes no sense to parallelize this algorithm through MPI because the address spaces are different.
    
    if (rank == 0) {
        return getSimpleCyclicSumSubNode();
    }
    
    return tree::node();
}

#endif

tree::tree(const tree::node root) {
    mRoot = root;
}

tree tree::parseTree(const char* value) {
    tree::node result = tree::node::parseNode(value);
    return tree(result);
}

std::string tree::toString() const {
    return mRoot.toString();
}

tree tree::getSimpleRecursiveSumSubTree() const {
    tree::node result = mRoot.getSimpleRecursiveSumSubNode();
    return tree(result);
}

tree tree::getSimpleCyclicSumSubTree() const {
    tree::node result = mRoot.getSimpleCyclicSumSubNode();
    return tree(result);
}

tree tree::getPthreadCyclicSumSubTree() const {
    tree::node result = mRoot.getPthreadCyclicSumSubNode();
    return tree(result);
}

#ifdef MPI_ENABLED

tree tree::getMpiCyclicSumSubTree() const {
    tree::node result = mRoot.getMpiCyclicSumSubNode();
    return tree(result);
}

#endif