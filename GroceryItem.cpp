
#include "GroceryItem.hpp"

using namespace std;

// method to print to given stream 
ostream&
GroceryItem::print(ostream &os) const
{
  os << _name << "  (" << _quantity << ") PURCHASED? " ;
  if (_bought)
    os << "YES";
  else
    os << "NO";

  return os; 
}

// method to read from given stream 
istream&
GroceryItem::read(istream &is)
{
  is >>  _name >> _quantity; // just read name and quantity ...
  _bought=false;             //      ... assume not bought yet

  return is; 
}

//implement overloaded << by calling print. 
ostream& operator<<(ostream &os, const GroceryItem &gi)
{
  return gi.print(os);
}

//implement overloaded >> by calling read. 
istream& operator>>(istream &is, GroceryItem &gi)
{
  return gi.read(is);
}
