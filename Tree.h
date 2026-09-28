#ifndef TREE_HPP
#define TREE_HPP

#include <string>
#include <ostream>

template<typename T>
class Tree {

public:
    // Constructor
    explicit Tree(const T& data);

    // Copy constructor
    Tree(const Tree<T>& other);

    // Move constructor (marked noexcept)
    Tree(Tree<T>&& other) noexcept;

    // Destructor
    ~Tree();

    // Copy assignment operator
    Tree<T>& operator=(const Tree<T>& other);

    // Move assignment operator
    Tree<T>& operator=(Tree<T>&& other) noexcept;

    // Add child functions
    bool addChild(const T& data);
    bool addChild(Tree<T>* tree);

    // Add sibling functions
    bool addSibling(const T& data);
    bool addSibling(Tree<T>* tree);

    // Overloaded operators
    Tree<T>& operator+=(const T& data);
    Tree<T>& operator+=(Tree<T>& tree);
    bool operator==(const Tree<T>& other) const;

    // Convert to string
    std::string toString() const;

    // Output operator
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Tree<U>& tree);

private:
    T data;
    Tree<T>* kids;
    Tree<T>* sibs;
    Tree<T>* prev;

    void clear();
    static Tree<T>* createDuplicateTree(const Tree<T>* tree);
    void toStringHelper(std::ostringstream& os) const;

    friend class CTreeTest;
};

#include "Tree.inc"

#endif 
