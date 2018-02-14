// utility/range/join.hpp
// Copyright (C) 2017 Seiji Emery 
//
// This forms part of the implicit utility library I originally wrote for part
// of a data structures class; since additional source files were prohibited I
// copied + pasted code and it grew more or less organically.
//
// This is one part of the /utility/range library, which basically implements
// lazy, D-like ranges in c++ (as a replacement for iterators).
//
// This file, join.hpp, implements a non-lazy string joining operation (which 
// is a special case of reduce).
//
#pragma once
#include <sstream>
#include <string>

template <typename Range>
std::string join (std::string sep, Range range) {
    if (!range) return "";
    else {
        std::stringstream ss;
        ss << *range; ++range;
        for (; range; ++range) {
            ss << sep << *range;
        }
        return ss.str();
    }
}
