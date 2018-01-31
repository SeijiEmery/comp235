// File: highscore.h
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/lab_03
//
// Purpose: 
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib> // exit()
using namespace std;

#include "highscore.h"

void loadFromFile(const char* path) {
	std::ifstream file{ path };
	if (!file.good()) {
		std::cerr << "Could not load '" << path << "'\n";
		getchar();
		exit(-1);
	}
	string name; int score;
	getHighScore(file, name, score);
	std::cout << "Got high score: " << name << ", " << score << '\n';
	getchar();

}
void loadFromMockData() {
	std::stringstream ss;
	ss << "Ronaldo\n10400\nDidier\n9800\nPele\n12300\nKaka\n8400\nCristiano\n";

	string name; int score;
	getHighScore(ss, name, score);
	std::cout << "Got high score: " << name << ", " << score << '\n';
	getchar();

}

int main() {
	//loadFromFile("scores.txt");
	loadFromMockData();
	return 0;
}