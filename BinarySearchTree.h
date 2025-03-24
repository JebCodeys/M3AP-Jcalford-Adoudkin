#ifndef BINARYSEARCHTREE_H
#define PROJECT3STARTER_BINARYSEARCHTREE_H

#include <memory>

template <typename Comparable>
class BinarySearchTree {
private:
    struct BinaryNode {
        Comparable value;
        BinaryNode* leftChild;
        BinaryNode* rightChild;

        // Constructors
        BinaryNode() : value(Comparable()), leftChild(nullptr), rightChild(nullptr) {}
        explicit BinaryNode(Comparable c) : value(c), leftChild(nullptr), rightChild(nullptr) {}
        BinaryNode(Comparable c, BinaryNode* l, BinaryNode* r) : value(c), leftChild(l), rightChild(r) {}
    };
    BinaryNode* root;
    unsigned long size;

    // Helper recursive function to destroy the tree.
    void destroy(BinaryNode* &n) {
        if (n != nullptr) {
            destroy(n->leftChild);
            destroy(n->rightChild);
            delete n;
            n = nullptr;
        }
    }

    // Helper recursive function to copy the tree.
    BinaryNode* copyNode(BinaryNode* n) {
        if (n == nullptr) {
            return nullptr;
        }
        ++size;
        return new BinaryNode(n->value, copyNode(n->leftChild), copyNode(n->rightChild));
    }

    // Helper recursive function to find a value in the tree.
    bool find(const Comparable &c, BinaryNode* n, int& depth) const {
        if (n == nullptr) {
            depth = -1;
            // Reached a dead end. Value not in tree.
            return false;
        }
        if (c < n->value) {
            depth++;
            // Value is less than current node. Go to node's left child.
            return find(c, n->leftChild,depth);
        }
        if (n->value < c) {
            depth++;
            // Value is greater than current node. Go to node's right child.
            return find(c, n->rightChild, depth);
        }
        // If code reaches here, c == n->value. Node found!
        return true;
    }

    bool find(const Comparable &c, BinaryNode* n) const {
        int depth = 0;
        return find(c, n, depth);
    }

    // Helper recursive function to add a value to the tree.
    bool add(const Comparable &c, BinaryNode* &n) {
        if (n == nullptr) {
            // We found the place where we can add the node.
            n = new BinaryNode(c, nullptr, nullptr);
            ++size;
            return true;
        }
        else if (c < n->value) {
            // Value is less than current node. Go to left child.
            return add(c, n->leftChild);
        }
        else if (n->value < c) {
            // Value is greater than current node. Go to right child.
            return add(c, n->rightChild);
        }
        // If code reaches here, value is a duplicate. Cannot add it to the tree.
        return false;
    }

    // Helper recursive method to find the maximum value from a given node.
    Comparable& findMax(BinaryNode* n) {
        if (n->rightChild == nullptr) {
            return n->value;
        }
        return findMax(n->rightChild);
    }

    // Helper recursive function to delete a value from the tree.
    void remove(const Comparable &c, BinaryNode* &n) {
        if (n == nullptr) {
            // We did not find the value. Cannot remove it. Nothing to do.
            return;
        }
        else if (c < n->value) {
            // Value is less than current node. Go to left child.
            remove(c, n->leftChild);
        }
        else if (n->value < c) {
            // Value is greater than current node. Go to right child.
            remove(c, n->rightChild);
        }
        // If code reaches here, we found the node. Now to remove it.
        else if (n->leftChild != nullptr && n->rightChild != nullptr) {
            // The node we want to remove has two children
            // Find the largest value from the left subtree
            n->value = findMax(n->leftChild);
            remove(n->value, n->leftChild);
        }
        else {
            // The node we want to remove has 0 or 1 child.
            // If it has a child, move it up. If not, set to nullptr.
            BinaryNode *oldNode = n;
            n = (n->leftChild != nullptr) ? n->leftChild : n->rightChild;
            delete oldNode;
            oldNode = nullptr;
            --size;
        }
    }

public:
    // Default Constructor
    BinarySearchTree() {
        root = nullptr;
        size = 0;
    }

    // Copy Constructor
    BinarySearchTree(const BinarySearchTree &b) {
        size = 0;
        // calls private helper function
        root = copyNode(b.root);
    }

    // Destructor
    ~BinarySearchTree() {
        // calls private helper function
        destroy(root);
    }

    // Method to destroy tree
    void timber() {
        // calls private helper function
        destroy(root);
    }

    bool isEmpty() const {
        return (root == nullptr);
    }
    bool find(const Comparable &c, int& depth) const {
        depth = 0;
        // calls private helper function
        return find(c, root, depth);
    }

    bool find(const Comparable &c) const {
        // calls private helper function
        return find(c, root);
    }

    bool add(const Comparable &c) {
        // calls private helper function
        return add(c, root);
    }

    void remove(const Comparable &c) {
        // calls private helper function
        remove(c, root);
    }

    unsigned long getSize() const {
        return size;
    }

    // Overloaded = operator
    BinarySearchTree& operator = (const BinarySearchTree &rhs) {
        destroy(root);
        size = 0;
        root = copyNode(rhs.root);
    }
}