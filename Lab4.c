#include <iostream>
#include <vector>
#include "island_solution.h"

/**
 * Runs a test case for the numIslands function.
 * 
 * @param grid The 2D grid representing land and water.
 * @param expectedResult The expected number of islands.
 * @param testNumber The test case number.
 */
void runTest(std::vector<std::vector<char>> grid, int expectedResult, int testNumber) {
    Solution solution;
    
    // Create a copy of the grid as DFS modifies it
    std::vector<std::vector<char>> gridCopy = grid;
    
    int result = solution.numIslands(gridCopy);
    
    std::cout << "Test " << testNumber << ": ";
    if (result == expectedResult) {
        std::cout << "PASSED";
    } else {
        std::cout << "FAILED";
    }
    std::cout << " (Expected: " << expectedResult << ", Got: " << result << ")" << std::endl;
    
    // Print the original grid for reference
    std::cout << "Grid for Test " << testNumber << ":" << std::endl;
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    // Test cases
    
    // Example 1
    std::vector<std::vector<char>> grid1 = {
        {'1','1','1','1','0'},
        {'1','1','0','1','0'},
        {'1','1','0','0','0'},
        {'0','0','0','0','0'}
    };
    runTest(grid1, 1, 1);
    
    // Example 2
    std::vector<std::vector<char>> grid2 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    runTest(grid2, 3, 2);
    
    // Additional test case: Empty grid
    std::vector<std::vector<char>> grid3 = {};
    runTest(grid3, 0, 3);
    
    // Additional test case: Single cell (land)
    std::vector<std::vector<char>> grid4 = {{'1'}};
    runTest(grid4, 1, 4);
    
    // Additional test case: Single cell (water)
    std::vector<std::vector<char>> grid5 = {{'0'}};
    runTest(grid5, 0, 5);
    
    // Additional test case: Diagonal islands (not connected)
    std::vector<std::vector<char>> grid6 = {
        {'1','0','1'},
        {'0','1','0'},
        {'1','0','1'}
    };
    runTest(grid6, 5, 6);
    
    // Additional test case: Complex pattern
    std::vector<std::vector<char>> grid7 = {
        {'1','1','0','0','1'},
        {'1','0','0','0','0'},
        {'0','0','1','1','0'},
        {'0','1','0','1','0'}
    };
    runTest(grid7, 4, 7);
    
    return 0;
}



//Symmetric

#include <iostream>
#include <vector>
#include <queue>
#include "solution.h"

/**
 * Constructs a binary tree from a level-order traversal array.
 * Null values are represented as -101 (since the problem states node values are in the range [-100, 100]).
 * 
 * @param values The level-order traversal array.
 * @return The root node of the constructed binary tree.
 */
TreeNode* constructTree(const std::vector<int>& values) {
    if (values.empty() || values[0] == -101) {
        return nullptr;
    }
    
    TreeNode* root = new TreeNode(values[0]);
    std::queue<TreeNode*> q;
    q.push(root);
    
    size_t i = 1;
    while (!q.empty() && i < values.size()) {
        TreeNode* current = q.front();
        q.pop();
        
        // Add left child
        if (i < values.size() && values[i] != -101) {
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        i++;
        
        // Add right child
        if (i < values.size() && values[i] != -101) {
            current->right = new TreeNode(values[i]);
            q.push(current->right);
        }
        i++;
    }
    
    return root;
}

/**
 * Frees the memory allocated for a binary tree.
 * 
 * @param root The root node of the binary tree.
 */
void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

/**
 * Runs a test case for the isSymmetric function.
 * 
 * @param values The level-order traversal array of the binary tree.
 * @param expectedResult The expected result of the isSymmetric function.
 * @param testNumber The test case number.
 */
void runTest(const std::vector<int>& values, bool expectedResult, int testNumber) {
    Solution solution;
    TreeNode* root = constructTree(values);
    
    bool result = solution.isSymmetric(root);
    
    std::cout << "Test " << testNumber << ": ";
    if (result == expectedResult) {
        std::cout << "PASSED";
    } else {
        std::cout << "FAILED";
    }
    std::cout << " (Expected: " << (expectedResult ? "true" : "false")
              << ", Got: " << (result ? "true" : "false") << ")" << std::endl;
    
    deleteTree(root);
}

int main() {
    // Test cases
    
    // Example 1: [1,2,2,3,4,4,3]
    // This is a symmetric tree, should return true
    runTest({1, 2, 2, 3, 4, 4, 3}, true, 1);
    
    // Example 2: [1,2,2,null,3,null,3]
    // This is not symmetric, should return false
    // Representing null as -101 (since values are in range [-100, 100])
    runTest({1, 2, 2, -101, 3, -101, 3}, false, 2);
    
   
    return 0;
}
