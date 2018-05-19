#include <iostream>
using namespace std;

class Glob
{
public:
    Glob() { *dataPtr = 111; }
    Glob(const Glob& lvalueP)
    {
        cout << "Regular constructor is called!\n";
        *dataPtr = 111;
        //...
    }

    Glob(Glob&& rvalueP)
    {
        cout << "Move constructor is called!\n";
        dataPtr = rvalueP.dataPtr; //Steal address
        rvalueP.dataPtr = nullptr; //remove ownership
        //...
    }

    Glob operator+ (const Glob& p_glob)     //Coded to produce
                            // a rvalue
    {
        Glob temp;
        *(temp.dataPtr) = *dataPtr + *(p_glob.dataPtr);
        return temp;
    }

    //0. Run this code and observe the outputs from the driver given below
    //I. Overload the assignment operator, using a regular lvalue reference parameter
    //II. Overload the assignment operator, using rvalue reference paramter
    //III. Then in the driver, demonstrate assignments in the similar way 

private:
    int *dataPtr = new int;                              
};

int main()
{
    Glob globbie1;
    Glob globbie2;
    Glob globbie3(globbie1); //Regular constructor 
    Glob globbie4(globbie1 + globbie2); //Move constructor

    Glob globbie5;
    globbie5 = globbie1;
    Glob globbie6;
    globbie6 = globbie1 + globbie2;

    return 0;
}
