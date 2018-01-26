// File: pig_game_driver.cpp
// Name: Seiji Emery
// Compiler: gcc, apple llvm 9.0.0
// Compiler flags: -std=c++14
// https://github.com/SeijiEmery/comp235/tree/master/assignment_01
//
// Purpose: implements an interactive, command-line game of pig with two
// players, one human and one scripted computer player.
//
#include <cstdlib>      // srand()
#include <ctime>        // time()
#include "pig_game.h"   // humanTurn(), computerTurn()


// Runs an interactive pig game with the following ruleset
// and two players (one human and one computer that rolls until reaching 20 points).
//
// The Pig ruleset:
// (1) players take turns in order
// (2) each turn, each player rolls a 6-sided die
// (3) if they roll a 1, they lose their turn
// (4) otherwise, they can choose to:
//     a) hold: their turn ends, and the sum of all roll made this turn is added to their score
//     b) roll: repeat from step (2)
// (5) the game ends when a player reaches a score >= 100
//
// For the full game and player decision making logic, see pig_game.cpp
//
void runPigGame () {
    int humanScore = 0;
    int computerScore = 0;

    // Seed rand() before playing.
    srand(time(nullptr));

    // Run game until one of the players wins.
    // All I/O is handled by the pig game interface, implemented in  pig_game.cpp
    while (1) {
        if ((humanScore    += humanTurn   (humanScore))    > 100) return;
        if ((computerScore += computerTurn(computerScore)) > 100) return;
    }
}

int main () {
    runPigGame();
    return 0;
}
