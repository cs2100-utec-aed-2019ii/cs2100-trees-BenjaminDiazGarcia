#include <iostream>
#include <vector>
#include "Tree.h"

using namespace std;

int main() {
    BinarySearchTree<int> tree1, tree2;
    ///Insertando valores
    tree1.insert(5);
    tree1.insert(3);
    tree1.insert(2);
    tree1.insert(4);
    tree1.insert(8);
    tree1.insert(7);
    tree1.insert(9);
    tree1.insert(1);

    tree2.insert(5);
    tree2.insert(3);
    tree2.insert(1);
    tree2.insert(2);


    ///Buscando ancestros
    int valor_en_el_arbol = 2;
    Node<int>* node = tree1.node_with_value(valor_en_el_arbol);
    vector<Node<int>*> vector = tree1.find_ancestors(node);
    cout << "Valores de los ancestros de " << valor_en_el_arbol << ": ";
    for (int i = 0; i < vector.size(); i++){
        cout << vector[i]->data << " ";
    }

    ///Inorder, preorder, postorder
    Node<int>* RootTree1 = tree1.get_root();
    cout << "\nInorder: ";
    tree1.inorder(RootTree1);
    cout << "\nPreorder: ";
    tree1.preorder(RootTree1);
    cout << "\nPostorder: ";
    tree1.postorder(RootTree1);

    ///Altura
    cout << "\nHeight: " << tree1.height() << endl;

    ///Check if two tree are identical
    cout << "tree1 == tree2: " << ((tree1.identical(tree1.get_root(), tree2.get_root())) ? ("True") : ("False")) << endl;

    ///Find next node in same level for given node in a binary tree
    auto node2 = tree1.node_with_value(4);
    auto node_next_to_4 = tree1.next_node_in_same_level(tree1.root, node2);
    cout << node_next_to_4->data << endl;

    ///Check if is height balanced
    cout << "Is height balanced?: " << ((tree1.is_height_balanced(tree1.get_root())) ? ("True") : ("False")) << endl;

    ///Print tree
    cout << "Print tree1: " << endl;
    tree1.print();

    ///Check if given binary tree is BST or not
    BinaryTree<int> bt1;
    bt1.insert(8);
    bt1.insert(4);bt1.insert(12);
    cout << "bt1 is a binary search tree?: " << ((bt1.is_bst(tree1.get_root())) ? ("True") : ("False")) << endl;
    return 0;
}