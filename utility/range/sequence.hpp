// utility/range/sequence.hpp
// Copyright (C) 2017 Seiji Emery 
//
// This forms part of the implicit utility library I originally wrote for part
// of a data structures class; since additional source files were prohibited I
// copied + pasted code and it grew more or less organically.
//
// This is one part of the /utility/range library, which basically implements
// lazy, D-like ranges in c++ (as a replacement for iterators).
//
// This file, sequence.hpp, implements a range, RSequence, that adapts a pair
// of existing iterators into a range.
//
#pragma once

template <typename It>
class RSequence {
    It begin, end;
public:
    RSequence (It begin, It end) : begin(begin), end(end) {}
    operator bool () const { return begin != end; }
    RSequence& operator++ () { return ++begin, *this; }
    auto operator* () const -> decltype(*begin) { return *begin; }
};
template <typename It>
auto sequence (It begin, It end) -> RSequence<It> { return { begin, end }; }
