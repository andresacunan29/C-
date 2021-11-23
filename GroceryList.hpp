/***********************************************************
 *    FILE: GroceryList.hpp                                *
 *  AUTHOR: Andres Acuna                                   *
 *    DATE: 11/2021                                        *
 * PURPOSE:   CSC24400 project 3                           *
 ***********************************************************/
#ifndef GROCERY_LIST_HPP
#define GROCERY_LIST_HPP

#include <string>
#include "GroceryItem.hpp"

class ListNode {
public:
    ListNode(const GroceryItem& item)
        : groceryItem(item), next(nullptr) {}

    GroceryItem groceryItem;
    ListNode* next;
};


class GroceryList {
public:
    GroceryList();
    int getLength() const;

    // all the overloading in other class, not in ListNode
    GroceryList& operator=(const GroceryList& other);
    GroceryList operator+=(const GroceryItem& item);
    GroceryList operator+=(const GroceryList& other);
    GroceryList operator-=(const std::string& item_name);
    GroceryItem* operator[](const std::string& item_name) const;
    void checkOff(const std::string& item_name);
    void print(std::ostream& ostr) const;
    
private:
    void clear();
    void copy(ListNode*& dest, ListNode* src);

private:
    ListNode* m_head;
    int m_count;
};


std::ostream& operator<<(std::ostream& ostr, const GroceryList& groceryList);

#endif