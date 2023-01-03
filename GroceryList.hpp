#ifndef GROCERY_LIST_H
#define GROCERY_LIST_H

#include "GroceryItem.hpp"

// Representation of a binary search tree node.
struct Node {
    GroceryItem data;
    Node* left;
    Node* right;
};

class GroceryList {
public:
    GroceryList();
    int getLength() const;
    GroceryList& operator=(const GroceryList& other);
    GroceryList operator+=(const GroceryItem& item);
    GroceryList operator+=(const GroceryList& other);
    GroceryList operator-=(const std::string& itemName);
    GroceryItem* operator[](const std::string& itemName) const;
    void checkOff(const std::string& itemName);

    friend std::ostream& operator<<(std::ostream& ostr, const GroceryList& groceryList);
private:
    Node* m_root;   // pointer to the root node.
    int m_count;    // total number of nodes in the binary search tree.
};

std::ostream& operator<<(std::ostream& ostr, const GroceryList& groceryList);

#endif