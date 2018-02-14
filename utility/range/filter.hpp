// utility/range/filter.hpp
// Copyright (C) 2017 Seiji Emery 
//
// This forms part of the implicit utility library I originally wrote for part
// of a data structures class; since additional source files were prohibited I
// copied + pasted code and it grew more or less organically.
//
// This is one part of the /utility/range library, which basically implements
// lazy, D-like ranges in c++ (as a replacement for iterators).
//
// This file, filter.hpp, implements a lazy filter(<range>, <pred>) operation.
//
#pragma once

template <typename F, typename Range>
class RFilter {
    F f;
    Range range;

    void advanceFilter () { while (range && !f(*range)) { ++range; } }
public:
    RFilter (F f, Range range) : f(f), range(range) {}
    operator bool () const { return bool(range); }
    RFilter& operator++ () { ++range; advanceFilter(); return *this; }
    auto operator* () const -> decltype(*range) { return *range; }
};
template <typename F, typename Range>
auto filter (F f, Range range) -> RFilter<F,Range> { return { f, range }; }

template <typename F, typename It>
auto filter (F f, It begin, It end) -> decltype(filter(f, sequence(begin, end))) {
    return filter(f, sequence(begin, end));
}
