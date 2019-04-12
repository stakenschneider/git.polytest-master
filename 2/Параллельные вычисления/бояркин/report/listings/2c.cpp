< ... >

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

< ... >
