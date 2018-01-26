// File: clothingSizes.h
// Name: Seiji Emery
// Compiler: gcc, apple llvm 9.0.0
//
// Purpose: provide functions to calculate clothing sizes.
//

#ifndef cothingSizes_H
#define cothingSizes_H

#include <stdexcept> // std::runtime_error

// Preconditions: positive, non-zero values for parameters:
//  weight: in lbs
//  height: in lbs
// Otherwise throws an std::runtime_error
//
double getHatSize (double weight, double height);

// Preconditions: positive, non-zero values for parameters:
//  weight: in lbs
//  height: in lbs
//  age:    in years
// Otherwise throws an std::runtime_error
//
double getJacketSize (double weight, double height, int age);

// Preconditions: positive, non-zero values for parameters:
//  weight: in lbs
//  age:    in years
// Otherwise throws an std::runtime_error
//
double getWaistSize (double weight, int age);

#endif // jacketSizes_H
