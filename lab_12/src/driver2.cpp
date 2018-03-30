#include "base.h"
#include "d1.h"
#include <iostream>
using namespace std;
using namespace my_wonderful_namespace;

int main()
{
    Base b1;
    cout << "b1 called into action...";
    b1.action();

    D1 objD1;
    cout << "objD1 called into action...";
    objD1.action();

    cout << "\nPart I: Public inheritance\n";
    //Using inherited getters from base class
    cout << "My inherited x value: " << objD1.getX() << endl;
    cout << "My inherited y value: " << objD1.getY() << endl;

    //Using derived class getters
    cout << "My own value: " << objD1.getD() << endl;
    cout << "... and all my integers add up to: " << objD1.addAll() << endl;

    //Part II
    D1 objD2;

    cout << "\nSHALLOW COPY in ....objD2 = objD1 \n";   /**********************************/
    /**  Fix a shallow-copy problem  **/
    objD2 = objD1;
    /**********************************/
    
    objD2.setY(1000); //add this setter in Base
    cout << "\nPart II: Shallow Copy\n";

    //... Same code from part 1 but shallow copy problem    

    //Using inherited getters from base class
    cout << "My inherited x value: " << objD1.getX() << endl;
    cout << "My inherited y value: " << objD1.getY() << endl;

    //Using derived class getters
    cout << "My own value: " << objD1.getD() << endl;
    cout << "... and all my integers add up to: " << objD1.addAll() << endl;

    return 0;
}
