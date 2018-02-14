/****************************/
/***   Implementatoions   ***/
/****************************/
//intItemH.cpp
//Miakhau, Chia
//2/16/2017
//MS Visual C++ 2017
//File needed: intItemH.h
//
//Purpose: To implement operator overloading in IntItem class
//  from the intItem.h header file

#include "intItemH.h"
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