
//#include "../src/main.cpp"
//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"
//#include <vector>
//#include <algorithm>



/*
TEST_CASE("Incorrect Commands") {
    AVLTree avlTree;

    // test incorrect insert command with invalid ID
    REQUIRE(avlTree.insert("Alice Smith", 123456789) == false);

    // test incorrect insert command with invalid name
    REQUIRE(avlTree.insert("1234", 98765432) == false);

    // test incorrect remove command with invalid ID
    REQUIRE(avlTree.remove(1234) == false);
    // test incorrect search command with invalid ID
    REQUIRE(avlTree.search(5678) == "unsuccessful");
    // test incorrect search command with invalid Name
    REQUIRE(avlTree.search("1234") == "unsuccessful");
}


TEST_CASE("Edge Cases") {
    AVLTree avlTree;

    // remove a node that doesn't exist
    REQUIRE(avlTree.remove(12345678) == false);

    // search for a name that doesn't exist
    REQUIRE(avlTree.search("John") == "unsuccessful");

    // insert the name with id and then insert another name with same id
    REQUIRE(avlTree.insert("Name", 10000001) == true);
    REQUIRE(avlTree.insert("Name", 10000001) == false);
}


TEST_CASE("Rotation Cases") {
    AVLTree avlTree;

    // right rotation
    avlTree.insert("A", 10000013);
    avlTree.insert("B", 10000012);
    avlTree.insert("C", 10000011);
    REQUIRE(avlTree.printPreorder() == "B, C, A");

    // left-right rotation
    avlTree = AVLTree();
    avlTree.insert("A", 10000013);
    avlTree.insert("C", 10000011);
    avlTree.insert("B", 10000012);
    REQUIRE(avlTree.printPreorder() == "B, C, A");

    // right-left Rotation
    avlTree = AVLTree();
    avlTree.insert("C", 10000018);
    avlTree.insert("B", 10000021);
    avlTree.insert("A", 10000020);
    REQUIRE(avlTree.printPreorder() == "A, C, B");

    // left Rotation
    avlTree = AVLTree();
    avlTree.insert("C", 10000013);
    avlTree.insert("A", 10000014);
    avlTree.insert("B", 10000015);
    REQUIRE(avlTree.printPreorder() == "A, C, B");
}

TEST_CASE("Deletion Cases") {
    AVLTree avlTree;

    // deletion with 0 children
    avlTree.insert("A", 10000013);
    avlTree.insert("B", 10000014);
    avlTree.remove(10000014);
    REQUIRE(avlTree.printPreorder() == "A");

    // deletion with 2 child
    avlTree = AVLTree();
    avlTree.insert("A", 10000013);
    avlTree.insert("B", 10000014);
    avlTree.insert("C", 10000015);
    avlTree.remove(10000014);
    REQUIRE(avlTree.printPreorder() == "C, A");

    // deletion with 1 child (right child)
    avlTree = AVLTree();
    avlTree.insert("A", 10000013);
    avlTree.insert("B", 10000014);
    avlTree.insert("C", 10000015);
    avlTree.insert("D", 10000016);
    avlTree.remove(10000015);
    REQUIRE(avlTree.printPreorder() == "B, A, D");

    // deletion with 1 child (left child)
    avlTree = AVLTree();
    avlTree.insert("A", 10000013);
    avlTree.insert("B", 10000014);
    avlTree.insert("C", 10000012);
    avlTree.insert("D", 10000011);
    avlTree.remove(10000012);
    REQUIRE(avlTree.printPreorder() == "A, D, B");
}

TEST_CASE("Insert and Remove 100 Nodes") {
    AVLTree avlTree;
    
    // insert 100 nodes
    for (int id = 10000000; id < 10000100; ++id) {
        std::string name = "Name";
        avlTree.insert(name, id);
    }
    
    REQUIRE(avlTree.countNodes() == 100); // verify
    
    // Remove 10 random nodes
    std::vector<string> removedIds;
    for (int i = 0; i < 10; ++i) {
        int randomId = rand() % 100; // generate a random number b/t 0 and 99

        randomId = 10000000 + randomId;
        
        string name = avlTree.search(randomId);
        if (name != "unsuccessful") {
            avlTree.remove(randomId);
            removedIds.push_back(name);
        } else {
            i--;
        }
    }

    REQUIRE(avlTree.countNodes() == 90); // verify
}
*/