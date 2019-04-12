< ... >

tree::node tree::node::getSimpleRecursiveSumSubNode() const {
    double sum = 0;
    tree::node result = tree::node();
    for (const auto& currentChild : mChilds) {
        sum += currentChild.mValue;
        result.addChild(currentChild.getSimpleRecursiveSumSubNode());
    }
    
    result.mValue = sum;
    return result;
}

< ... >
