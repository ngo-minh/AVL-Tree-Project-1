#include "../src/main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <vector>
#include <algorithm>

/*
    To check output (At the Project1 directory):
        g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("Incorrect Commands") {
    AVLTree avlTree;

    // Test incorrect insert command with invalid ID
    REQUIRE(avlTree.insert("Alice Smith", 12345678) == true);  // ID is not 8 digits

    // Test incorrect insert command with invalid name
    REQUIRE(avlTree.insert("1234", 98765432) == false);  // Name contains digits

    // Test incorrect remove command with invalid ID
    REQUIRE(avlTree.remove(1234) == false);  // ID is not found

    // Test incorrect search command with invalid ID
    REQUIRE(avlTree.search(5678) == "unsuccessful");  // ID is not found

    // Test incorrect search command with invalid Name
    REQUIRE(avlTree.search("1234") == "unsuccessful");  // Name is not found
}


TEST_CASE("Edge Cases") {
    AVLTree avlTree;

    // Edge case 1: Remove a node that doesn't exist
    REQUIRE(avlTree.remove(12345678) == false);  // ID doesn't exist

    // Edge case 2: Search for a name that doesn't exist
    REQUIRE(avlTree.search("John") == "unsuccessful");  // Name is not found

    // Edge case 3: Insert the name with id and then insert another name with same id
    REQUIRE(avlTree.insert("Name", 10000001) == true);  // Insertion is successful
    REQUIRE(avlTree.insert("Name", 10000001) == false);  // ID already exists
}


TEST_CASE("Rotation Cases") {
    AVLTree avlTree;

    // Case 1: Left-Left Rotation
    avlTree.insert("A", 12345678);
    avlTree.insert("B", 12345679);
    avlTree.insert("C", 12345668);
    REQUIRE(avlTree.printPreorder() == "A, C, B");

    // Case 2: Left-Right Rotation
    avlTree = AVLTree(); // Reset the tree
    avlTree.insert("A", 12345678);
    avlTree.insert("C", 12345668);
    avlTree.insert("B", 12345679);
    REQUIRE(avlTree.printPreorder() == "A, C, B");

    // Case 3: Right-Right Rotation
    avlTree = AVLTree(); // Reset the tree
    avlTree.insert("C", 12345668);
    avlTree.insert("B", 12345679);
    avlTree.insert("A", 12345678);
    REQUIRE(avlTree.printPreorder() == "A, C, B");

    // Case 4: Right-Left Rotation
    avlTree = AVLTree(); // Reset the tree
    avlTree.insert("C", 12345668);
    avlTree.insert("A", 12345678);
    avlTree.insert("B", 12345679);
    REQUIRE(avlTree.printPreorder() == "A, C, B");
}

TEST_CASE("Deletion Cases") {
    AVLTree avlTree;

    // Case 1: Deletion with No Children
    avlTree.insert("A", 12345671);
    avlTree.insert("B", 12345672);
    avlTree.remove(12345671); // Remove the node with no children
    REQUIRE(avlTree.printPreorder() == "B");

    // Case 2: Deletion with 1 Child (Left Child)
    avlTree = AVLTree(); // Reset the tree
    avlTree.insert("A", 12345671);
    avlTree.insert("B", 12345672);
    avlTree.insert("C", 12345673);
    avlTree.remove(12345672); // Remove the node with 1 left child
    REQUIRE(avlTree.printPreorder() == "C, A");

    // Case 3: Deletion with 1 Child (Right Child)
    avlTree = AVLTree(); // Reset the tree
    avlTree.insert("A", 12345671);
    avlTree.insert("B", 12345672);
    avlTree.insert("C", 12345673);
    avlTree.remove(12345671); // Remove the node with 1 right child
    REQUIRE(avlTree.printPreorder() == "B, C");

    // Case 4: Deletion with 2 Children
    avlTree = AVLTree(); // Reset the tree
    avlTree.insert("A", 12345671);
    avlTree.insert("B", 12345672);
    avlTree.insert("C", 12345673);
    avlTree.remove(12345672); // Remove the node with 2 children
    REQUIRE(avlTree.printPreorder() == "C, A");
}

TEST_CASE("Insert and Remove 100 Nodes") {
    AVLTree avlTree;
    
    // Insert 100 nodes with unique IDs
    for (int id = 10000000; id < 10000100; ++id) {
        std::string name = "Name";
        avlTree.insert(name, id);
    }
    
    REQUIRE(avlTree.countNodes() == 100); // Verify the 100 insertions
    
    // Remove 10 random nodes
    std::vector<string> removedIds;
    for (int i = 0; i < 10; ++i) {
        int randomId = rand() % 100; // Generate a random number between 0 and 99
        
        // Add the random number to the lower bound (10000000) to get the randomId between 10000000 (inclusive) and 10000100 (exclusive)
        randomId = 10000000 + randomId;
        
        string name = avlTree.search(randomId);
        if (name != "unsuccessful") {
            avlTree.remove(randomId);
            removedIds.push_back(name);
        } else {
            i--;
        }
    }

    REQUIRE(avlTree.countNodes() == 90); // Verify the 90 nodes after removals
}
