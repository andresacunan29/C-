/***********************************************************
 *    FILE: GroceryList.hpp                                *
 *  AUTHOR: Andres Acuna                                                      *
 *    DATE: 10/2021                                         *
 *                                                         *
 ***********************************************************/
#ifndef _GROCERY_LIST_HPP
#define _GROCERY_LIST_HPP

#include <iostream>
#include <string>
#include "GroceryItem.hpp"

class GroceryList {
private:
    static const int INITIAL_CAPACITY { 5 };
    int _capacity;
    int _count;
    GroceryItem* _grocery_items;

public:
    GroceryList();
    int getLength() const;
    int numEmptySlots() const;
    GroceryList& operator=(const GroceryList& other);
    GroceryList operator+=(const GroceryItem& item);
    GroceryList operator+=(const GroceryList& other);
    GroceryList operator-=(const std::string& itemName);
    GroceryItem* operator[](const std::string& itemName) const;
    void checkOff(const std::string& itemName);

    GroceryList(const GroceryList& other);
    ~GroceryList();

    friend std::ostream& operator<<(std::ostream& ostr, const GroceryList& gl);
};

#endif