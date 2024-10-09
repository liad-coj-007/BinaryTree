#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>  
using namespace std;

template<class T>
class BinaryTree {
public:
    // Default constructor
    BinaryTree() : root(nullptr) {}

    /**
     * @brief Insert the value into the tree
     * @param value - the value to insert
     */
    void insert(const T &value) {
        insertToNode(root, value);
    }

    template<class ...Args>
    void insert(const T& value,Args... args){
        insert(value);
        insert(args...);
    }

    /**
     * @brief return true if the value in the tree
     * @param value - the value to search
     * @return true/false
     */
    bool find(const T &value) const {
        return findOnNode(root,value);
    }


    /**
     * @brief do desructor
     */
    ~BinaryTree(){
        DeleteNode(root);
    }

private:
    struct Node {
        T value;
        Node* left;
        Node* right;

        Node(const T &value) : value(value), left(nullptr), right(nullptr) {}
    };

    template<class ...Args>
    void insert(){
        //nothing happend
    }

    void DeleteNode(Node*& node){
        if(node == nullptr){
            return;
        }

        if(node->left != nullptr){
            DeleteNode(node->left);
        }

        if(node->right != nullptr){
            DeleteNode(node->right);
        }

        delete node;
    }

    /**
     * @brief do operator << ostream
     * @param os - the os we use
     * @param tree - the tree we print
     */
    friend ostream& operator<<(ostream &os,
    const BinaryTree<T> &tree){
        tree.printAsTree(tree.root,0,os);
        return os;
    }

    bool findOnNode(Node* node, const T &value) const {
        if (!node) return false;
        if (node->value == value) return true;
        return value < node->value ? findOnNode(node->left, value) : findOnNode(node->right, value);
    }

    void printAsTree(Node* node, int level, ostream &os) const {
        if (node == nullptr) return;

        printAsTree(node->right, level + 1, os);

        if (node->right) {
            os << setw(4 * level) << " "; 
            os << " /" << endl;
        }

        if (level > 0) {
            os << setw(4 * level) << ""; 
        }

        os << node->value << endl;

        if (node->left) {
            os << setw(4 * level) << " "; 
            os << " \\" << endl; 
        }

        printAsTree(node->left, level + 1, os);
    }

    /**
     * @brief Insert value into the node
     * @param &node - reference to the pointer where we put the value
     * @param value - the value to insert
     */
    void insertToNode(Node*& node, const T &value) {
        if (node == nullptr) {
            node = new Node(value);
            return;
        }

        if (value < node->value) {
            insertToNode(node->left, value);
        } else {
            insertToNode(node->right, value);
        }
    }

    Node* root; // Pointer to the root node
};