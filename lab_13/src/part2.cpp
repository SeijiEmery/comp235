#include <iostream>
using namespace std;

bool checkForWin (int guess, int answer)
{
    if (answer == guess)
    {
        cout << "You're right! You win!" << endl;
        return true;
    }
    else if (answer < guess)
        cout << "Your guess is too high." << endl;
    else
        cout << "your guess is too low." << endl;
    return false;
}
void play (Player &player1, Player &player2)
{
    int answer = 0, guess = 0;
    answer = rand( ) % 100;
    bool win = false;
    while (!win)
    {
        cout << "Player 1's turn to guess." << endl;
        guess = player1.getGuess( );
        win = checkForWin(guess, answer);
        if (win) return;

        cout << "Player 2's turn to guess." << endl;
        guess = player2.getGuess( );
        win = checkForWin(guess, answer);
    }
}
