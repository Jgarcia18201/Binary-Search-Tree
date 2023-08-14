#include <iostream>

using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node(int key) {
        this->key = key;
        this->left = this->right = nullptr;
    }
};

class BST {
private:
    Node* root;

    Node* search(Node* root, int key) {
        if (root == nullptr || root->key == key)
            return root;

        if (root->key < key)
            return search(root->right, key);

        return search(root->left, key);
    }

    Node* insert(Node* root, int key) {
        if (root == nullptr)
            return new Node(key);

        if (root->key < key)
            root->right = insert(root->right, key);
        else if (root->key > key)
            root->left = insert(root->left, key);

        return root;
    }

    Node* remove(Node* root, int key) {
        if (root == nullptr)
            return root;

        if (root->key < key)
            root->right = remove(root->right, key);
        else if (root->key > key)
            root->left = remove(root->left, key);
        else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = remove(root->right, temp->key);
        }
        return root;
    }

    int nodeLevel(Node* root, int key, int level) {
        if (root == nullptr)
            return -1;
        if (root->key == key)
            return level;
        int left = nodeLevel(root->left, key, level + 1);
        if (left == -1)
            return nodeLevel(root->right, key, level + 1);
        return left;
    }

    Node* minValueNode(Node* root) {
        Node* current = root;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    void inOrder(Node* root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    int nodeLevel(int key) {
        return nodeLevel(root, key, 0);
    }

    bool search(int key) {
        return search(root, key) != nullptr;
    }

    void print() {
        inOrder(root);
    }
};

int main() {
    BST bst;

    // Inserting elements
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);
    bst.insert(90);
    bst.insert(100);
    bst.insert(110);

    // Searching for an element
    int searchKey = 90;
    if (bst.search(searchKey))
        cout << searchKey << " is found in the tree" << endl;
    else
        cout << searchKey << " is not found in the tree" << endl;

    // Removing an element
    int removeKey = 20;
    bst.remove(removeKey);
    cout << "After removing " << removeKey << ", the tree is: ";
    bst.print();
    cout << endl;

    // Finding the level of a node
    int levelKey = 100;
    int level = bst.nodeLevel(levelKey);
    if (level != -1)
        cout << "The level of node " << levelKey << " is: " << level << endl;
    else
        cout << levelKey << " is not found in the tree" << endl;

    return 0;
}