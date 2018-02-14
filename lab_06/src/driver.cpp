/******************/
/***   Driver   ***/
/******************/
//driver.cpp
//Miakhau, Chia
//2/16/2017
//MS Visual C++ 2017
//File needed: intItem.h and intItem.cpp
//
//Purpose: To test operator overloaded in IntItem class
//  from the intItem.h header file
#include "intItemH.h"
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
