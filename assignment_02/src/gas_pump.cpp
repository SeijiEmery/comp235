// File: gas_pump.cpp
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/assignment_02
//
// Purpose: implements gas_pump.h
//
#include "gas_pump.h"
#include <vector>
#include <utility>
#include <stdexcept>
#include <curses.h>
using namespace std;

class GasPump::Impl {
public:
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

void enforce (bool condition, const char* msg) {
    if (!condition) {
        throw runtime_error(msg);
    }
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
void GasPump::printReceipt () const {
    enforce(impl->inTransaction, "No transaction!");
    enforce(!impl->isPumping, "Cannot print reciept while pumping!");

    // Print stuff to a file reciept.txt
    // Not implemented, whatever
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
    
    clear();
    printw("Welcome to gas-mart\n");
    printw("Press any key to continue\n");
    refresh();
}
void GasPump::displayGasOptions () const {
    enforce(impl->inTransaction, "Transaction not started!");
    enforce(!impl->isPumping && (impl->gasPumped == 0), "Cannot display options once gas pumping started");

    clear();
    printw("Choose an option:\n");
    for (auto i = 0; i < impl->gasOptions.size(); ++i) {
        printw("%d: %s $%0.2lf\n", i + 1,
            get<0>(impl->gasOptions[i]).c_str(),
            get<1>(impl->gasOptions[i]));
    }
    refresh();
}
void GasPump::displayPumpingScreen () const {
    enforce(impl->inTransaction, "Transaction not started!");
    enforce(impl->isPumping, "Must be pumping!");

    clear();
    printw("%s\n", get<0>(impl->gasOptions[impl->optionSelected - 1]).c_str());
    printw("Gallons: %.2lf\n ", impl->gasPumped);
    printw("Charge: $%.2lf\n", impl->gasPumped * get<1>(impl->gasOptions[impl->optionSelected - 1]));
    printw("Press esc to stop pumping\n");
    refresh();
}
void GasPump::displaySummary () const {
    enforce(impl->inTransaction, "Transaction not started!");
    enforce(!impl->isPumping, "Must have finished pumping!");

    clear();
    printw("Finished pumping\n");
    printw("Gallons: %.2lf\n");
    printw("Charge: $%.2lf\n");
    refresh();
}
