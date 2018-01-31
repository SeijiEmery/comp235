// File: treadmill_calculator.cpp
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/lab_03
//
// Purpose: Implements two functions to convert treadmill values to MPH
//

#include <stdexcept>	// std::runtime_error
#include <climits>		// INT_MAX

template <typename T>
static void enforceBounded(const char* msg, T value, T min, T max) {
	if (value < min || value > max) {
		throw std::runtime_error(msg);
	}
}

double convertToMPH(int minutes_per_mile, int seconds_per_mile) {
	enforceBounded("invalid minutes", minutes_per_mile, 0, INT_MAX);
	enforceBounded("invalid seconds", seconds_per_mile, 0, 59);
	auto m = static_cast<double>(minutes_per_mile);
	auto s = static_cast<double>(seconds_per_mile);
	return 1.0 / (m / 60 + s / 3600);
}

double convertToMPH(double kph) {
	return kph * 1.61;
}
