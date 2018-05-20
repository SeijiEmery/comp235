#include <iostream>
using namespace std;

class Glob
{
public:
    typedef Glob This;
    Glob () : Glob(111) {}
    Glob (int value) : dataPtr(new int(value)) {}
    Glob (const Glob& other) : dataPtr(new int(*other.dataPtr)) {
        std::cout << "Copy constructor called!\n";
    }
    Glob (Glob&& other) {
        std::cout << "Move constructor called!\n";
        std::swap(dataPtr, other.dataPtr);
    }
    ~Glob () {
        if (dataPtr) {
            delete dataPtr;
        }
    }
    Glob operator+ (const Glob& other) {
        return { *dataPtr + *other.dataPtr };
    }
    This& operator= (const This& other) {
        std::cout << "Assignment operator called!\n";
        return *dataPtr = *other.dataPtr, *this;
    }
    This& operator= (This&& other) {
        std::cout << "Move assignment called!\n";
        return std::swap(dataPtr, other.dataPtr), *this;
    }
private:
    int *dataPtr;                              
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

    // move assignment
    globbie4 = std::move(globbie1);
    std::swap(globbie1, globbie3);

    return 0;
}
