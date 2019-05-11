< ... >

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

< ... >
