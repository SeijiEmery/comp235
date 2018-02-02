// File: odometer.cpp
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/lab_04
//
// Purpose: implements odometer.h
//
#include "odometer.h"

void Odometer::reset() {
	m_miles_driven = 0.0;
}
void Odometer::setMPG(double mpg) {
	m_mpg = mpg;
}
void Odometer::addMilesDriven(double miles) {
	m_miles_driven += miles;
}
double Odometer::getMilesDriven() const {
	return m_miles_driven;
}
double Odometer::getGallonsUsed() const {
	return m_miles_driven / m_mpg;
}
