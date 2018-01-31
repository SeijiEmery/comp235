// File: highscore.cpp
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/lab_03
//
// Purpose: implements highscore.h
//

#include <stdexcept>
#include <regex>
#include <climits> // INT_MIN
#include "highscore.h"

void getHighScore(std::istream& file, std::string& name, int& high_score) {
	if (!file.good()) { throw std::runtime_error("Invalid file"); }
	std::string line;

	high_score = INT_MIN;

	const static std::regex name_regex { "(\\w+)" };
	const static std::regex score_regex{ "(\\d+)" };
	std::string first_line, second_line;
	std::smatch name_match, score_match;

	while (getline(file, first_line) && std::regex_match(first_line, name_match, name_regex) &&
		getline(file, second_line) && std::regex_match(second_line, score_match, score_regex))
	{
		int score = atoi(score_match.str().c_str());
		if (score > high_score) {
			high_score = score;
			name = name_match.str();
		}
	}
}
