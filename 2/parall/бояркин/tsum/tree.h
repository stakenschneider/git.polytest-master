#ifndef TREE_H
#define TREE_H

#include <memory>
#include <vector>
#include <mutex>
#include <stack>
#include "config.h"

class tree {
private:
    static const char OPEN_BRACKET = '(';
    static const char CLOSE_BRACKET = ')';
    static const char DELIMITER = ',';
    
    class node {
    private:
        double mValue;
        std::vector<tree::node> mChilds;
        
        struct parg {
            std::mutex* stackNodesMutex;
            std::mutex* valuesMutex;
#ifdef POOL_ENABLED
            std::mutex* threadsMutex;
            const uint8_t* threadsLimit;
            uint8_t* threadsCount;
#endif
            std::stack<std::pair<tree::node*, tree::node*>>* stackNodes;
        };
        
        static void* getPthreadCyclicSumSubNodeHandler(void* argument);
        
    public:
        node();
        node(const double value);
        static tree::node parseNode(const char* value);
        std::string toString() const;
        void setValue(const double value);
        double getValue() const;
        void addChild(const tree::node& child);
        std::vector<tree::node> getChilds() const;
        tree::node getSimpleCyclicSumSubNode() const;
        tree::node getSimpleRecursiveSumSubNode() const;
        tree::node getPthreadCyclicSumSubNode() const;
    #ifdef MPI_ENABLED
        tree::node getMpiCyclicSumSubNode() const;
    #endif
    };
private:
    tree::node mRoot;
    tree(const tree::node root);
public:
    static tree parseTree(const char* value);
    std::string toString() const;
    tree getSimpleCyclicSumSubTree() const;
    tree getSimpleRecursiveSumSubTree() const;
    tree getPthreadCyclicSumSubTree() const;
#ifdef MPI_ENABLED
    tree getMpiCyclicSumSubTree() const;
#endif
};

#endif /* TREE_H */

