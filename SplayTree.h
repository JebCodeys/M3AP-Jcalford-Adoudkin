
#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>

template <typename Comparable>
class SplayTree {
private:
    // Node structure for the splay tree
    struct SplayNode {
        Comparable element;   // Stored value
        SplayNode* left;      // Left child pointer
        SplayNode* right;     // Right child pointer

        SplayNode(const Comparable& theElement, SplayNode* lt = nullptr, SplayNode* rt = nullptr)
            : element(theElement), left(lt), right(rt) {}
    };

    SplayNode* root;  // Root of the tree

    // Splay operation: moves the accessed node to the root and tracks depth
    SplayNode* splay(const Comparable& x, SplayNode* t, int& depth) {
        if (t == nullptr) {
            return nullptr;  // Empty tree or not found
        }

        if (x < t->element) {
            if (t->left == nullptr) return t;  // No further left subtree
            depth++;
            if (x < t->left->element) {
                t->left->left = splay(x, t->left->left, depth);  // Zig-zig case
                t = rotateWithRightChild(t);
            } else if (x > t->left->element) {
                t->left->right = splay(x, t->left->right, depth);  // Zig-zag case
                if (t->left->right != nullptr) {
                    t->left = rotateWithLeftChild(t->left);
                }
            }
            return (t->left == nullptr) ? t : rotateWithRightChild(t);
        } else if (t->element < x) {
            if (t->right == nullptr) return t;  // No further right subtree
            depth++;
            if (t->right->element < x) {
                t->right->right = splay(x, t->right->right, depth);  // Zig-zig case
                t = rotateWithLeftChild(t);
            } else if (x < t->right->element) {
                t->right->left = splay(x, t->right->left, depth);  // Zig-zag case
                if (t->right->left != nullptr) {
                    t->right = rotateWithRightChild(t->right);
                }
            }
            return (t->right == nullptr) ? t : rotateWithLeftChild(t);
        }
        return t;  // Found the element
    }

    // Rotate a node with its left child (right rotation)
    SplayNode* rotateWithLeftChild(SplayNode* k2) {
        if (k2 == nullptr || k2->left == nullptr) return k2;
        SplayNode* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        return k1;
    }

    // Rotate a node with its right child (left rotation)
    SplayNode* rotateWithRightChild(SplayNode* k1) {
        if (k1 == nullptr || k1->right == nullptr) return k1;
        SplayNode* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        return k2;
    }

    // Insert a new element into the tree
    SplayNode* insert(const Comparable& x, SplayNode* t) {
        int depth = 0;  // Temporary depth tracker for splay
        if (t == nullptr) {
            return new SplayNode(x);  // New leaf node
        }

        t = splay(x, t, depth);  // Splay to bring similar value to root
        if (t->element == x) {
            return t;  // Duplicate value, no insertion
        }

        SplayNode* newNode = new SplayNode(x);
        if (x < t->element) {
            newNode->right = t;
            newNode->left = t->left;
            t->left = nullptr;
        } else {
            newNode->left = t;
            newNode->right = t->right;
            t->right = nullptr;
        }
        return newNode;
    }

public:
    // Constructor: initializes an empty tree
    SplayTree() : root(nullptr) {}

    // Add a new element to the tree
    void add(const Comparable& c) {
        root = insert(c, root);
    }

    // Find an element and return its depth, splaying it to the root
    int find(const Comparable& x, int& depth) {
        depth = 0;  // Reset depth
        root = splay(x, root, depth);
        if (root == nullptr || root->element != x) {
            return 100;  // Not found, return sentinel value
        }
        return depth;  // Return depth of found element (now at root)
    }

    // Destructor or cleanup could be added if needed (not required here)
};

#endif // SPLAYTREE_H