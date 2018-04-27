#include <list>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    /*** Test common functions of containers ***/
    //default constructor
    list<int> myList1;

    //Get an appropriate iterator for myList1
    list<int>::iterator iter1 = myList1.begin();

    //insert(pos, elem), 'pos' is an iterator
    myList1.insert(iter1, 111);
    myList1.insert(iter1, 222);
    myList1.insert(iter1, 333);

    //copy constructor
    list<int> myList2(myList1);

    //Get an appropriate iterator for myList1
    list<int>::iterator iter2 = myList2.begin();

    //erase(begin, end)
    myList2.erase(++iter2, myList2.end());
        
    //empty( )
    cout << boolalpha;
    if (!myList1.empty()) cout << "myList1.empty() returns: " << myList1.empty() << endl;
    //size( )
    if (!myList1.empty()) cout << "myList1.size() returns: " << myList1.size() << endl;
    if (!myList2.empty()) cout << "myList2.size() returns: " << myList2.size() << endl;
    //max_size( )
    if (!myList1.empty()) cout << "myList1.max_size() returns: " << myList1.max_size() << endl;

    //Question 1: Is MyList2 a shallow or deep copy of myList2? Why?
    
    //swap( )
    myList1.swap(myList2);

    if (!myList1.empty()) cout << "myList1.size() returns: " << myList1.size() << endl;
    cout << "Content of myList1..." << endl;
    iter1 = myList1.begin();
    while (iter1 != myList1.end())
    {
        cout << *iter1 << ' ';
        iter1++;
    }
    cout << endl;

    if (!myList2.empty()) cout << "myList2.size() returns: " << myList2.size() << endl;
    cout << "Content of myList2..." << endl;
    iter2 = myList2.begin();
    while (iter2 != myList2.end())
    {
        cout << *iter2 << ' ';
        iter2++;
    }

    cout << endl;

    //begin( ) and end ( )
    //for (list<int>::iterator forwardIter = myList2.begin(); forwardIter != myList2.end(); forwardIter++)
    cout << "Display list 2 forward..." << endl;
    for (auto myForwardIter = myList2.begin(); myForwardIter != myList2.end(); myForwardIter++)
        cout << *myForwardIter << ' ';
    cout << endl;

    //rbegin( ) and rend ( )
    cout << "Display list 2 in reverse..." << endl;
    for (auto myReverseIter = myList2.rbegin(); myReverseIter != myList2.rend(); myReverseIter++)
        cout << *myReverseIter << ' ';
    cout << endl;

    return 0;
}