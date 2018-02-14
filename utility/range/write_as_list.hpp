// utility/range/write_as_list.hpp
// Copyright (C) 2017 Seiji Emery 
//
// This forms part of the implicit utility library I originally wrote for part
// of a data structures class; since additional source files were prohibited I
// copied + pasted code and it grew more or less organically.
//
// This is one part of the /utility/range library, which basically implements
// lazy, D-like ranges in c++ (as a replacement for iterators).
//
// Implements a common use-case for ranges: printing out a range / sequence
// as a list-like entity (ie. like in python)
//
// Note: this enitty returned is NOT a range, just something that can be 
// printed / outputted to any std::ostream
//
#pragma once
#include <iostream>

template <typename Range>
class RWriteAsList {
    Range range;
public:
    RWriteAsList (Range range) : range(range) {}
    friend std::ostream& operator<< (std::ostream& os, const RWriteAsList<Range>& list) {
        if (list.range) {
            return os << "[ " << join(", ", list.range) << " ]";
        } else {
            return os << "[]";
        }
    }
};
template <typename Range>
auto writeAsList (Range range) -> RWriteAsList<Range> {
    return { range };
}
