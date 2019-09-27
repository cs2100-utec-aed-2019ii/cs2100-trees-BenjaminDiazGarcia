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
class BinarySearchTree{
public:
    Node<T>* root;

    BinarySearchTree() {
        this->root = nullptr;
    }

    explicit BinarySearchTree(T value) {
        root = new Node(value);
    }

    void print(){

        if (this->get_root() == NULL) return;

        std::queue< Node<T>* > q;

        q.push(this->get_root());

        bool esta_en_el_nivel = false;

        int height = this->height();

        while (!q.empty()) {
            for (int i = 0; i < height; ++i){
                cout << "\t";
            }
            --height;

            int node_count = q.size();

            std::vector< Node<T>* > nodes_in_same_level(0);

            while (node_count > 0) {
                Node<T>* _node = q.front();

                nodes_in_same_level.push_back(_node);

                q.pop();
                if (_node->left != NULL)
                    q.push(_node->left);
                if (_node->right != NULL)
                    q.push(_node->right);
                --node_count;
            }

            int nodes_in_same_level_size = nodes_in_same_level.size();

            for (int i = 0; i < nodes_in_same_level_size; ++i) {
                if (i%2 == 0)
                    cout << "\t\t";
                else
                    for (int j = 0; j < height; j++)
                        cout << "\t";
                cout << nodes_in_same_level[i]->data << " ";
            }
            cout << endl;
        }
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
        //cout << "\nDelete: " << node->data;
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

    Node<T>* next_node_in_same_level(Node<T>* _root, Node<T>* node) {
        if (node == NULL)
            return node;

        std::queue< Node<T>* > q;

        q.push(_root);

        bool esta_en_el_nivel = false;

        while (!q.empty()) {
            int node_count = q.size();

            std::vector< Node<T>* > nodes_in_same_level(0);

            while (node_count > 0) {
                Node<T>* _node = q.front();

                nodes_in_same_level.push_back(_node);

                q.pop();
                if (_node->left != NULL)
                    q.push(_node->left);
                if (_node->right != NULL)
                    q.push(_node->right);
                --node_count;
            }

            int nodes_in_same_level_size = nodes_in_same_level.size();

            int indice;

            for (int i = 0; i < nodes_in_same_level_size; ++i) {
                if (node == nodes_in_same_level[i]) {
                    esta_en_el_nivel = true;
                    indice = i;
                    break;
                }
            }

            if (esta_en_el_nivel && indice != nodes_in_same_level_size-1 && nodes_in_same_level_size > 1) {
                return nodes_in_same_level[indice+1];
            }

        }
        return node;
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

    ~BinarySearchTree(){
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

template <typename T>
class BinaryTree {
public:
    Node<T>* root;

    BinaryTree() {
        this->root = nullptr;
    }

    explicit BinaryTree(T value) {
        root = new Node(value);
    }

    void print(){

        if (this->get_root() == NULL) return;

        std::queue< Node<T>* > q;

        q.push(this->get_root());

        bool esta_en_el_nivel = false;

        int height = this->height();

        while (!q.empty()) {
            for (int i = 0; i < height; ++i){
                cout << "\t";
            }
            --height;

            int node_count = q.size();

            std::vector< Node<T>* > nodes_in_same_level(0);

            while (node_count > 0) {
                Node<T>* _node = q.front();

                nodes_in_same_level.push_back(_node);

                q.pop();
                if (_node->left != NULL)
                    q.push(_node->left);
                if (_node->right != NULL)
                    q.push(_node->right);
                --node_count;
            }

            int nodes_in_same_level_size = nodes_in_same_level.size();

            for (int i = 0; i < nodes_in_same_level_size; ++i) {
                if (i%2 == 0)
                    cout << "\t\t";
                else
                    for (int j = 0; j < height; j++)
                        cout << "\t";
                cout << nodes_in_same_level[i]->data << " ";
            }
            cout << endl;
        }
    }

    bool isEmpty() {
        return root == nullptr;
    }

    void insert(T data) {
        if (this->get_root() == nullptr){
            root = new Node(data);
        } else {
            queue<Node<T> *> q;
            q.push(this->get_root());

            while (!q.empty()) {
                Node<T> *temp = q.front();
                q.pop();

                if (!temp->left) {
                    temp->left = new Node(data);
                    break;
                } else
                    q.push(temp->left);

                if (!temp->right) {
                    temp->right = new Node(data);
                    break;
                } else
                    q.push(temp->right);
            }
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
        //cout << "\nDelete: " << node->data;
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

    Node<T>* next_node_in_same_level(Node<T>* _root, Node<T>* node) {
        if (node == NULL)
            return node;

        std::queue< Node<T>* > q;

        q.push(_root);

        bool esta_en_el_nivel = false;

        while (!q.empty()) {
            int node_count = q.size();

            std::vector< Node<T>* > nodes_in_same_level(0);

            while (node_count > 0) {
                Node<T>* _node = q.front();

                nodes_in_same_level.push_back(_node);

                q.pop();
                if (_node->left != NULL)
                    q.push(_node->left);
                if (_node->right != NULL)
                    q.push(_node->right);
                --node_count;
            }

            int nodes_in_same_level_size = nodes_in_same_level.size();

            int indice;

            for (int i = 0; i < nodes_in_same_level_size; ++i) {
                if (node == nodes_in_same_level[i]) {
                    esta_en_el_nivel = true;
                    indice = i;
                    break;
                }
            }

            if (esta_en_el_nivel && indice != nodes_in_same_level_size-1 && nodes_in_same_level_size > 1) {
                return nodes_in_same_level[indice+1];
            }

        }
        return node;
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

    bool is_bst(Node<T> *node) {
        return(is_bst(node, INT_MIN, INT_MAX));
    }

    bool is_bst(Node<T> *node, int min, int max) {
        if (node == nullptr)
            return true;

        if (node->data < min || node->data > max)
            return false;

        return is_bst(node->left, min, node->data - 1) && is_bst(node->right, node->data + 1, max);
    }



    ~BinaryTree(){
        clear(root);
    }

};


#endif