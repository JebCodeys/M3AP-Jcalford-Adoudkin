#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <random>
#include <cstdlib> // For system()
#include "SplayTree.h"
#include "AVLTree.h"
#include "BinarySearchTree.h" // Assuming you have this header

// Function to print depths for debugging
void printDepths(const BinarySearchTree<int>& bst, const std::vector<int>& testValues) {
    for (const auto& value : testValues) {
        int depth = 0;
        bst.find(value, depth);
        std::cout << "Value: " << value << ", Depth: " << depth << std::endl;
    }
}

int main() {
    // Initialize trees
    BinarySearchTree<int> bst;
    AVLTree<int> avl;
    SplayTree<int> splay;

    // Ensure the 'data' directory exists
    std::filesystem::create_directories("data");

    // Open output file for ordered insertion
    std::ofstream orderedFile("data/ordered_depths.csv");
    if (!orderedFile) {
        std::cerr << "Error opening ordered_depths.csv!" << std::endl;
        return 1;
    }
    orderedFile << "Value,BST_Depth,AVL_Depth,Splay_Depth\n"; // CSV header

    // Insert values 1-100 in order and record depths
    for (int i = 1; i <= 100; ++i) {
        bst.add(i);
        avl.add(i);
        splay.add(i);
    }
    for (int i = 1; i <= 100; ++i) {
        int depthBST = 0, depthAVL = 0, depthSplay = 0;
        bst.find(i, depthBST);
        avl.find(i, depthAVL);
        splay.find(i, depthSplay);
        orderedFile << i << "," << depthBST << "," << depthAVL << "," << depthSplay << "\n";
    }
    orderedFile.close();

    // Test with out-of-range values for debugging
    std::vector<int> testValues = {0, 101, 102};
    std::cout << "Testing BST with out-of-range values:\n";
    printDepths(bst, testValues);

    // Open output file for random insertion
    std::ofstream randomFile("data/random_depths.csv");
    if (!randomFile) {
        std::cerr << "Error opening random_depths.csv!" << std::endl;
        return 1;
    }
    randomFile << "Value,BST_Depth,AVL_Depth,Splay_Depth\n"; // CSV header

    // Insert values 1-100 in random order
    std::vector<int> randomValues(100);
    std::iota(randomValues.begin(), randomValues.end(), 1); // Fill with 1-100
    std::shuffle(randomValues.begin(), randomValues.end(), std::mt19937{std::random_device{}()});
    for (const int value : randomValues) {
        bst.add(value);
        avl.add(value);
        splay.add(value);
    }
    for (int i = 1; i <= 100; ++i) {
        int depthBST = 0, depthAVL = 0, depthSplay = 0;
        bst.find(i, depthBST);
        avl.find(i, depthAVL);
        splay.find(i, depthSplay);
        randomFile << i << "," << depthBST << "," << depthAVL << "," << depthSplay << "\n";
    }
    randomFile.close();

    // Call Python script to generate graphs
    std::cout << "Generating graphs with Python...\n";
    int result = std::system("python3 generate_graphs.py");
    if (result != 0) {
        std::cerr << "Error running Python script!" << std::endl;
        return 1;
    }

    return 0;
}