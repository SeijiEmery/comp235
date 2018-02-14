/******************/
/***   Header   ***/
/******************/
//intItemH.h
//Miakhau, Chia
//2/16/2017
//MS Visual C++ 2017
//
//Purpose, to overload:
//  Arihmetic operators
//  stream I/O operators
//  Comparison operators 

#ifndef MCHIA_INTITEM
#define MCHIA_INTITEM
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
#endif
