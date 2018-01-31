// File: treadmill_calculator.h
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/lab_03
//
// Purpose: Provides two functions to convert treadmill values to MPH
//

// Converts treadmill values (eg. 1 mile per 12:40) to MPH (eg. 4.73)
// Preconditions:
//	minutes_per_mile, seconds_per_mile forms valid time interval:
//		minutes_per_mile bounded by [0, +inf)
//		seconds_per_mile bounded by [0, 60)
//	invalid time => throws std::runtime_exception
//
double convertToMPH(int minutes_per_mile, int seconds_per_mile);

// Converts treadmill values (kph) to MPH
// Preconditions:
//	N/A
//
double convertToMPH(double kph);
