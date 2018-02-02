// File: odometer_driver.h
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/lab_04
//
// Purpose:
//
#include "odometer.h"
#include <iostream>
using namespace std;

int main() {
	Odometer myOdometer;
	//Trip 1
	myOdometer.setMPG(20.0);
	myOdometer.addMilesDriven(0);
	cout << "Trip 1: 20 mpg, 0 mile travelled..." << endl;
	cout << "Gallons of fuel used:\t" << myOdometer.getGallonsUsed() << endl;
	
	//Trip 2
	myOdometer.setMPG(25.5);
	myOdometer.addMilesDriven(102);
	cout << "\nTrip 2: 25.5 mpg, 102 miles travelled..." << endl;
	cout << "Gallons of fuel used:\t" << myOdometer.getGallonsUsed() << endl;
	
	//Trip 3
	myOdometer.setMPG(31.5);
	myOdometer.addMilesDriven(221);
	cout << "\nTrip 3: 31.5 mpg, 221 miles travelled..." << endl;
	cout << "Gallons of fuel used:\t" << myOdometer.getGallonsUsed() << endl;

	getchar();
	return 0;
}