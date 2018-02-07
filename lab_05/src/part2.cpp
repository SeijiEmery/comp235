#include "vehicle.h"
#include <iostream>
using namespace std;

int main () {
    Vehicle v1;
    Vehicle v2(2);
    Vehicle v3(3);

    cout << "There are " << Vehicle::howManyVehicles() << " vehicles" << endl;

    cout << endl;
    return 0;
}