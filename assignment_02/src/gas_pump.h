// File: gas_pump.h
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/assignment_02
//
// Purpose: Implements an OOP "gas pump" interface, to be used with
// gas_pump_driver.h
//
#ifndef gas_pump_h
#define gas_pump_h
#include <string>

// Implements a gas pump object with display and transactional
// state changing functions.
class GasPump {
public:
	// Default constructable, disabled assignment + copy
	GasPump ();
	GasPump (const GasPump&) = delete;
	GasPump& operator= (const GasPump&) = delete;
	virtual ~GasPump ();

	//
	// Display methods
	//

	// Displays the default screen
	// Preconditions (enforced with std::runtime_error):
	// 	no transaction started
	void displayWelcomeScreen () const;
	
	// Displays all available gas options (eg. regular, premium, etc)
	// Preconditions (enforced with std::runtime_error):
	//	transaction started, did not start pumping
	void displayGasOptions () const;

	// Displays the interactive pumping screen
	// Preconditions (enforced with std::runtime_error):
	//	transaction started, pumping started
	void displayPumpingScreen () const;

	// Displays the summary screen after pumping complete
	// Preconditions (enforced with std::runtime_error):
	// 	transaction started, pumping started then stopped
	void displaySummary () const;


	//
	// Transactional methods
	//

	// Begins a transaction
	// Preconditions (enforced with std::runtime_error):
	//	no transaction started / in progress
	void beginTransaction ();

	// Selects a numbered gas option (shown with displayGasOptions())
	// Preconditions (enforced with std::runtime_error):
	// 	- transaction started
	//  - no option has been selected
	//  - validOption(option) returns true
	void selectGasOption (int option);

	// Starts pumping gas
	// Preconditions (enforced with std::runtime_error):
	//  - transaction started
	//  - option selected
	//  - beginPumping() has not yet been called
	void beginPumping ();

	// Notifies the gas pump that a quantity of gas (in gallons) has been pumped
	// Preconditions (enforced with std::runtime_error):
	//  - transaction started
	//  - beginPumping() called
	//  - stopPumping() not called
	void updatePumped (double qtyGasPumped);

	// Stops pumping gas
	// Preconditions (enforced with std::runtime_error):
	// 	- 
	// Postconditions:
	//	- updatePumped() may not be called until the next transaction
	void stopPumping ();
	
	// Prints receipt to a file 'receipt.txt'
	// Preconditions:
	//  - active transaction:
	//	- transaction started and finished (gas pumped)
	//  - endTransaction() not yet called
	void printReceipt () const;

	// Ends / resets the current transaction, clearing all customer payment data etc

	// Preconditions:
	// - active transaction:
	// - transaction started and finished (gas pumped)
	// - endTransaction() not yet called
	// Postconditions:
	// - No transaction-related calls may be made until the next transaction
	//   is started with startTransaction()
	void endTransaction ();

	//
	// Internal (setup) + option validating methods
	//

	// Adds a pricing option.
	// name: type of gas / description (eg. Regular, Premium, Plus, Diesel)
	// pricePerGallon: price in $USD / gallon
	//
	// Note: each option added is assigned an option index, which is
	// shown on screen with displayGasOptions().
	void addOption (const std::string& name, double pricePerGallon);
	
	// Checks if an option (ie. index) is valid.
	// Note: options are 1-based, not 0-based.
	bool validOption (int option) const;
private:
	// Internal data hidden hidden w/ PIMPL idiom
	class Impl;
	Impl* impl;
};

#endif // gas_pump_h