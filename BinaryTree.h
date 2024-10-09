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

    /**
     * @brief adding insert values
     * @param value - the value we add
     * @param args - the other vals we add 
     */
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

    void erase(const T& value){
        root = eraseData(root,value);
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
    /**
     * @brief insert none args
     */
    void insert(){
        //nothing happend
    }

    /**
     * @brief free  node data 
     * @param node the node we free
    */
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

    /**
     * @brief return true if the value
     * is in the node
     * @param node - the node we search on
     * @param value - the value we take
     */
    bool findOnNode(Node* node, const T &value) const {
        if (!node) return false;
        if (node->value == value) return true;
        return value < node->value ? findOnNode(node->left, value) : findOnNode(node->right, value);
    }

    /**
     * @brief return the node without the value
     * @param node - the node we change
     * @param value - the value we want to delete
     */
    Node* eraseData(Node *&node,const T &value){
        if(node == nullptr){
            return node;
        }

        if(node->value == value){
             return eraseNode(node);
        }

        if(value < node->value){
            node->left =  eraseData(node->left,value);
        }else{
            node->right = eraseData(node->right,value);
        }

        return node;
    }

    /**
     * @brief erase the node from the data
     * @param node - the node we delete
     * @return a newnode of the data
     * the node has
     */
    Node* eraseNode(Node* &node){
        Node* newnode = node->right;
        Node* minnode = min(newnode);
        if(minnode == nullptr){
            newnode = node->left;
        }else{
            minnode->left = node->left;
        }
        node->right = nullptr;
        node->left = nullptr;
        DeleteNode(node);
        return newnode;
    }


   

    /**
     * @brief return the min node
     * @param node - the node we search the minimyne
     */
    Node* min(Node*& node){
        if(node == nullptr || node->left == nullptr){
            return node;
        }
        return min(node->left);
    }

    /**
     * @brief print the as a tree nodes values
     * @param level - the level of the tree
     * @param os - the os we use
     */
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