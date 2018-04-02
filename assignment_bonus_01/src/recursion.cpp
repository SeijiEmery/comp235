// copyright (c) Seiji Emery 2018

#include <iostream>
#include <string>

//
// PART 1
// Substring searching algorithm
//

// Return whether the string s strictly contains a substring q,
// (ie. starting at the first character)
// eg.
//      issubstr("foobar",  "foo") => true
//      issubstr("ffoobar", "foo") => false
//      issubstr("foo",     "foo") => true
//      issubstr("f",       "foo") => false
bool issubstr (const char* s, const char* q) {
    return !*s || !*q ?
        *q == '\0' :
        *s == *q ? issubstr(s + 1, q + 1) : false;
}

// Return whether the string s contains the substring q
// blame assignment for names, etc
// eg.
//      find("foobar", "foo") => true
//      find("foobar", "bar") => true
//      find("foo",    "foo") => true
//      find("f",      "foo") => false
bool find (const char* s, const char* q) {
    return !*s || !*q ?
        *q == '\0' :
        issubstr(s, q) || find(s + 1, q);
}

//
// PART 2
// Substring index / pointer searching algorithm:
// find index / pointer to the first substring, or -1 / nullptr otherwise
//

// Note: c++ has pointers, these are _semantically_ much better than indices
const char* findFirstSubstring (const char* s, const char* q) {
    return !*s || !*q ?
        (*q == '\0' ? s : nullptr) :
        (issubstr(s, q) ? s : findFirstSubstring(s + 1, q));
}
// Though we can ofc convert between the two trivially
int indexOf (const char* s, const char* q) {
    const char* ptr = findFirstSubstring(s, q);
    return ptr ? 
        static_cast<int>(ptr - s) : 
        -1;
}

// Method adapters for std::string
bool find (const std::string& s, const std::string& q) {
    return find(s.c_str(), q.c_str());
}
int indexOf (const std::string& s, const std::string& q) {
    return indexOf(s.c_str(), q.c_str());
}

//
// Testdriver
//

//
// Wrap values for custom formatting
// (note: cannot overload raw operator<< for bool, since aliased to int...)
//
template <typename T>
struct Wrapped {
    const T& value;
    Wrapped (const T& value) : value(value) {}
};
template <typename T> Wrapped<T> wrap (const T& value) { return { value }; }

#define OVERLOAD_OSTREAM_OP(T, value) std::ostream& operator<< (std::ostream& os, const T& value)
OVERLOAD_OSTREAM_OP(Wrapped<bool>, wrapped) { return os << (wrapped.value ? "true" : "false"); }
template <typename T> OVERLOAD_OSTREAM_OP(Wrapped<T>, wrapped) { return os << wrapped.value; }
#undef OVERLOAD_OSTREAM_OP

//
// Print macro
//
#define EVAL(f, a, b) do {\
    auto x = f(a, b); \
    std::cout << #f "(" #a ", " #b ") => " << wrap(x) << '\n'; \
} while (0)

//
// Testcases
//
int main () {
    EVAL(find, "Mississippi!", "sip");
    EVAL(find, "Mississippi!", "pip");
    EVAL(indexOf, "Mississippi!", "Miss");
    EVAL(indexOf, "Mississippi!", "iss");
    EVAL(indexOf, "Mississippi!", "sip");
    EVAL(indexOf, "Mississippi!", "pip");
    EVAL(indexOf, "", "pip");
    EVAL(indexOf, "pip", "pip");
    return 0;
}
#undef EVAL
