#include <iostream>
#include <sstream>
#include <utility> 

// Constructor
template<typename T>
Tree<T>::Tree(const T& data) {
    this->data = data;
    kids = nullptr;
    sibs = nullptr;
    prev = nullptr;
}

// Copy constructor
template<typename T>
Tree<T>::Tree(const Tree<T>& other) {
    data = other.data;
    kids = createDuplicateTree(other.kids);
    sibs = createDuplicateTree(other.sibs);
    prev = nullptr; // Root node's prev should be nullptr
}

// Move constructor
template<typename T>
Tree<T>::Tree(Tree<T>&& other) noexcept {
    data = std::move(other.data);
    kids = other.kids;
    sibs = other.sibs;
    prev = other.prev;
    other.kids = nullptr;
    other.sibs = nullptr;
    other.prev = nullptr;
}

// Destructor
template<typename T>
Tree<T>::~Tree() {
    clear();
}

// Copy assignment operator
template<typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    data = other.data;
    kids = createDuplicateTree(other.kids);
    sibs = createDuplicateTree(other.sibs);
    return *this;
}

// Move assignment operator
template<typename T>
Tree<T>& Tree<T>::operator=(Tree<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    clear();
    data = std::move(other.data);
    kids = other.kids;
    sibs = other.sibs;
    prev = nullptr;
    other.kids = nullptr;
    other.sibs = nullptr;
    other.prev = nullptr;
    return *this;
}

// Adds a child with the given data
template<typename T>
bool Tree<T>::addChild(const T& data) {
    if (!kids) {
        kids = new Tree<T>(data);
        kids->prev = this;
        return true;
    }
    if (data < kids->data) {
        Tree<T>* new_node = new Tree<T>(data);
        new_node->sibs = kids;
        new_node->prev = this;
        kids->prev = new_node;
        kids = new_node;
        return true;
    }
    return kids->addSibling(data);
}

// Adds a child node from an existing tree
template<typename T>
bool Tree<T>::addChild(Tree<T>* tree) {
    if (!tree || tree->prev || tree->sibs) {
        return false;
    }
    if (!kids) {
        kids = tree;
        tree->prev = this;
        return true;
    }
    if (tree->data < kids->data) {
        tree->sibs = kids;
        kids->prev = tree;
        tree->prev = this;
        kids = tree;
        return true;
    }
    return kids->addSibling(tree);
}

// Adds a sibling with the given data
template<typename T>
bool Tree<T>::addSibling(const T& data) {
    // Cannot add siblings to the root
    if (!prev) {
        return false; 
    }
    //prevents duplicates
    if (data == this->data) {
        return false; 
    }
    if (data < this->data) {
        Tree<T>* new_node = new Tree<T>(data);
        new_node->sibs = this;
        new_node->prev = prev;
        if (prev->kids == this) {
            prev->kids = new_node;
        } else {
            prev->sibs = new_node;
        }
        prev = new_node;
        return true;
    }
    if (!sibs) {
        sibs = new Tree<T>(data);
        sibs->prev = this;
        return true;
    }
    return sibs->addSibling(data);
}

// Adds a sibling node
template<typename T>
bool Tree<T>::addSibling(Tree<T>* tree) {
    if (!prev || !tree || tree->prev || tree->sibs) {
        return false;
    }
    if (tree->data == this->data) {
        return false;
    }
    if (tree->data < this->data) {
        tree->sibs = this;
        tree->prev = prev;
        if (prev->kids == this) {
            prev->kids = tree;
        } else {
            prev->sibs = tree;
        }
        prev = tree;
        return true;
    }
    if (!sibs) {
        sibs = tree;
        tree->prev = this;
        return true;
    }
    return sibs->addSibling(tree);
}

// Overloaded += operator
template<typename T>
Tree<T>& Tree<T>::operator+=(const T& data) {
    addChild(data);
    return *this;
}

// Overloaded += operator
template<typename T>
Tree<T>& Tree<T>::operator+=(Tree<T>& tree) {
    if (tree.prev) return *this; // Prevent adding a tree that's already attached
    addChild(&tree);
    return *this;
}

// Equality operator
template<typename T>
bool Tree<T>::operator==(const Tree<T>& other) const {
    return data == other.data &&
           ((!kids && !other.kids) || (kids && other.kids && *kids == *other.kids)) &&
           ((!sibs && !other.sibs) || (sibs && other.sibs && *sibs == *other.sibs));
}

// Clears the tree
template<typename T>
void Tree<T>::clear() {
    delete kids;
    delete sibs;
    kids = sibs = nullptr;
}

// Helper function to duplicate
template<typename T>
Tree<T>* Tree<T>::createDuplicateTree(const Tree<T>* tree) {
    if (!tree) return nullptr;
    Tree<T>* copy = new Tree<T>(tree->data);
    copy->kids = createDuplicateTree(tree->kids);
    if (copy->kids) copy->kids->prev = copy;
    copy->sibs = createDuplicateTree(tree->sibs);
    if (copy->sibs) copy->sibs->prev = copy;
    return copy;
}

// Optimized toString using a helper function
template<typename T>
std::string Tree<T>::toString() const {
    std::ostringstream os;
    toStringHelper(os);
    return os.str();
}

template<typename T>
void Tree<T>::toStringHelper(std::ostringstream& os) const {
    os << data << '\n';
    if (kids) kids->toStringHelper(os);
    if (sibs) sibs->toStringHelper(os);
}

// Output stream operator for Tree<T>
template<typename T>
std::ostream& operator<<(std::ostream& os, const Tree<T>& tree) {
    os << tree.toString();
    return os;
}
