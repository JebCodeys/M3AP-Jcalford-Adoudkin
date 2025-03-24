#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>  // For std::max

template <typename Comparable>
class AVLTree {
private:
    // Node structure for the AVL tree
    struct AVLNode {
        Comparable element;   // Stored value
        AVLNode* left;        // Left child pointer
        AVLNode* right;       // Right child pointer
        int height;           // Height of the subtree rooted at this node

        AVLNode(const Comparable& theElement, AVLNode* lt = nullptr, AVLNode* rt = nullptr)
            : element(theElement), left(lt), right(rt), height(0) {}
    };

    AVLNode* root;  // Root of the tree

    // Compute the height of a node
    int height(AVLNode* t) const {
        return (t == nullptr) ? -1 : t->height;
    }

    // Update the height of a node based on its children
    void updateHeight(AVLNode* t) {
        if (t != nullptr) {
            t->height = std::max(height(t->left), height(t->right)) + 1;
        }
    }

    // Calculate the balance factor of a node
    int balanceFactor(AVLNode* t) const {
        return height(t->left) - height(t->right);
    }

    // Single rotation with left child (right rotation)
    AVLNode* rotateWithLeftChild(AVLNode* k2) {
        AVLNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        updateHeight(k2);
        updateHeight(k1);
        return k1;
    }

    // Single rotation with right child (left rotation)
    AVLNode* rotateWithRightChild(AVLNode* k1) {
        AVLNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        updateHeight(k1);
        updateHeight(k2);
        return k2;
    }

    // Double rotation: left-right case
    AVLNode* doubleWithLeftChild(AVLNode* k3) {
        k3->left = rotateWithRightChild(k3->left);
        return rotateWithLeftChild(k3);
    }

    // Double rotation: right-left case
    AVLNode* doubleWithRightChild(AVLNode* k1) {
        k1->right = rotateWithLeftChild(k1->right);
        return rotateWithRightChild(k1);
    }

    // Insert a new element and rebalance the tree
    AVLNode* insert(const Comparable& x, AVLNode* t) {
        if (t == nullptr) {
            return new AVLNode(x);  // New leaf node
        }

        if (x < t->element) {
            t->left = insert(x, t->left);
        } else if (t->element < x) {
            t->right = insert(x, t->right);
        } else {
            return t;  // Duplicate value, no insertion
        }

        updateHeight(t);
        return balance(t);
    }

    // Balance the tree after insertion
    AVLNode* balance(AVLNode* t) {
        int bf = balanceFactor(t);
        if (bf == 2) {  // Left-heavy
            if (balanceFactor(t->left) >= 0) {  // Left-left case
                return rotateWithLeftChild(t);
            } else {  // Left-right case
                return doubleWithLeftChild(t);
            }
        } else if (bf == -2) {  // Right-heavy
            if (balanceFactor(t->right) <= 0) {  // Right-right case
                return rotateWithRightChild(t);
            } else {  // Right-left case
                return doubleWithRightChild(t);
            }
        }
        return t;  // Already balanced
    }

public:
    // Constructor: initializes an empty tree
    AVLTree() : root(nullptr) {}

    // Add a new element to the tree
    void add(const Comparable& c) {
        root = insert(c, root);
    }

    // Find an element and return its depth
    int find(const Comparable& x, int& depth) const {
        AVLNode* current = root;
        depth = 0;  // Start at root (depth 0)
        while (current != nullptr) {
            if (x < current->element) {
                current = current->left;
                ++depth;
            } else if (current->element < x) {
                current = current->right;
                ++depth;
            } else {
                return depth;  // Found the element
            }
        }
        return 100;  // Not found, return sentinel value
    }

    // Destructor or cleanup could be added if needed (not required here)
};

#endif // AVLTREE_H