// string_operations.h
// Seiji Emery
// compiler: clang++
// compiler flags: -std=c++14
//
#pragma once

size_t length (const char* string);
void   insert (char* dst, const char* src);
bool   search (const char* src, const char* substr);
void   reverse (char* str);
bool   streq  (const char* a, const char* b);
int    atoi   (const char*& str);
