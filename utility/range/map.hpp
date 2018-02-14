// utility/range/map.hpp
// Copyright (C) 2017 Seiji Emery 
//
// This forms part of the implicit utility library I originally wrote for part
// of a data structures class; since additional source files were prohibited I
// copied + pasted code and it grew more or less organically.
//
// This is one part of the /utility/range library, which basically implements
// lazy, D-like ranges in c++ (as a replacement for iterators).
//
// This file, map.hpp, implements a lazy map(<range>, <fcn>) operation.
//
#pragma once

template <typename F, typename Range>
class RMap {
    F f;
    Range range;
public:
    RMap (F f, Range range) : f(f), range(range) {}
    operator bool () const { return bool(range); }
    RMap& operator++ () { return ++range, *this; }
    auto  operator*  () const -> decltype(f(*range)) { return f(*range); }
};
template <typename F, typename Range>
auto map (F f, Range range) -> RMap<F,Range> { return { f, range }; }

template <typename F, typename It>
auto map (F f, It begin, It end) -> decltype(map(f, sequence(begin, end))) {
    return map(f, sequence(begin, end));
}
