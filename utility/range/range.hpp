// utility/range/range.hpp
// Copyright (C) 2017 Seiji Emery 
//
// This forms part of the implicit utility library I originally wrote for part
// of a data structures class; since additional source files were prohibited I
// copied + pasted code and it grew more or less organically.
//
// This sub-library, /utility/range, forms a mostly lazy (and sometimes greedy)
// implementation of D-like ranges, which replace (and are better than) c++ 
// iterators.
//
#pragma once

#include "sequence.hpp"
#include "map.hpp"
#include "filter.hpp"
#include "reduce.hpp"
#include "join.hpp"
#include "take.hpp"
#include "write_as_list.hpp"
