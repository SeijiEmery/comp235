// File: treadmill_calculator_driver.cpp
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/lab_03
//
// Purpose: Implements an interactive commandline program to convert treadmill
// speed values into MPH.
//
#include <iostream>
#include <regex>
#include <stdexcept>
using namespace std;

#include "treadmill_calculator.h"

int main() {
	cout << "Converts treadmill values to MPH. Press Ctrl+C to quit\n";
	cout << "Enter <int minutes>:<int seconds> or <double kph>\n";

	std::regex min_secs_regex { "(\\d+)\\:(\\d+)" };
	std::regex kph_regex{ "(\\d+\\.?\\d*)" };
	std::regex quit_regex{ "quit" };
	std::string line;
	std::smatch match;

	while (true) {
		cout << ">> "; 
		if (std::getline(std::cin, line)) {
			try {
				if (std::regex_match(line, match, min_secs_regex)) {
					int minutes = atoi(match[1].str().c_str());
					int seconds = atoi(match[2].str().c_str());
					cout << convertToMPH(minutes, seconds) << " MPH\n";
				}
				else if (std::regex_match(line, match, kph_regex)) {
					double kph = atof(match[1].str().c_str());
					cout << convertToMPH(kph) << " MPH\n";
				}
				else if (std::regex_match(line, quit_regex)) {
					return 0;
				}
				else {
					std::cout << "Invalid input\n";
				}
			}
			catch (std::runtime_error err) {
				std::cerr << err.what() << '\n';
			}
		}
	}
}