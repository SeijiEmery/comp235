// testdriver.cpp
// (provided by instructor)
//
// Demo a string stream to extract user input
// and store TWO values, the numerator and
// denominator (even from a mixed number)
//
// ASSUMPTION 1: Acceptable user input format, 
//  no spaces between each token.
//  For examples:
//  1. a mixed number: 1+2/3
//  2. a simple fraction: 1/3
//  3. an integer value instead: 1234
// ASSUMPTION 2: Othere input formats are 
//  not handled in the code below
// ASSUMPTION 3:  A mixed number input will
//  converted and saved as two values, its
//  corresponding numerator and denominator

#include <sstream>
#include <iostream>
using namespace std;

int main()
{
    string str = "";
    char plusSign = ' ';
    char forwardSlash = ' ';

    cout << "Enter a fraction:\t";
    cin >> str;

    stringstream ss(str);

    int wholeNum = 0;
    int numerator = 0;
    int denominator = 1;

    ss >> wholeNum; //assumes mixed number
    if (!ss.eof())
    {
        if (ss.peek() == '/')
        { //Not mixed number

            numerator = wholeNum;
            wholeNum = 0;
            //Read off the forward slash
            ss >> forwardSlash;
            ss >> denominator;
        }
        else if (ss.peek() == '+')
        { //Must be a mixed number

            //Read off the plus sign
            ss >> plusSign;
            ss >> numerator;
            ss >> forwardSlash;
            ss >> denominator;
        }
    }

    //Assume you want to store two values only
    // -- the numerator and the denominator
    numerator = numerator + wholeNum * denominator;
    wholeNum = 0;
    cout << "Whole number = " << wholeNum << endl;
    cout << "Numerator = "   << numerator << endl;
    cout << "Denominator = " << denominator << endl;


    cout << endl;
    return 0;
}
