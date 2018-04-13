#include <iostream>
#include "bst.h"
using namespace std;

int main () {
    BST<int> myIntBST;
    myIntBST.insert(5);
    myIntBST.insert(3);
    myIntBST.insert(7);
    myIntBST.insert(1);
    myIntBST.insert(4);
    myIntBST.insert(6);
    myIntBST.insert(8);
    myIntBST.insert(2);
    cout << "TEST 1: Integer Tree...\n";
    myIntBST.inOrder();
    myIntBST.preOrder();
    myIntBST.postOrder();

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
