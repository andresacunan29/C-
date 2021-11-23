/***********************************************************
 *    FILE: GroceryList.cpp                                *
 *  AUTHOR: Andres Acuna                                   *
 *    DATE: 11/2021                                        *
 * PURPOSE:   CSC24400 project 3                           *
 ***********************************************************/

#include "GroceryList.hpp"

//default (no argument) constructor no actual GroceryItems
GroceryList::GroceryList() 
    : m_head(nullptr), m_count(0) {
}

// takes no arguments and returns an integer, current number of GroceryItems
int GroceryList::getLength() const {
    return m_count;
}

//contains an exact duplicate of each GroceryItem in the right hand side GroceryList.
GroceryList& GroceryList::operator=(const GroceryList& other) {
    if (this == &other) {
        return *this;
    }

    clear();
    copy(m_head, other.m_head);
    m_count = other.m_count;

    return *this;
}

void GroceryList::copy(ListNode*& dest, ListNode* src)
{
	if (!src) {
        return;
    }
	dest = new ListNode(src->groceryItem);
	copy(dest->next, src->next);
}

void GroceryList::clear() {
    ListNode* current = m_head;
    while (current) {
        ListNode* remaining = current->next;
        delete current;
        current = remaining;
    }
    m_head = nullptr;
    m_count = 0;
}

// when the grocery item already exists it is updated to be the sum of the two associated quantities.
GroceryList GroceryList::operator+=(const GroceryItem& item) {
    ListNode* previous = nullptr;
    for (ListNode* current = m_head; current != nullptr; current = current->next) {
        if (current->groceryItem.name() == item.name()) {
            current->groceryItem.quantity() += item.quantity();
            return *this;
        }
        previous = current;
    }

    // if previous is nullptr it means 'this' list was empty.
    // else previous points to the last node of the list.
    
    ListNode* new_node = new ListNode(item);
    if (previous) {
        previous->next = new_node;
    } else {
        m_head = new_node;
    }
    m_count++;

    return *this;
}


GroceryList GroceryList::operator+=(const GroceryList& other) {
    for (ListNode* current = other.m_head; current != nullptr; current = current->next) {
        (*this) += current->groceryItem;
    }
    return *this;
}


//when the right hand side is a string 
GroceryList GroceryList::operator-=(const std::string& item_name) {
    ListNode* temp = m_head;
    ListNode* prev = nullptr;

    //an item is found in the GroceryList, then that item 
    //should be removed from the GroceryList.

    if (temp != nullptr && temp->groceryItem.name() == item_name) {
        m_head = temp->next;
        delete temp;
        return *this;
    } else {
        while (temp != nullptr && temp->groceryItem.name() != item_name) {
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr) {
            return *this;
        }
        prev->next = temp->next;
        delete temp;
    }

    return *this;
}

//return a pointer to the corresponding GroceryItem if it is found in GroceryList
GroceryItem* GroceryList::operator[](const std::string& item_name) const {
    for (ListNode* current = m_head; current != nullptr; current = current->next) {
        if (current->groceryItem.name() == item_name) {
            return &current->groceryItem;
        }
    }//NULL otherwise
    return nullptr;
}

//single string parameter representing the name of a GroceryItem to mark as purchased
void GroceryList::checkOff(const std::string& item_name) {
    for (ListNode* current = m_head; current != nullptr; current = current->next) {
        if (current->groceryItem.name() == item_name) {
            current->groceryItem.bought() = true;
            return;
        }
    }
}

void GroceryList::print(std::ostream& ostr) const {
    for (ListNode* current = m_head; current != nullptr; current = current->next) {
        ostr << current->groceryItem << std::endl;
    }
}

//to output to a stream, the order the GroceryItems are listed is not important
std::ostream& operator<<(std::ostream& ostr, const GroceryList& groceryList) {
    groceryList.print(ostr);
    return ostr;
}