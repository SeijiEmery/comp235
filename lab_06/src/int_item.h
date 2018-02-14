// File: int_item.h
// Programmer: Seiji Emery
// Compiler: Apple LLVM version 9.0.0 (clang-900.0.39.2)
// Compiler Flags: -std=c++11
//
//Purpose: demonstrate overloading of
//  Arihmetic operators
//  stream I/O operators
//  Comparison operators 

#ifndef __int_item_h__
#define __int_item_h__
#include <iostream>
 
//Wrapper class for simple data type: int
class IntItem
{
public:
    IntItem(int p_intNum = 0) : m_intNum(p_intNum) {}

    //Member functions
    bool operator< (const IntItem& rhs);  

    //Non-member functions
    friend std::ostream& operator<< (std::ostream& out, const IntItem& rhs);
    friend IntItem operator+ (const IntItem& lhs, const IntItem& rhs);

private:
    int m_intNum = 0;
};
#endif // __int_item_h__
