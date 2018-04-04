#include <iostream>
using namespace std;

class LivingThing
{
public:
    LivingThing() {}
    LivingThing(int p) { legs = p; }
    int legs;
    virtual void move() { cout << "A living thing is moving! "; };
};

class Human : public LivingThing
{
public:
    //TO DO: declare a no-arg constructor, it should call the base class
    //  constructor using the initializer 2 for number of legs
    
    //TO DO: Override the 'move' function to display "Human is walking!"    
};

class Tiger : public LivingThing
{
public:
    //TO DO: declare a no-arg constructor, it should call the base class
    //  constructor using the initializer 4 for number of legs
    
    //TO DO: Override the 'move' function to display "Tiger is prowling!"
    
};

int main()
{
    cout << "Part I. Static Bindings\n";
    cout << "=======================\n";
    //Declare an array of LivingThing base type, of size 4  
    //Randomly populate the array with a mix of humans and tigers,
    //simply use an initializer list.
    //Use a loop, call the "move" virtual function from the base class
    //and display the ‘legs’ field of each object.

    cout << "Part II. Dynamic Bindings\n";
    cout << "=========================\n";
    //Declare an array of pointers of LivingThing base type, of size 4
    //Randomly populate the array with a mix of pointers to humans and tigers
    //Use a loop, call the "move" function with each LivingThing object in the
//  array and display the ‘legs’ field of each object.

    return 0;
}
