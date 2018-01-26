// File: pig_game.cpp
// Name: Seiji Emery
// Compiler: gcc, apple llvm 9.0.0
// Compiler flags: -std=c++14
// https://github.com/SeijiEmery/comp235/tree/master/assignment_01
//
// Purpose: implements two functions that can be used to play an interactive,
// command-line version of the game of pig, as well as all internal game logic
// and a decision making framework that could be used to add new types of players.
//
#include <cstdlib>      // rand()
#include <cstdio>       // printf(), getchar()
#include "pig_game.h"   // implements humanPlayer(), computerPlayer()


// Describes the two actions a player can make in a game of pig.
enum class PlayerAction {
    ROLL, HOLD
};

// A computer player instance. Rolls until reaching 20 points.
struct ComputerPlayer {
    static const char* name () { return "CPU"; }
    static PlayerAction chooseAction (int points) {
        return points < 20 ?
            PlayerAction::ROLL :
            PlayerAction::HOLD;
    }
};

// A human player instance. Asks (using stdin) for what action to take:
// typing 'r' (or any character) => roll, 'h' => hold
struct HumanPlayer {
    static const char* name () { return "Player"; }
    static PlayerAction chooseAction (int points) {
        printf("roll (r) or hold (h)? ");
        char choice = getchar(); while (choice != '\n' && getchar() != '\n');
        return choice != 'h' ? 
            PlayerAction::ROLL : 
            PlayerAction::HOLD;
    }
};

// Returns the result of rolling a 6-sided die
// Preconditions:
//  srand() called sometime previously with a random or fixed seed value
// Postconditions:
//  return value is always on range [1, 6]
static int rolld6 () { 
    return rand() % 6 + 1; 
}

// Runs a turn for a player, executing all I/O for displaying game actions
// and following the game logic of pig.
//
// Player must be a type matching the static interface:
//      static const char* name ();
//      static PlayerAction chooseAction (int points);
//
// Function is declared as static so it has file-only scope (ie. not a publicly linkable symbol).
//
template <typename Player>
static int runPigTurn (int score) {
    printf("Beginning turn for %s, score %d\n", Player::name(), score);
    int accum = 0;
    while (1) {
        int roll = rolld6();
        if (roll == 1) {
            printf("%s rolled %d, turn lost!\n", Player::name(), roll);
            return 0;
        } else {
            printf("%s rolled %d (score %d + %d)\n", Player::name(), roll, score, accum += roll);
            if (score + accum >= 100) {
                printf("%s has won!\n", Player::name());
                return accum;
            }
            if (Player::chooseAction(accum) == PlayerAction::HOLD) {
                printf("%s gained %d points!\n", Player::name(), accum);
                return accum;
            }
        }
    }    
}

// Implements the interface in pig_game.h
int humanTurn (int score) {
    return runPigTurn<HumanPlayer>(score);
}

// Implements the interface in pig_game.h
int computerTurn (int score) {
    return runPigTurn<ComputerPlayer>(score);
}
