#include <iostream>
#include "Tree.h"

using namespace std;

int main() {
    Tree<int> t;
    t.insert(5);
    t.insert(3);
    t.insert(7);
    t.insert(9);
    t.insert(6);
    t.insert(8);
    t.erase(8);
    t.print();
    cout << "Height: " << t.height() << endl;
    return 0;
}