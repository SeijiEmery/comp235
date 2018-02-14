// File: driver.cpp
// Programmer: Seiji Emery
// Compiler: Apple LLVM version 9.0.0 (clang-900.0.39.2)
// Compiler Flags: -std=c++11
//
// Purpose: Test operator overloading in the IntItem class.
//
#include "int_item.h"
#include <iostream>
using namespace std;

int main()
{
    IntItem myIntObj01{ 111 };
    IntItem myIntObj02{ 222 };
    
    myIntObj01 = myIntObj02 + myIntObj01;
    cout << "Object 1 = " << myIntObj01 << "  Object 2 = " << myIntObj02 << endl;

    if (myIntObj01 < myIntObj02)
        cout << "Object 1 is smaller.\n";
    else
        cout << "Object 2 is smaller.\n";

    return 0;
}
