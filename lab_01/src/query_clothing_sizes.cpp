// File: clothingSizes.cpp
// Name: Seiji Emery
// Compiler: gcc, apple llvm 9.0.0
//
// Purpose: interactive program to get clothing sizes
//
#include "clothing_sizes.h"
#include <iostream>
#include <i omanip>
using namespace std;

int main () {
    cout << "Displays clothing sizes. Press Ctrl+C to quit\n";
    double weight, height; int age;

    while (true) {
        cout << "Height? (inches) "; cin >> height;
        cout << "Weight? (pounds) "; cin >> weight;
        cout << "Age?    (years)  "; cin >> age;

        try {
            cout << "Hat size:    "; cout.flush();
            cout << setprecision(2) << fixed << getHatSize(weight, height) << '\n';

            cout << "Jacket size: "; cout.flush();
            cout << setprecision(2) << fixed << getJacketSize(weight, height, age) << '\n';

            cout << "Waist size: "; cout.flush();
            cout << setprecision(2) << fixed << getWaistSize(weight, age) << '\n';

            cout << '\n';

        } catch (std::runtime_error e) {
            cerr << '\n' << e.what() << '\n';
        }
    }
}
