#ifndef BINARY_TREE_TREE_H
#define BINARY_TREE_TREE_H

#include <iostream>

template <typename T>
class Node{
public:
    T data;
    Node<T> *left, *right;
    explicit Node(T key): data{key}, left{nullptr}, right{nullptr} {}
};

template <typename T>
class Tree{
public:
    Node<T>* root;

    Tree(){
        this->root = nullptr;
    }

    explicit Tree(T value){
        root->data = value;
        root->left = nullptr;
        root->right = nullptr;
    }

    void print2DUtil(Node<T> *root, int space){
        if (root == nullptr)
            return;

        space += 2;

        print2DUtil(root->right, space);

        std::cout<<std::endl;

        for (int i = 2; i < space; i++)
            std::cout<<" ";

        std::cout<<root->data<<"\n";

        print2DUtil(root->left, space);
    }

    void print() {
        print2DUtil(root, 0);
    }

    bool isEmpty(){
        return root == nullptr;
    }

    void insert(T data) {
        Node<T>* t = new Node(data);
        Node<T>* parent;
        parent = NULL;

        if(isEmpty()) {
            root = t;
            root->left = nullptr;
            root->right = nullptr;
        }

        else {
            Node<T>* curr = root;

            while(curr) {
                parent = curr;
                if (t->data > curr->data)
                    curr = curr->right;
                else
                    curr = curr->left;
            }

            if ((t->data) < (parent->data))
                parent->left = t;
            else
                parent->right = t;
        }

    }
    Node<T>* get_root(){
        return root;
    }

    void clear(Node<T>* root){
        if( root == NULL )
            return;
        if( root->left != NULL )
            clear(root->left );
        if( root->right != NULL )
            clear( root->right );

        delete root;
    }

    Node<T>* minValueNode(Node<T>* node)
    {
        Node<T>* current = node;

        while (current && current->left != NULL)
            current = current->left;

        return current;
    }

    void erase(T key){
        erase(root, key);
    }

    Node<T>* erase(Node<T> *root, T data) {
        if (root == NULL)
            return root;

        if (data < root->data) {
            root->left = erase(root->left, data);
        }

        else if (data > root->data) {
            root->right = erase(root->right, data);
        }

        else {
            if (root->left == NULL) {
                Node<T>* temp = root->right;
                free(root);
                return temp;
            }
            else if (root->right == NULL) {
                Node<T>* temp = root->left;
                free(root);
                return temp;
            }

            Node<T>* temp = minValueNode(root->right);

            root->data = temp->data;

            root->right = erase(root->right, temp->data);
        }
        return root;
    }

    int height(){
        return height(this->get_root());
    }

    int height(Node<T>* node) {
        if (node == nullptr)
            return 0;
        else
            return 1 + std::max(height(node->left), height(node->right));

    }

    ~Tree(){
        clear(root);
    }
};

#endif //BINARY_TREE_TREE_H