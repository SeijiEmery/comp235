// File: int_item.cpp
// Programmer: Seiji Emery
// Compiler: Apple LLVM version 9.0.0 (clang-900.0.39.2)
// Compiler Flags: -std=c++11
//
// Purpose: implement operator overloading in int_item.h

#include "int_item.h"
#include <iostream>
using namespace std;

/***** MEMBER FUNCIONS *****/
bool IntItem::operator< (const IntItem& rhs) {
    if (this->m_intNum < rhs.m_intNum)
        return true;
    else
        return false;
}

/***** NON_MEMBER FUNCTIONS *****/
ostream& operator<< (ostream& out, const IntItem& rhs)
{
    cout << rhs.m_intNum;
    return out; //NOT *out
}
IntItem operator + (const IntItem& lhs, const IntItem& rhs) {
    IntItem temp;
    temp.m_intNum = lhs.m_intNum + rhs.m_intNum;
    return temp;
}