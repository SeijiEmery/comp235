// File: gas_pump.h
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/assignment_02
//
// Purpose:
//
#ifndef gas_pump_h
#define gas_pump_h

class GasPump {
public:
	void displayAmountDispensed() const;
	void displayAmountCharged() const;
	void displayCostPerGallon() const;
	
	void startTransaction();
	void endTransaction();
	void display


	double amountDispensed() const;


private:
	class Impl;
	Impl* impl;
};

#endif // gas_pump_h