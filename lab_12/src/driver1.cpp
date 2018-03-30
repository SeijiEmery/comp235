#include "base.h"
#include "d1.h"
#include <iostream>
using namespace std;
using namespace my_wonderful_namespace;

int main()
{
    D1 objD1;
    objD1.action();

    //Using inherited getters from base class
    cout << "My inherited x value: " << objD1.getX() << endl;
    cout << "My inherited y value: " << objD1.getY() << endl;

    //Using derived class getters
    cout << "My own d value: " << objD1.getD() << endl;
    cout << "... and all my integers add up to: " << objD1.addAll() << endl;

    return 0;
}
