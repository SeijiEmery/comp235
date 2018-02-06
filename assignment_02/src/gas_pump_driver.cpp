// File: gas_pump_driver.h
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/assignment_02
//
// Purpose:
//
#include "gas_pump.h"
#include <iostream>
using namespace std;

const static char ESC = 27;

int main() {
    GasPump pump;

    // Setup gas prices (hardcoded)
    pump.addOption("Regular", 3.589);
    pump.addOption("Plus",    3.709);
    pump.addOption("Diesel",  3.959);

    // Program config: pump rate + display rate hardcoded
    double pumpRate    = 1.0;      // Gal / sec
    double ticksPerSec = 10;

    //
    // Note: I started writing this using an enum class + nested switch statements,
    // then realized it made much more sense to use goto and blocking input.
    //
    // Pump state is modeled as a FSM for obvious reasons; the gas pump API
    // arose naturally / logically b/c of this
    //
    setupDisplay();
idle:
    clearScreen();
    pump.displayWelcomeScreen();
    printf("Press any key to continue, esc to exit, q or Q to quit\n");
    while (true) {
        switch (getch()) {
            case 0: break;
            case 'q': case 'Q': goto quit;
            case ESC:           goto ask_quit;
            default:            goto select_option;
        }
    }
select_option:
    pump.beginTransaction();
    clearScreen();
    pump.displayGasOptions();
    printf("Press [#option] to choose option, esc to cancel\n");
    while (true) {
        int option = getch();
        switch (getch()) {
            case 0: break;
            case ESC: goto idle;
            default: {
                if (pump.validOption(option)) {
                    pump.selectGasOption(option);
                    goto start_pumping;
                }
            }
        }
    }
start_pumping:
    pump.beginPumping();
    while (true) {
        clearScreen();
        pump.displayPumpingScreen();
        printf("Press space to finish");
        switch (getch()) {
            case ' ': goto stop_pumping;
            default:
        }
        pump.updatePumped(pumpRate / ticksPerSec);
        sleep( 1.0 / ticksPerSec );
    }
stop_pumping:
    pump.stopPumping();
    clearScreen();
    pump.displaySummary();
    printf("Print reciept? y / n");
    while (1) {
        switch (getch()) {
            case 'y': case 'Y': case ' ': goto print_receipt;
            case 'n': case 'N': case ESC: goto finish_transaction;
            default:
        }
    }
display_reciept:
    pump.printReceipt();
finish_transaction:
    pump.endTransaction();
    goto idle;
ask_quit:
    clearScreen();
    printf("Are you sure you want to quit? (y / n)");
    while (1) {
        switch (getch()) {
            case 'y': case 'Y': case ' ': goto quit;
            case 'n': case 'N': case ESC: goto idle;
        }
    }
quit:
	return 0;
}