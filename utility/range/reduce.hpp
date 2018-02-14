// utility/range/reduce.hpp
// Copyright (C) 2017 Seiji Emery 
//
// This forms part of the implicit utility library I originally wrote for part
// of a data structures class; since additional source files were prohibited I
// copied + pasted code and it grew more or less organically.
//
// This is one part of the /utility/range library, which basically implements
// lazy, D-like ranges in c++ (as a replacement for iterators).
//
// This file, reduce.hpp, implements two versions of a non-lazy reduce operation.
//
#pragma once

template <typename F, typename Range, typename R>
auto reduce (F f, Range range, R first) -> R {
    for (; range; ++range) {
        first = f(first, *range);
    }
    return first;
}
template <typename F, typename Range>
auto reduce (F f, Range range) -> decltype(*range) {
    if (!range) return {};
    else {
        auto first = *range; ++range;
        for (; range; ++range) {
            first = f(first, *range);
        }
        return first;
    }
}