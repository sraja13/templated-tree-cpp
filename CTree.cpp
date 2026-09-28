#include "CTree.h"
#include <iostream>
#include <ostream>


//constructor, intitializing root with the character input
CTree::CTree(char c){
    data = c;
    kids= nullptr;
    sibs= nullptr;
    prev= nullptr;
}


//copy constructor, makes a  copy of the tree
CTree::CTree(const CTree &tree) {
    data = tree.data;
    kids = createDuplicateTree(tree.kids);
    sibs = createDuplicateTree(tree.sibs);
    //the root doesnt have a previous node so needs to be set to nullptr
    prev = nullptr;
}
//destructor, recursively deletes all sibilngs and kids
CTree::~CTree(){
    if(kids){
        delete kids;
        kids = nullptr;
    }
    if(sibs){
        delete sibs;
        sibs = nullptr;
    }
}
//Assignment operator
CTree &CTree::operator=(const CTree &right_side) {
    // checks if it's assinging to itslef
    if (this == &right_side) {
        return *this;
    }


    // Clears the current children and siblings
    clear();

    // Copies the root data from rhs to this
    this->data = right_side.data;

    // Copies the children and siblings from the right side by calling createDuplicateTree
    kids = createDuplicateTree(right_side.kids);
    if (kids != nullptr) {
        //sets the parent pointer
        kids->prev = this;  
    }

    sibs = createDuplicateTree(right_side.sibs);
    if (sibs != nullptr) {
        sibs->prev = this;
    }

    return *this;
}


//create Duplicate Tree method
CTree* createDuplicateTree(const CTree* tree) {
    if (tree == nullptr) {
        return nullptr;
    }

    // Create a new node with the same data
    CTree* copy = new CTree(tree->data);

    // Recursively copy the children
    copy->kids = createDuplicateTree(tree->kids);
    if (copy->kids != nullptr) {
        copy->kids->prev = copy;
    }

    // Recursively copies the siblings
    copy->sibs = createDuplicateTree(tree->sibs);
    if (copy->sibs != nullptr) {
        copy->sibs->prev = copy;
    }

    return copy;
}

//addChild for character parameter

bool CTree::addChild(char c) {
    // If there are no children,  the new child is added as the first child
    if (kids == nullptr) {
        kids = new CTree(c);
        kids->prev = this;
        return true;
    }

    // If the new child should be inserted before the first child 
    if (c < kids->data) {
        CTree* new_node = new CTree(c);
        new_node->sibs = kids;
        new_node->prev = this;
        kids->prev = new_node;
        kids = new_node;
        return true;
    }

    return kids->addSibling(c);
}


//addChild for trees (overloaded)
bool CTree::addChild(CTree* tree) {
    if (tree == nullptr || tree->prev != nullptr || tree->sibs != nullptr) {
        return false;
    }

    // If there are no children, add the tree as the first child
    if (kids == nullptr) {
        kids = tree;
        tree->prev = this;
        return true;
    }

    // If the new child should be inserted before the first child
    if (tree->data < kids->data) {
        tree->sibs = kids;
        kids->prev = tree;
        tree->prev = this;
        kids = tree;
        return true;
    }

    // Otherwise, delegate to the addSibling method of the first child
    return kids->addSibling(tree);
}


//addSibling with a character being passed in
bool CTree::addSibling(char c) {
    // Do not add siblings to the root 
    if (prev == nullptr) {
        return false;
    }

    // Prevents duplicates
    if (data == c) {
        return false;
    }

    // If the new sibling should be inserted before the current node
    if (c < data) {
        CTree* new_node = new CTree(c);
        new_node->sibs = this;
        new_node->prev = prev;
        if (prev != nullptr) {
            prev->sibs = new_node;
        }
        prev = new_node;
        return true;
    }

    // If no more siblings exist, add the new sibling here
    if (sibs == nullptr) {
        sibs = new CTree(c);
        sibs->prev = this;
        return true;
    }

    // Recursively calls addSibling to keep th eorder 
    return sibs->addSibling(c);
}



void CTree::clear() {
    // Recursively delete children
    if (kids) {
        delete kids;
        kids = nullptr;
    }

    // Recursively delete siblings
    if (sibs) {
        delete sibs;
        sibs = nullptr;
    }
}

//addSibling with the root of an existing tree
bool CTree::addSibling(CTree* tree) {
    // Do not add siblings to the root node
    if (prev == nullptr) {
        return false;
    }

    // makes sure there exists a tree
    if (tree == nullptr || tree->prev != nullptr || tree->sibs != nullptr) {
        return false;
    }

    // Prevent duplicates
    if (data == tree->data) {
        return false;
    }

    // If the new sibling should be inserted before the current node
    if (tree->data < data) {
        tree->sibs = this;
        tree->prev = prev;
        if (prev != nullptr) {
            prev->sibs = tree;
        }
        prev = tree;
        return true;
    }

    // If no more siblings exist, add the new sibling here
    if (sibs == nullptr) {
        sibs = tree;
        tree->prev = this;
        return true;
    }

    // Recursively call addSibling 
    return sibs->addSibling(tree);
}

//+= operator
CTree &CTree::operator+=(char c){
    addChild(c);
    return *this;
}

//overloaded ==operator
bool CTree::operator==(const CTree &other) const{
    //checks if the data is equal or not
    if(this->data != other.data){
        return false;
    }

    //checks if the kids of both trees are equal
    bool equal_kids;
    if((this->kids==nullptr)&&(other.kids==nullptr)){
        equal_kids=true;
    }
    else if(this->kids==nullptr || other.kids==nullptr){
        equal_kids=false;
    }
    else{
        equal_kids= (*this->kids==*other.kids);
    }
    //checks if the sibs are equall
    bool equal_sibs;
    if((this->sibs==nullptr)&&(other.sibs==nullptr)){
        equal_sibs=true;
    }
    else if(this->sibs ==nullptr || other.sibs==nullptr){
        equal_sibs=false;
    }
    else{
        equal_sibs= (*this->sibs==*other.sibs);
    }
    
    if(!equal_kids){
        return false;
    }
    if(!equal_sibs){
        return false;
    }

    return true;
    
}
//overlaoded += operator for tree
CTree& CTree::operator+=(CTree &tree) {
    addChild(&tree);
    return *this;
}

//<<operator
std::ostream &operator<<(std::ostream &output,const CTree &tree){
    output<<tree.toString();
    return output;
}



//toString function
std::string CTree::toString() const {
    // traverse root
    std::string result;
    result.push_back(data);
    result.push_back('\n');

    // traverse children
    if (kids != nullptr) {
        result += kids->toString();
    }

    // traverse siblings
    if (sibs != nullptr) {
        result += sibs->toString();
    }

    return result;
}

