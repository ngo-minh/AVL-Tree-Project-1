#include "AVLTree.h"
#include <regex>

// ++++++++++++++++++++++++++++++++++++++++++ CONSTRUCTORS AND DESTRUCTORS ++++++++++++++++++++++++++++++++++++++++++
AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {

    destroyTree(root);
}

// ++++++++++++++++++++++++++++++++++++++++++ PUBLIC FUNCTIONS ++++++++++++++++++++++++++++++++++++++++++

// recursive function to destroy tree
void AVLTree::destroyTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// public insert w/ name and id
bool AVLTree::insert(const string& name, int id)
{
    if (idDuplicateValidation(root, id)) { //checking for duplicates
        return false;
    }

    Node* tmp = insert(root, name, id);
    if (tmp != nullptr)
    {
        root = tmp;
        return true;
    }
    else {
        return false;
    }
}

// public remove given tree id, first uses search to find if id exists
bool AVLTree::remove(int id)
{
    if (search(id) == "unsuccessful")
    {
        return false;
    }

    root = remove(root, id);
    return true;
}

// public search for id, returns name
string AVLTree::search(const int& id)
{
    return search(root, id);
}

// public search for name, returns id
string AVLTree::search(const string& name)
{
    string result;
    searchName(root, name, result);;

    if (result.empty()) {
        return "unsuccessful";
    } else {
        return result;
    }
}

// return string of tree inorder
string AVLTree::printInorder()
{
    return inorder(root);
}

// return string of tree preorder
string AVLTree::printPreorder()
{
    return preorder(root);
}

// return string of tree postorder
string AVLTree::printPostorder() {
    return postorder(root);
}

// return int of levels
int AVLTree::printLevelCount()
{
    int levels = countLevels(root);
    cout << levels << endl;
    return levels;
}

// public function to remove nth node given n. returns true or false if removed or not.
bool AVLTree::removeInorder(int n) {
    if (n < 0 || n >= countNodes(root)) {
        return false;
    }

    if (n == 0) { // to find the smallest node
        Node* curr = root;
        Node* par = nullptr;
        while (curr->left != nullptr){ // when curr can no longer transverse left then has reached smallest node
            par = curr;
            curr = curr->left;
        }

        if (par == nullptr) { // check if root is smallest value
            root = remove(root, curr->id);
            return true;
        } else {
            par->left = remove(curr, curr->id);
            return true;
        }
    } else {
        removeNthInorder(root, n);
        return true;

    }
}

// to count nodes
int AVLTree::countNodes()
{
    return countNodes(root);
}

// ++++++++++++++++++++++++++++++++++++++++++ PRIVATE HELPERS FUNCTIONS ++++++++++++++++++++++++++++++++++++++++++

// height of node
int AVLTree::height(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

// balance factor is height of left - right
int AVLTree::balanceFactor(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// rotate right from Balanced Tree Slides
// https://ufl.instructure.com/courses/488814/pages/module-4-balanced-trees/
AVLTree::Node* AVLTree::rotateRight(Node* node)
{
    Node* grandchild = node->left->right;
    Node* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;


    node->height = 1 + max(height(node->left), height(node->right));
    newParent->height = 1 + max(height(newParent->left), height(newParent->right));

    return newParent;
}

// rotate left from Balanced Tree Slides
// https://ufl.instructure.com/courses/488814/pages/module-4-balanced-trees/
AVLTree::Node* AVLTree::rotateLeft(Node* node)
{
    Node* grandchild = node->right->left;
    Node* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;

    node->height = 1 + max(height(node->left), height(node->right));
    newParent->height = 1 + max(height(newParent->left), height(newParent->right));

    return newParent;
}

// https://stackoverflow.com/questions/19278236/avl-tree-balance
AVLTree::Node* AVLTree::balance(Node* node)
{
    int bf = balanceFactor(node);

    if (bf > 1) // left left or left right
    {
        if (balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (bf < -1) // right-right or right-left
    {
        if (balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

// insert concept from module 4 slides w/ name and id parameter w/ regex data validation
// https://ufl.instructure.com/courses/488814/pages/module-4-balanced-trees/
AVLTree::Node* AVLTree::insert(Node* node, const string& name, int id)
{

    // validation with regex
    bool nameVal = isValidName(name);
    if(nameVal != true){
        return nullptr;
    }

    if (node == nullptr)
    {
        return new Node(name, id);
    }

    if (id < node->id) // if less than root node insert left, and balance
    {
        Node* result = insert(node->left, name, id);
        node->left = result;
        node->height = 1 + max(height(node->left), height(node->right));
        return balance(node);

    }
    else if (id > node->id) // if greater than root node insert right, and balance
    {
        Node* result = insert(node->right, name, id);
        node->right = result;
        node->height = 1 + max(height(node->left), height(node->right));
        return balance(node);
    }
    else
    {
        return nullptr;
    }
}


// concept https://prepinsta.com/cpp-program/deletion-in-avl-tree/
// transverses by recursion like BST tree, consider one, 0, and 2 child scenarios
// uses balance helper function to balance node after
AVLTree::Node* AVLTree::remove(Node* node, int deleteID) {
    if (node == nullptr) {
        return nullptr;
    }

    // recursion to transverse tree and find node to delete
    if (deleteID < node->id) {
        node->left = remove(node->left, deleteID);
    } else if (deleteID > node->id) {
        node->right = remove(node->right, deleteID);
    } else {
        if ((node->left == nullptr) || (node->right == nullptr)) { // one or 0 child
            Node* tempNode;

            if (node->left == nullptr) { // 1 child case
                tempNode = node->right;
            } else if (node->right == nullptr) {
                tempNode = node->left;
            }

            if (tempNode == nullptr) { // 0 child case
                node = nullptr;
            } else {
                *node = *tempNode;
            }

            delete tempNode;
        } else if (node->left != nullptr && node->right != nullptr) { // two child check
            // find the inorder successor
            Node* tempNode = node->right;
            while (tempNode->left != nullptr) {
                tempNode = tempNode->left;
            }
            node->id = tempNode->id;
            node->name = tempNode->name;
            node->right = remove(node->right, tempNode->id); // favors the inorder successor
        }
    }

    if (node == nullptr) { // if tree only has one node
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    node = balance(node);

    return node;
}

// search for node with ID and return corresponding name
string AVLTree::search(Node* node, const int& id)
{
    if (node == nullptr)
    {
        return "unsuccessful";
    }

    // standard BST search
    if (id == node->id)
    {
        return node -> name;
    }
    else if (id < node->id)
    {
        return search(node->left, id);
    }
    else
    {
        return search(node->right, id);;
    }
}

// search for the corresponding name and return ID
void AVLTree::searchName(Node* node, const string& name, string& result)
{
    if (node == nullptr)
    {
        return;
    }

    if (name.compare(node->name)==0)
    {
        if(result.size() > 0)
        {
            result += "\n";
        }
        result += to_string(node->id);
    }

    // recursively calls twice to check both left and right side
    searchName(node->left, name, result);
    searchName(node->right, name, result);
}

// returns a string of node names under inorder transversal
string AVLTree::inorder(Node* node)
{
    if (node == nullptr)
    {
        return "";
    }

    string current = "";
    string leftStr = inorder(node->left);

    if (leftStr.size() > 0)
    {
        current += leftStr + ", ";
    }

    current += node->name; // middle because inorder
    string rightStr = inorder(node->right);

    if (rightStr.size() > 0)
    {
        current += ", " + rightStr;
    }

    return current;
}

// returns a string of node names under preorder transversal
string AVLTree::preorder(Node* node)
{
    if (node == nullptr)
    {
        return "";
    }

    string current = node->name; // start because preorder
    string leftStr = preorder(node->left);

    if (leftStr.size() > 0)
    {
        current += ", " + leftStr;
    }

    string rightStr = preorder(node->right);

    if (rightStr.size() > 0)
    {
        current += ", " + rightStr;
    }

    return current;
}



// returns a string of node names under postorder transversal
string AVLTree::postorder(Node* node) {
    if (node == nullptr) {
        return "";
    }

    string current = "";
    string leftStr = postorder(node->left);

    if (leftStr.size() > 0) {
        current += leftStr + ", ";
    }

    string rightStr = postorder(node->right);

    if (rightStr.size() > 0) {
        current += rightStr + ", ";
    }

    current += node->name; // end because postorder

    return current;
}


// count the heights of left and right side and finds the max between them + 1
int AVLTree::countLevels(Node* node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int leftLevels = countLevels(node->left);
    int rightLevels = countLevels(node->right);

    return max(leftLevels, rightLevels) + 1;
}

// helper function for removeInorder given n
AVLTree::Node* AVLTree::removeNthInorder(Node* node, int& n)
{
    if (node == nullptr)
    {
        return node;
    }


    node->left = removeNthInorder(node->left, n);

    if (n == 0) // when nth node is found i.e becomes 0 then it removes the node.
    {
        root = remove(root, node->id);
        n--;
        return nullptr;
    }

    n--;


    node->right = removeNthInorder(node->right, n);

    return node;
}


// counts the total numbers of nodes in tree
int AVLTree::countNodes(Node* node)
{
    if (node == nullptr) // if head of node is null print 0
    {
        return 0;
    }
    else
    {
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
}

// data validation for ID with regex
bool AVLTree::isValidIdRegex(const string &idStr) {
    regex id("^\\d{8}$");
    return regex_match(idStr, id);
}

// data validation for name check for leading space and trailing, may include only words (case sensitive)
bool AVLTree::isValidName(const string& name) {
    regex name_pattern("^ *([a-zA-Z]+( [a-zA-Z]+)*) *$");
    return regex_match(name, name_pattern);
}

// checking for any duplicate values before insertion
bool AVLTree::idDuplicateValidation(Node* node, int id) {
    if (node == nullptr) {
        return false;
    }
    if (node->id == id) {
        return true;
    }
    if (id < node->id) {
        return idDuplicateValidation(node->left, id);
    } else {
        return idDuplicateValidation(node->right, id);
    }
}