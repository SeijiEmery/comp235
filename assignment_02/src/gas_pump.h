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
	GasPump ();
	virtual ~GasPump ();

	void displayWelcomeScreen () const;
	void displayGasOptions () const;
	void displayPumpingScreen () const;
	void displaySummary () const;

	void beginTransaction ();
	void selectGasOption (int option);
	void beginPumping ();
	void updatePumped (double qtyGasPumped);
	void stopPumping ();
	void printReceipt () const;
	void endTransaction ();

	void addOption (const std::string& name, double pricePerGallon);
	bool validOption (int option) const;
private:
	class Impl;
	Impl* impl;
};

#endif // gas_pump_h