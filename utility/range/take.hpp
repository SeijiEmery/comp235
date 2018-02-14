// utility/range/take.hpp
// Copyright (C) 2017 Seiji Emery 
//
// This forms part of the implicit utility library I originally wrote for part
// of a data structures class; since additional source files were prohibited I
// copied + pasted code and it grew more or less organically.
//
// This is one part of the /utility/range library, which basically implements
// lazy, D-like ranges in c++ (as a replacement for iterators).
//
// This file, take.hpp, implements a lazy take(<n>, <range>) operation.
//
#pragma once

template <typename Range>
struct RTake {
    size_t count;
    Range range;
public:
    RTake (size_t count, Range range) : count(count), range(range) {}
    operator bool () const { return count > 0 && range; }
    RTake& operator++ () { ++range; --count; return *this; }
    auto operator* () const -> decltype(*range) { return *range; }
};
template <typename Range>
auto take (size_t n, Range range) -> RTake<Range> {
    return { n, range };
}
