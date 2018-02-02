// File: odometer.h
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/lab_04
//
// Purpose:
//
#ifndef odometer_h
#define odometer_h

class Odometer {
public:
	Odometer() = default;
	Odometer(double mpg) : m_mpg(mpg) {}
	Odometer(const Odometer&) = default;
	Odometer& operator= (const Odometer&) = default;

	void reset();
	void setMPG(double efficiencey_in_mpg);
	void addMilesDriven(double miles);

	double getMilesDriven() const;
	double getGallonsUsed() const;
private:
	double m_mpg = 0.0;
	double m_miles_driven = 0.0;
};

#endif // odometer_h