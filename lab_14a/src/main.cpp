#include "linked_list.h" /*** use your header file name ***/
#include <iostream>
#include <string>
using namespace std;
int main()
{
    List<int> myList1;
    myList1.push_front(111);
    myList1.push_back(222);
    myList1.push_front(1);
    myList1.push_back(999);
    cout << "Display list # 1 forward...\n";
    myList1.displayListForward();
    cout << "\nDisplay list # 1 backward...\n"; 
    myList1.displayListBackward();
    cout << "\nPopping one item from front and one from back...\n";
    myList1.pop_front();
    myList1.pop_back();
    cout << "Display list # 1 forward...\n";
    myList1.displayListForward();
    cout << "\nDisplay list # 1 backward...\n";
    myList1.displayListBackward();
    cout << "\nPopping one item from front and one from back...\n";
    myList1.pop_front();
    myList1.pop_back();
    cout << "Display list # 1 forward...\n";
    myList1.displayListForward();
    cout << "\nDisplay list # 1 backward...\n";
    myList1.displayListBackward();

    cout << "***********************************************";

    List<string> myList2;
    myList2.push_back("111");
    myList2.push_front("222");
    myList2.push_back("1");
    myList2.push_front("999");
    cout << "\n\nDisplay list # 2 forward...\n";
    myList2.displayListForward();
    cout << "\nDisplay list # 2 backward...\n";
    myList2.displayListBackward();
    cout << "\nAdd two more 111s into the list...\n";
    myList2.push_front("111");
    myList2.push_back("111");
    cout << "\n\nDisplay list # 2 forward...\n";
    myList2.displayListForward();
    cout << "\nDisplay list # 2 backward...\n";
    myList2.displayListBackward();
    cout << "\nRemove ALL 111 from the list...\n";
    myList2.removeAll("111");
    cout << "\n\nDisplay list # 2 forward...\n";
    myList2.displayListForward();
    cout << "\nDisplay list # 2 backward...\n";
    myList2.displayListBackward();

    return 0;
};