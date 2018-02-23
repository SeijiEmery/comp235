// string_operations.h
// Seiji Emery
// compiler: clang++
// compiler flags: -std=c++14
//
#pragma once
#include <cstddef> // size_t

size_t length (const char* string);
void   insert (char* dst, const char* src);
bool   search (const char* src, const char* substr);
void   reverse (char* str);
bool   streq  (const char* a, const char* b);
int    parseInt (const char*& str);
