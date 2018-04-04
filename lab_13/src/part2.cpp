#include <iostream>
using namespace std;

enum class Comparison { EQUAL = 0, GREATER = 1, LESSER = -1 };

class IPlayer {
public:
    virtual const char* name () const = 0;
    virtual int  getGuess    () = 0;
    virtual void reportGuess (int guess, Comparison cmp) {}
};

bool checkForWin (IPlayer& player, IPlayer& secondPlayer, int playerId, int answer) {
    int guess = player.getGuess();
    cout << player.name() << " player " << playerId << " guessed " << guess << ", ";
    if (guess == answer) {
        cout << player.name() << " player " << playerId << " has won!\n";
        return true;
    } else {
        cout << "guess was " << (guess > answer ? "too high" : "too low") << '\n';
        player.reportGuess(guess, guess > answer ? Comparison::LESSER : Comparison::GREATER);
        secondPlayer.reportGuess(guess, guess > answer ? Comparison::LESSER : Comparison::GREATER);
        return false;
    }
}

void play (IPlayer &player1, IPlayer &player2) {
    cout << "\nStarting game with players " << player1.name() << ", " << player2.name() << "\n";
    int answer = 0, guess = 0;
    answer = rand() % 100;
    while (!checkForWin(player1, player2, 1, answer) && !checkForWin(player2, player1, 2, answer));
}
template <typename P1, typename P2>
void playWith () {
    P1 player1;
    P2 player2;
    play(static_cast<IPlayer&>(player1), static_cast<IPlayer&>(player2));
}


class RandomPlayer : public IPlayer {
public:
    const char* name () const override { return "Random"; }
    int getGuess () override { return rand() % 100; }
    void reportGuess (int guess, Comparison cmp) override {}
};

class HumanPlayer : public IPlayer {
public:
    const char* name () const override { return "Human"; }
    int getGuess () override {
        cout << "guess = ";
        int guess = 0;
        cin >> guess;
        return guess;
    }
};

class ComputerPlayer : public IPlayer {
    int lowBound = 0, upBound = 100;
public:
    const char* name () const override { return "Computer"; }
    int getGuess () override { return rand() % (upBound - lowBound) + lowBound; }
    void reportGuess (int guess, Comparison cmp) override {
        switch (cmp) {
            case Comparison::GREATER: lowBound = guess + 1; break;
            case Comparison::LESSER:  upBound  = guess - 1; break;
            default:;
        }
    }
};


int main () {
    srand(time(nullptr));
    playWith<ComputerPlayer, HumanPlayer>();

    playWith<HumanPlayer, HumanPlayer>();
    playWith<HumanPlayer, RandomPlayer>();
    playWith<RandomPlayer, RandomPlayer>();
    return 0;
}
