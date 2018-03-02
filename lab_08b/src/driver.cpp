/*** Driver ***/
#include "list.h"
#include <iostream>
using namespace std;

int main()
{
    List obj1(5);
    obj1.addItem(33);
    obj1.addItem(23);
    obj1.addItem(93);
    obj1.addItem(43);
    obj1.addItem(83);

    List obj2(obj1);
    obj1.decrementAll();

    List obj3;
    obj3 = obj1;
    obj3.decrementAll();

    cout << "Object 1:\t";
    obj1.printList();
    cout << endl;
    cout << "Object 2:\t";
    obj2.printList();
    cout << endl;
    cout << "Object 3:\t";
    obj3.printList();

    cout << endl;
    return 0;
}