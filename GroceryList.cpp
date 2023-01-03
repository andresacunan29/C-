#include "GroceryList.hpp"
#include <iostream>

GroceryList::GroceryList() 
    : m_root(nullptr), m_count(0) {
}

int GroceryList::getLength() const {
    return m_count;
}

static void copy(Node*& dest, const Node* src)
{	
    // base case.
    if (src == nullptr) {
		dest = nullptr;
		return;
	}

    // actual copying of the nodes.
	Node* new_node = new Node();
	new_node->data = src->data;
	new_node->left = nullptr;
	new_node->right = nullptr;
	dest = new_node;

    // recursive calls.
	copy(dest->left, src->left);
	copy(dest->right, src->right);
}

static void destroy(Node*& node) {
    if (node != nullptr) {

        // Recursively destroy all children first.
        destroy(node->left);
        destroy(node->right);

        // Destroy current node.
        delete node;
    }
    node = nullptr;
}

static Node* search(Node* root, const GroceryItem& item) {
    // base case 1: we found an empty tree and therefore, item is not there.
    // base case 2: we found the match. Done.
    if (root == nullptr || root->data.name() == item.name()) {
        return root;
    }
    // otherwise, recursively search for item in its children.
    if (item.name().compare(root->data.name()) < 0) {
        return search(root->left, item);
    }
    return search(root->right, item);
}

static Node* search(Node* root, const std::string& itemName) {
    if (root == nullptr || root->data.name() == itemName) {
        return root;
    }
    if (itemName < root->data.name()) {
        return search(root->left, itemName);
    }
    return search(root->right, itemName);
}

static void insert(Node*& node, const GroceryItem& item) {
    if (node == nullptr) {
        Node* new_node = new Node();
        new_node->data = item;
        new_node->left = nullptr;
        new_node->right = nullptr;
        node = new_node;
    }
    else {
        if (item.name() < node->data.name()) {
            insert(node->left, item);
        } else {
            insert(node->right, item);
        }
    }
}

GroceryList& GroceryList::operator=(const GroceryList& other) {
    // Self reference: nothing should happen.
    if (this == &other) {
        return *this;
    }

    // Free existing heap memory associated with current object.
    destroy(m_root);

    // Copy everything over.
    copy(m_root, other.m_root);
    m_count = other.m_count;

    // Keep chain of assignments alive by returning a reference to the current object.
    return *this;
}

GroceryList GroceryList::operator+=(const GroceryItem& item) {
    // Search for a matching node.
    Node* found = search(m_root, item);
        
    // if found, update that node.
    if (found) {
        found->data.quantity() += item.quantity();
    }

    // else insert a new node
    else {
        insert(m_root, item);
        m_count++;
    }

    // Return a copy of current object.
    return *this;
}

static void inorderTraversal(Node* node, GroceryList& list) {
    // Base case.
    if (! node) {
        return;
    }

    // Recursively traverse left child first, then this node and then
    // the right child.
    inorderTraversal(node->left, list);

    // Add item stored in the current node to the list (passed as reference).
    list += node->data;
    
    inorderTraversal(node->right, list);
}

GroceryList GroceryList::operator+=(const GroceryList& other) {
    // Iterate over all items in other grocery list
    // and add each item to this grocery list
    inorderTraversal(other.m_root, *this);

    // Return a copy of current object.
    return *this;
}

static Node* findMin(Node* node) {
    // By the condition of BST, all the values to the left of any node are smaller than that of the node 
	// itself. So we keep going to the left of left of left (and so on...) until we hit a node which doesn't 
	// have any left node -which means there is no smaller value than this one. That's our desired minimum value.

	// The caller must makes sure the tree entered is not nullptr.
    if (node->left == nullptr) {
        return node;
    }
    return findMin(node->left);
}

// Retuns true if the node is removed successfully form the tree. Returns false otherwise.
static bool remove(Node*& node, const std::string& name)
{
	// Base case-1: If we hit an empty tree, the value is not here. We are done!
	// Base case-2: If we find the value:
	// If the value to to remove is less than current value (of the node), remove from left subtree.
	// If the value to remove is more than current value (of the node), remove from the right subtree.

	if(node == nullptr){
		// Nothing to do. Value is not here.
		return false;
	}
	else if (node->data.name() == name) {

		// remove this node

		// case 1: The node has no child.
		// case 2: The node has one child.
		// case 3: The node has two children.

		// No child:
		// ( this block is unnecessary, since One child block handles this just fine)
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			node = nullptr;
		}

		// One child:
		else if (node->right == nullptr) {
			Node* temp = node->left;
			delete node;
			node = temp;
		}
		else if (node->left == nullptr) {
			Node* temp = node->right;
			delete node;
			node = temp;
		}

		// Two children
		// 1. Find the minimum from the right subtre or the maximum from the left subtree.
		// 2. Update the current node with either of those values.
		// 3. Delete the duplicate from the right or the left subtree depending on which was chosen in step 1.

		else {
			Node* minOfRightSubtree = findMin(node->right);
			node->data = minOfRightSubtree->data;
			remove(node->right, node->data.name());
		}

		return true;
	}
	else {
		if (name < node->data.name())
			return remove(node->left, name);
		else return remove(node->right, name);
	}
}

GroceryList GroceryList::operator-=(const std::string& itemName) {
    if (remove(m_root, itemName)) {
        m_count--;
    }
    return *this;
}

GroceryItem* GroceryList::operator[](const std::string& itemName) const {
    Node* found = search(m_root, itemName);
    if (found) {
        return &found->data;
    }
    return nullptr;
}

void GroceryList::checkOff(const std::string& itemName) {
    Node* found = search(m_root, itemName);
    if (found) {
        found->data.bought() = true;
    }
}

static void print(Node* root, std::ostream& ostr) {
    // Base case: tree is empty and therefore, nothing to print.
    if (! root) {
        return;
    }

    // Recursively print left child first then current node and finally the right child.
    print(root->left, ostr);
    ostr << root->data << std::endl;
    print(root->right, ostr);
}

std::ostream& operator<<(std::ostream& ostr, const GroceryList& groceryList) {
    print(groceryList.m_root, ostr);
    return ostr;
}