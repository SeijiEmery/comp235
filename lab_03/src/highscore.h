// File: highscore.h
// Name: Seiji Emery
// Compiler: 
// Compiler flags: 
// https://github.com/SeijiEmery/comp235/tree/master/lab_03
//
// Purpose: Provides a function to load a list of high score values from a text file
// in a specific format, and return the highest name / score pair from that file.
//

#include <string>
#include <istream>

// Scans through a file with the following format, and sets (name) and (score)
// to the highest name / score values in the file
//
// Preconditions:
//	file is valid, and not at EOF (file.good() == true)
// Postconditions:
//  file is at EOF if all reads were successful
//	(just reads pairs of lines until reaching bad input)
//
// File format: repeating lines of
//	<name  (string)>
//  <score (int)>
//
// eg.
//	Bob
//	110
//	Alice
//	220
//	<EOF>
//
// => returns name = "Alice", score = 220
//
// Note: error handling / validation is minimal, so make sure to use exactly the right file format!
//
void getHighScore(std::istream& file, std::string& name, int& score);
