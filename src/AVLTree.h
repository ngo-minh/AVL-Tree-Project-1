#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <iostream>
using namespace std;

class AVLTree
{
    private:
        struct Node
        {
            string name;
            int id;
            Node* left;
            Node* right;
            int height;

            // constructor for node structure
            Node(const string& n, int i) : name(n), id(i), left(nullptr), right(nullptr), height(1) {}
        };

        Node* root;

        int height(Node* node);
        int balanceFactor(Node* node);
        Node* rotateRight(Node* node);
        Node* rotateLeft(Node* node);
        Node* balance(Node* node);
        Node* insert(Node* node, const string& name, int id);
		string search(Node* node, const int& id);
        void searchName(Node* node, const string& name, string& result);
        Node* remove(Node* node, int id);
        string inorder(Node* node);
        string preorder(Node* node);
        string postorder(Node* node);
        int countLevels(Node* node);
        Node* removeNthInorder(Node* node, int& n);
        int countNodes(Node* node);
        bool isValidId(int id);
        bool isValidName(const string& name);
        bool idDuplicateValidation(Node* node, int id);

    public:
        AVLTree();  // constructor
        ~AVLTree(); // destructor

        void destroyTree(Node* node);
        bool insert(const string& name, int id);
        bool remove(int id);
        string search(const int& id);
        string search(const string& name);
        string printInorder();
        string printPreorder();
        string printPostorder();
        int printLevelCount();
        bool removeInorder(int n);
        int countNodes();
        bool isValidIdRegex(const std::string &idStr);
};

#endif // AVL_TREE_H
