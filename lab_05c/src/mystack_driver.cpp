
#include <iostream>
#include "mystack.h"
using namespace std;

int main() {
    //Stk1: empty to begin with
    MyStack stk1;
    cout << "1. No initializer list used to instantiate stack 1,\n";
    cout << " pushing items 1...5 onto stack...\n";
    for (int i = 0; i < stk1.CAPACITY; i++)
        stk1.push(i + 1);

    cout << "\nTesting top() and pop(), until stack is empty:\t";
    for (int i = 0; i < MyStack::CAPACITY; i++) {
        cout << stk1.top() << ' ';stk1.pop();
    }

    //Stk2 and stk3: intiailized with different number of initializers
    cout << "\n\n2. Stack 2 is constructed with C++11 initializer list...\n";
    MyStack stk2{ 1, 2, 3 };

    cout << "Testing top() and pop(), content of stack 2:\t";
    for (int i = 0; i < stk2.getSize(); i++){
        cout << stk2.top() << ' ';
        stk2.pop();
    }

    cout << "\n\n3. stack 3: intiailized with too many initializers.... " << endl;
    MyStack stk3{ 111, 222, 333, 4444, 555, 666, 777, 888, 999 };
    cout << endl;
    return 0;
}
