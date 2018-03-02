#include <iostream>
#include "myvector.h"
#include <string>
using namespace std;

int main()
{
    MyVector vec01;

    cout << "***** Testing function, size *****\n";
    cout << "Current size of my vector =\t" << vec01.size() << endl;

    cout << "\n***** Testing function, addEntry *****\n";
    cout << "Adding three elements...\n";
    vec01.addEntry("Iron");
    vec01.addEntry("Copper");
    vec01.addEntry("Zinc");

    cout << "Confirming updated size =\t" << vec01.size() << endl;

    cout << "\n***** Testing function, getEntry *****\n";
    cout << "Contents of my vector ==>\t";
    for (int i = 0; i < vec01.size(); i++)
        cout << vec01.getEntry(i) << ' ';
    cout << endl;

    cout << "\n***** Testing Out-Of_bound from getEntry *****\n";
    for (int i = 0; i < 5; i++)
    {
        string returnedString = vec01.getEntry(i);
        if (returnedString != "")
            cout << "Index " << i << " = " << returnedString << endl;
        else
            cout << "Index " << i << " is out of bound\n";;
    }

    cout << "\n***** Testing item-not-found checking in deleteEntry *****\n";
    cout << "Attempt to delete non-existing metals: Potassium and Sulphur...\n";
    if (!vec01.deleteEntry("Potassium") && !vec01.deleteEntry("Sulphur"))
        cout << "They are not found in the vector!" << endl; 

    cout << "\n***** Testing deleteEntry *****\n";
    vec01.deleteEntry("Zinc");
    cout << "Size after deleting zinc = " << vec01.size() << endl;
    cout << "Confirm new contents ==>\t";  
    for (int i = 0; i < vec01.size(); i++)
        cout << vec01.getEntry(i) << ' ';
    vec01.deleteEntry("Iron");
    cout << "\nSize after deleting Iron = " << vec01.size() << endl;
    cout << "Confirm new contents ==>\t";
    for (int i = 0; i < vec01.size(); i++)
        cout << vec01.getEntry(i) << ' ';
    vec01.deleteEntry("Copper");
    cout << "\nSize after deleting Copper = " << vec01.size() << endl;
    cout << "Confirm new contents ==>\t";
    for (int i = 0; i < vec01.size(); i++)
        cout << vec01.getEntry(i) << ' ';
 

    cout << endl;
    return 0;
}