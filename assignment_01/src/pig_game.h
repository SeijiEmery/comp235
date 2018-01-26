// File: pig_game.h
// Name: Seiji Emery
// Compiler: gcc, apple llvm 9.0.0
// Compiler flags: -std=c++14
// https://github.com/SeijiEmery/comp235/tree/master/assignment_01
//
// Purpose: provides two functions that can be used to play an interactive,
// command-line version of the game of pig.
//

#ifndef pig_game_H
#define pig_game_H

// Runs an interactive human turn of the game pig.
//
// Preconditions:
// - score >= 0, score < 100.
// - If score >= 100, then the game has been won by this player.
// - This function calls rand() for RNG, so srand() must be called
//   when starting a new game, before calling this function.
// Returns:
// - The number of points gained in this turn (may be zero).
//
// Note: Calling this function will write out game messages to stdout,
// and use blocking input on stdin; there is currently no way to disable this.
// No additional game messages are required, other than perhaps "starting a game".
//
// Messages that may be shown when calling this function:
//  "Beginning turn for $(name), score $(score)"
//  "$(name) rolled $(roll), turn lost!"
//  "$(name) rolled $(roll) (score $(score) + $(points))"
//  "$(name) has won!"
//  "$(name) has gained $(points) points!"
//
int humanTurn (int score);


// Runs a non-interactive turn of the game pig with a CPU player
// that that follows the following rules:
//  (1) roll until accumulated points >= 20
//  (2) then hold
//
// Preconditions:
// - score >= 0, score < 100.
// - If score >= 100, then the game has been won by this player.
// - This function calls rand() for RNG, so srand() must be called
//   when starting a new game, before calling this function.
// Returns:
// - The number of points gained in this turn (may be zero).
//
// Note: Calling this function will write out game messages to stdout,
// and use blocking input on stdin; there is currently no way to disable this. 
// No additional game messages are required, other than perhaps "starting a game".
//
// Messages that may be shown when calling this function:
//  "Beginning turn for $(name), score $(score)"
//  "$(name) rolled $(roll), turn lost!"
//  "$(name) rolled $(roll) (score $(score) + $(points))"
//  "$(name) has won!"
//  "$(name) has gained $(points) points!"
//
int computerTurn (int score);

#endif // pig_game_H
