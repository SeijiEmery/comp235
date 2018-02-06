// File: gas_pump.cpp
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/assignment_02
//
// Purpose: implements gas_pump.h
//
#include "gas_pump.h"

class GasPump::Impl {
    bool   inTransaction  = false;
    bool   isPumping      = false;
    double gasPumped      = 0;
    int    optionSelected = -1;
    vector<tuple<string,double>> gasOptions;
};

GasPump::GasPump ()
    : impl(new GasPump::Impl()) 
{}
GasPump::~GasPump () {
    delete impl;
}

//
// Gas pump state logic
//

void GasPump::beginTransaction () {
    enforce(!impl->inTransaction, "Invalid state: transaction already started");
    impl->inTransaction = true;
    impl->isPumping = false;
    impl->gasPumped = 0;
    impl->optionSelected = -1;
}
void GasPump::selectGasOption (int option) {
    enforce(impl->inTransaction, "Transaction not started!");
    enforce(validOption(option), "Invalid option!");
    enforce(impl->optionSelected < 0, "Option already selected!");
    impl->optionSelected = option;
}
void GasPump::beginPumping () {
    enforce(impl->inTransaction, "Transaction not started!");
    enforce(validOption(impl->optionSelected), "No option selected!");
    enforce(!impl->isPumping, "Already pumping!");
    impl->isPumping = true;
}
void GasPump::updatePumped (double qtyGasPumped) {
    enforce(impl->isPumping, "Should not be pumping!");
    impl->gasPumped += qtyGasPumped;
}
void GasPump::stopPumping () {
    enforce(impl->inTransaction, "Transaction not started!");
    enforce(impl->isPumping, "Did not start pumping!");
    impl->isPumping = false;
}
void GasPump::printReceipt () {
    enfore(impl->inTransaction, "No transaction!");
    enforce(!impl->isPumping, "Cannot print reciept while pumping!");

    // Print stuff to a file reciept.txt
}
void GasPump::endTransaction () {
    enforce(impl->inTransaction, "Transaction not started!");
    impl->inTransaction = false;
}

//
// Check option(s), set option
//

// Options are 1-based indexes into the gasOptions array
bool GasPump::validOption (int option) const {
    return option >= 1 && option < impl->gasOptions.size();
}

void GasPump::addOption (const std::string& name, double pricePerGallon) {
    impl->gasOptions.emplace_back(name, pricePerGallon);
}

//
// Displays
//

void GasPump::displayWelcomeScreen () const {
    enforce(!impl->inTransaction, "Transaction started!");

    // display welcome screen...
}
void GasPump::displayGasOptions () const {
    enforce(impl->inTransaction, "Transaction not started!");
    enforce(!impl->isPumping && (impl->gasPumped == 0), "Cannot display options once gas pumping started");

    // display gas options... (as 1-based indexes)
}
void GasPump::displayPumpingScreen () const {
    enforce(impl->inTransaction, "Transaction not started!");
    enforce(impl->isPumping, "Must be pumping!");

    // display gas pumping info...
}
void GasPump::displaySummary () cosnt {
    enforce(impl->inTransaction, "Transaction not started!");
    enforce(!impl->isPumping, "Must have finished pumping!");

    // display gas pumping summary...
}
