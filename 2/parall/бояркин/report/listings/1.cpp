< ... >

class tree {
private:
    < ... >
    
    class node {
    private:
        double mValue;
        std::vector<tree::node> mChilds;
        
        < ... >
        
    public:
        node();
        node(const double value);
        static tree::node parseNode(const char* value);
        std::string toString() const;
        void setValue(const double value);
        double getValue() const;
        void addChild(const tree::node& child);
        std::vector<tree::node> getChilds() const;

        < ... >
    };

private:
    tree::node mRoot;
    tree(const tree::node root);
public:
    static tree parseTree(const char* value);
    std::string toString() const;

    < ... >
};

< ... >
