#include "GroceryList.hpp"
#include <iostream>
#include <string>

GroceryList::GroceryList()
    : _capacity(INITIAL_CAPACITY), _count(0), _grocery_items(nullptr) {
    _grocery_items = new GroceryItem[_capacity];
}

int GroceryList::getLength() const {
    return _count;
}

int GroceryList::numEmptySlots() const {
    return _capacity - _count;
}

GroceryList& GroceryList::operator=(const GroceryList& other) {
    if (this == &other) {
        return *this;
    }

    delete[] _grocery_items;

    _capacity = other._capacity;
    _count = other._count;
    _grocery_items = new GroceryItem[_capacity];
    
    for (int i = 0; i < _count; i++) {
        _grocery_items[i] = other._grocery_items[i];
    }

    return *this;
}

GroceryList GroceryList::operator+=(const GroceryItem& item) {
    int index = -1;
    for (int i = 0; i < _count; i++) {
        if (_grocery_items[i].name() == item.name()) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        if (_count >= _capacity) {
            _capacity *= 2; // double the capacity
            GroceryItem* temp = new GroceryItem[_capacity];
            for (int i = 0; i < _count; i++) {
                temp[i] = _grocery_items[i];
            }
            delete[] _grocery_items;
            _grocery_items = temp;
        }
        _grocery_items[_count++] = item;
    } else {
        _grocery_items[index].quantity() = _grocery_items[index].quantity() + item.quantity();
    }

    return *this;
}

GroceryList GroceryList::operator+=(const GroceryList& other) {
    for (int i = 0; i < other._count; i++) {
        (*this) += other._grocery_items[i];
    }
    return *this;
}

GroceryList GroceryList::operator-=(const std::string& itemName) {
    int index = -1;
    for (int i = 0; i < _count; i++) {
        if (_grocery_items[i].name() == itemName) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        for (int i = index; i < _count - 1; i++) {
            _grocery_items[i] = _grocery_items[i + 1];
        }
        _count--;
    }

    return *this;
}

GroceryItem* GroceryList::operator[](const std::string& itemName) const {
    int index = -1;
    for (int i = 0; i < _count; i++) {
        if (_grocery_items[i].name() == itemName) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        return (GroceryItem*)(_grocery_items + index);
    }
    return nullptr;
}

void GroceryList::checkOff(const std::string& itemName) {
    int index = -1;
    for (int i = 0; i < _count; i++) {
        if (_grocery_items[i].name() == itemName) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        _grocery_items[index].bought() = true;
    }
}

std::ostream& operator<<(std::ostream& ostr, const GroceryList& gl) {
    for (int i = 0; i < gl._count; i++) {
        ostr << gl._grocery_items[i] << std::endl;
    }
    return ostr;
}

GroceryList::GroceryList(const GroceryList& other) {
    _grocery_items = nullptr;
    (*this) = other;
}

GroceryList::~GroceryList() {
    delete[] _grocery_items;
}
