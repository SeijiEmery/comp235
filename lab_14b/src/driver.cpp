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

    cout << "removing 1, 4, 8, 2\n";
    myIntBST.remove(1); myIntBST.inOrder();
    myIntBST.remove(4); myIntBST.inOrder();
    myIntBST.remove(8); myIntBST.inOrder();
    myIntBST.remove(2); myIntBST.inOrder();

    cout << "re-adding 2, 3, 4, 4, 5\n";
    myIntBST.remove(2); myIntBST.inOrder();
    myIntBST.remove(3); myIntBST.inOrder();
    myIntBST.remove(4); myIntBST.inOrder();
    myIntBST.remove(4); myIntBST.inOrder();
    myIntBST.remove(5); myIntBST.inOrder();

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
