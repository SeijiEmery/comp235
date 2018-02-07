// File: gas_pump_driver.h
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/assignment_02
//
// Purpose: Implements a gas pump program with:
// - a GasPump object
// - an interactive commandline interface via curses.h
//
#include "gas_pump.h"
#include <curses.h>
#include <unistd.h>
#include <ctime>
using namespace std;

const static char ESC = 27;
const static int CLOCK_TICK_RATE = 30;

void setupDisplay () {
    initscr();
    raw();
    cbreak();
    noecho();
    timeout(CLOCK_TICK_RATE);
}
int main() {
    GasPump pump;

    // Setup gas prices (hardcoded)
    pump.addOption("Regular", 3.589);
    pump.addOption("Plus   ", 3.709);
    pump.addOption("Diesel ",  3.959);

    // Program config: pump rate + display rate hardcoded
    double pumpRate    = 1.0;      // Gal / sec

    setupDisplay();

    // Note: gas pump state is modeled as a FSM for obvious reasons.
    //
    // While I started with an enum class + nested switch statements, I
    // quickly realized that it made much more sense to just use goto
    // (one of the few cases where goto is appropriate)
    //
idle:
    pump.displayWelcomeScreen();
    while (true) {
        switch (getch()) {
            case ERR:           continue;
            case 'q': case 'Q': goto quit;
            case ESC:           goto ask_quit;
            default:            goto select_option;
        }
    }
select_option:
    pump.beginTransaction();
    pump.displayGasOptions();
    while (true) {
        int option = getch();
        switch (option) {
            case ERR: continue;
            case ESC: pump.endTransaction(); goto idle;
            default: {
                if (pump.validOption(option - '0')) {
                    pump.selectGasOption(option - '0');
                    goto start_pumping;
                }
            }
        }
    }
start_pumping: {
    pump.beginPumping();
    clock_t t = clock(), t2 = t;
    double dt = 0;

    while (true) {
        pump.displayPumpingScreen();
        t2 = clock();
        dt = static_cast<double>(t2 - t) / static_cast<double>(CLOCKS_PER_SEC) * CLOCK_TICK_RATE;
        printw("%d, %lf\n", t2 - t, dt);
        t = t2;
        switch (getch()) {
            case ESC: case ' ': goto stop_pumping;
            default:;
        }
         
        pump.updatePumped(pumpRate * dt);
    }
}
stop_pumping:
    pump.stopPumping();
    pump.displaySummary();
    printw("Would you like a reciept? y / n\n");
    while (1) {
        switch (getch()) {
            case 'y': case 'Y': case ' ': goto print_receipt;
            case 'n': case 'N': case ESC: goto finish_transaction;
            default:;
        }
    }
print_receipt:
    pump.printReceipt();
finish_transaction:
    pump.endTransaction();
    goto idle;
ask_quit:
    clear();
    printw("Are you sure you want to quit? (y / n)\n");
    refresh();
    while (1) {
        switch (getch()) {
            case 'y': case 'Y': case ' ': goto quit;
            case 'n': case 'N': case ESC: goto idle;
        }
    }
quit:
    printw("Exiting\n");
    endwin();
	return 0;
}