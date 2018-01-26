// File: clothingSizes.cpp
// Name: Seiji Emery
// Compiler: gcc, apple llvm 9.0.0
// Compiler flags: -std=c++14
//
// Purpose: provide functions to calculate clothing sizes.
//
#include <sstream>
#include "clothing_sizes.h"

template <typename T>
static void enforceGt (T value, T threshold, const std::string& msg) {
    if (value <= threshold) {
        std::stringstream ss;
        ss << msg << ": " << value << '\n';
        throw std::runtime_error(ss.str());
    }
}

double getHatSize (double weight, double height) {
    enforceGt(weight, 0.0, "Invalid weight");
    enforceGt(height, 0.0, "Invalid height");

    return weight / height * 2.9;
}

double getJacketSize (double weight, double height, int age) {
    enforceGt(weight, 0.0, "Invalid weight");
    enforceGt(height, 0.0, "Invalid height");
    enforceGt(age,    0,   "Invalid age");

    return height * weight / 288.0 + 
        std::max(0.0, ((age - 30 - 10) / 10) * (1.0 / 8));
}

double getWaistSize (double weight, int age) {
    enforceGt(weight, 0.0, "Invalid weight");
    enforceGt(age,    0, "Invalid age");

    return weight / 5.7 + std::max(0.0, ((age - 28 - 2) / 2) * (1.0 / 10));
}
