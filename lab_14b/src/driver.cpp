#include <iostream>
// #include "bst.h"
#include "bst.hpp"
#include "utility/util/mem_bench.hpp"
#include "utility/util/lineio.hpp"
using namespace std;

template <typename T>
void insert (BST<T>& tree, const std::initializer_list<T>& values) {
    for (auto value : values) {
        info() << "inserting " << value << " into " << tree;
        tree.insert(value);
        info() << "\b => " << tree;
    }
}


int main () {
    BST<int> myIntBST;
    insert(myIntBST, { 5, 3, 7, 1, 4, 6, 8, 2 });
    cout << "TEST 1: Integer Tree...\n";
    myIntBST.inOrder();
    myIntBST.preOrder();
    myIntBST.postOrder();

    cout << "removing 1, 4, 8, 2\n";
    myIntBST.remove(1); myIntBST.inOrder();
    myIntBST.remove(4); myIntBST.inOrder();
    myIntBST.remove(8); myIntBST.inOrder();
    myIntBST.remove(5); myIntBST.inOrder();

    cout << "re-adding 2, 3, 4, 4, 5\n";
    myIntBST.insert(2); myIntBST.inOrder();
    myIntBST.insert(3); myIntBST.inOrder();
    myIntBST.insert(4); myIntBST.inOrder();
    myIntBST.insert(4); myIntBST.inOrder();
    myIntBST.insert(5); myIntBST.inOrder();

    BST<char> myCharBST;
    myCharBST.insert('E');
    myCharBST.insert('C');
    myCharBST.insert('G');
    myCharBST.insert('A');
    myCharBST.insert('D');
    myCharBST.insert('F');
    myCharBST.insert('H');
    myCharBST.insert('B');

    cout << "\nTEST 2: Character Tree...\n";
    myCharBST.inOrder();
    myCharBST.preOrder();
    myCharBST.postOrder();
}
