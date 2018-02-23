// string_operations.h
// Seiji Emery
// compiler: clang++
// compiler flags: -std=c++14
//
#include "stringops.h"
#include <cassert>
#include <algorithm> // std::swap

size_t length (const char* str) {
    assert(str != nullptr);
    size_t len = 0;
    while (*str++) ++len;
    return len;
}
void insert (char* dst, const char* src) {
    assert(dst != nullptr && src != nullptr);
    while ((*dst++ = *src++));
}
bool search (const char* src, const char* substr) {
    assert(src != nullptr && substr != nullptr);
    for (; *src; ++src) {
        if (*src == *substr) {
            const char* search = substr;
            while (*search && *src && *search++ == *src++);
            if (!*search) return true;
        }
    }
    return false;
}
void reverse (char* str) {
    assert(str != nullptr);
    if (!*str) return;
    char* end = &str[length(str)-1];
    for (; str < end; ++str, --end) {
        std::swap(*str, *end);
    }
}
bool streq (const char* a, const char* b) {
    while (*a && *b && *a++ == *b++);
    return *a == *b;
}
static bool parseDecimalDigit (char c, int& value) {
    return c >= '0' && c <= '9' ?
        (value += static_cast<int>(c - '0')), true :
        false;
}
static bool parseHexDigit (char c, int& value) {
    return parseDecimalDigit(c, value) ||
        (c >= 'a' && c <= 'f' ? (value += static_cast<int>(c - 'a' + 10), true) : 
        (c >= 'A' && c <= 'F' ? (value += static_cast<int>(c - 'A' + 10), true) : false));
}
static bool parseBinaryDigit (char c, int& value) {
    return c == '0' || c == '1' ?
        value += static_cast<int>(c - '0'), true : false;
}
static int parseBase (const char*& str, int base, bool(&parseDigit)(char c, int& value)) {
    int value = 0;
    while (parseDigit(*str, value))
        ++str, value *= base;
    return value / base;
}
static int parseDec (const char*& str) { return parseBase(str, 10, parseDecimalDigit); }
static int parseHex (const char*& str) { return parseBase(str, 16, parseHexDigit); }
static int parseBin (const char*& str) { return parseBase(str, 2,  parseBinaryDigit); }

int parseInt (const char*& str) {
    int sign = 1;
    if (*str == '-')      ++str, sign = -1;
    else if (*str == '+') ++str, sign = 1;
    if (str[0] == '0' && str[1] == 'x') {
        return sign * parseHex(str += 2);
    } else if (str[0] == '0' && str[1] == 'b') {
        return sign * parseBin(str += 2);
    } else if (str[0] < '0' || str[0] > '9') {
        return -((1 << 31) - 1);
    } else {
        return sign * parseDec(str);
    }
}
