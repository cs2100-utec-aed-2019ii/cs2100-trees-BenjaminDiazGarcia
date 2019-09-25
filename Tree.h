#ifndef BINARY_TREE_TREE_H
#define BINARY_TREE_TREE_H

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

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

    Tree() {
        this->root = nullptr;
    }

    explicit Tree(T value) {
        root = new Node(value);
    }

    void print2DUtil(Node<T> *root, int space) {
        if (root == nullptr)
            return;

        space += 2;

        print2DUtil(root->right, space);

        cout << endl;

        for (int i = 2; i < space; i++)
            cout<<" ";

        cout<<root->data<<"\n";

        print2DUtil(root->left, space);
    }

    void print() {
        print2DUtil(root, 0);
    }

    bool isEmpty() {
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

    void clear (Node<T>* node){
        if (node == nullptr)
            return;

        clear(node->left);
        clear(node->right);
        cout << "\nDelete: " << node->data;
        delete node;

        this->root = nullptr;

    }

    Node<T>* min(Node<T> *node) {
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

            Node<T>* temp = min(root->right);

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
            return 1 + max(height(node->left), height(node->right));

    }

    void inorder(Node<T>* node) {
        if (node == NULL)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node<T>* node) {
        if (node == NULL)
            return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node<T>* node) {
        if (node == NULL)
            return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    vector<Node<T>*> find_ancestors(Node<T>* node) {
        vector<Node<T>*> ancestors;
        if (node == root || node == NULL)
            return ancestors;
        else {
            T node_key = node->data;
            Node<T>* temp = root;
            while (temp != NULL && temp->data != node_key) {
                ancestors.push_back(temp);
                if (node_key > temp->data)
                    temp = temp->right;
                else
                    temp = temp->left;
            }
            return ancestors;
        }
    }

    Node<T>* node_with_value(const T& value) {
        Node<T>* curr = root;

        while (curr != NULL) {
            if (value == curr->data) {
                return curr;
            } else {
                if (value > curr->data)
                    curr = curr->right;
                else
                    curr = curr->left;
            }
        }
        return NULL;
    }

    bool identical(Node<T> *a, Node<T> *b) {
        if (a == nullptr && b == nullptr)
            return true;

        if (a != nullptr && b != nullptr) {
            return ( a->data == b->data && identical(a->left, b->left) && identical(a->right, b->right) );
        }

        return false;
    }

    Node<T>* next_node_in_same_level(Node<T>* node) {

        if (node == nullptr || node == this->get_root())
            return nullptr;

        queue<Node<T>*> q;
        vector<Node<T>*> vector;


        q.push(this->get_root());

        while (!q.empty()) {
            Node<T>* node2 = q.front();

            q.pop();

            if (node2->left != nullptr) {
                vector.push_back(node2->left);
                q.push(node2->left);
            }

            if (node2->right != nullptr) {
                vector.push_back(node2->right);
                q.push(node2->right);
            }

            for (int i = 0; i < vector.size(); i++){
                if (vector[i]->data == node->data && i != vector.size()-1)
                    cout << vector[i+1]->data << " ";
            }
            vector.clear();
        }
    }

    bool is_height_balanced(Node<T> *node) {
        int left;
        int right;

        if (node == NULL)
            return true;

        left = height(node->left);
        right = height(node->right);

        if (abs(left - right) <= 1 && is_height_balanced(node->left) && is_height_balanced(node->right))
            return true;

        return false;
    }

    ~Tree(){
        clear(root);
    }
};

template <typename T>
int is_bst(Node<T> *node, int min, int max);

template <typename T>
int is_bst(Node<T> *node) {
    return(is_bst(node, INT_MIN, INT_MAX));
}

template <typename T>
int is_bst(Node<T> *node, int min, int max) {
    if (node == nullptr)
        return 1;

    if (node->data < min || node->data > max)
        return 0;

    return is_bst(node->left, min, node->data - 1) && is_bst(node->right, node->data + 1, max);
}
#endif