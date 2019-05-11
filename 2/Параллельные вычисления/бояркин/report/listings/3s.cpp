< ... >

class node {
    private:
        < ... >
        
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

< ... >
