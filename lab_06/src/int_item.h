// File: int_item.h
// Programmer: Seiji Emery
// Compiler: Apple LLVM version 9.0.0 (clang-900.0.39.2)
// Compiler Flags: -std=c++11
//
//Purpose: demonstrate overloading of
//  Arihmetic operators
//  stream I/O operators
//  Comparison operators 

#ifndef __int_item_h__
#define __int_item_h__
#include <iostream>

// Overload this at global name scope to implement comparison for any Boxed<T> values
int cmp (int a, int b) { return a - b; }

// Generalized to Boxed<T> concept.
// Uses all arithmetic operators (hardcoded), which may be undesirable in some cases
template <typename T>
class Boxed {
    T m_value;
public:
    Boxed (T value = T()) : m_value(value) {}
    Boxed (const Boxed<T>&) = default;

    const T& value () const { return m_value; }
    T&       value ()       { return m_value; }

    friend int cmp (const Boxed<T>& a, const Boxed<T>& b) { return cmp(a.value(), b.value()); }

    #define IMPLEMENT_COMPARISON_OPERATOR(op) \
    bool operator op (const Boxed<T>& rhs) { return cmp(*this, rhs) op 0; } \
    bool operator op (const T& rhs)        { return value() op rhs; }
        IMPLEMENT_COMPARISON_OPERATOR(<)
        IMPLEMENT_COMPARISON_OPERATOR(>)
        IMPLEMENT_COMPARISON_OPERATOR(<=)
        IMPLEMENT_COMPARISON_OPERATOR(>=)
        IMPLEMENT_COMPARISON_OPERATOR(==)
        IMPLEMENT_COMPARISON_OPERATOR(!=)
    #undef IMPLEMENT_COMPARISON_OPERATOR

    friend std::ostream& operator<< (std::ostream& os, const Boxed<T>& rhs) {
        return os << rhs.value();
    }
    friend std::istream& operator>> (std::istream& is, Boxed<T>& rhs) {
        return is >> rhs.value();
    }

    #define IMPLEMENT_BINARY_OP(op) \
    friend Boxed<T> operator op (const Boxed<T>& lhs, const Boxed<T>& rhs) { \
        return Boxed<T> { lhs.value() op rhs.value() }; \
    }
    #define IMPLEMENT_MUTATING_OP(op) \
    Boxed<T>& operator op (const Boxed<T>& rhs) { \
        return this->value() op rhs.value(), *this; \
    } \
    Boxed<T>& operator op (const T& rhs) { \
        return this->value() op rhs, *this; \
    }

    // Assignment operator
    IMPLEMENT_MUTATING_OP(=)

    // Arithmetic operators
    IMPLEMENT_BINARY_OP(+) IMPLEMENT_MUTATING_OP(+=)
    IMPLEMENT_BINARY_OP(-) IMPLEMENT_MUTATING_OP(-=)
    IMPLEMENT_BINARY_OP(*) IMPLEMENT_MUTATING_OP(*=)
    IMPLEMENT_BINARY_OP(/) IMPLEMENT_MUTATING_OP(/=)

    // Prefix increment + decrement
    Boxed<T>& operator++ () { return *this += 1; }
    Boxed<T>& operator-- () { return *this -= 1; }

    // Postfix increment + decrement
    // Note: the behavior of this is a bit wierd, which is why it's
    // always better to do ++i (as a habit) instead of i++
    Boxed<T> operator++ (int) { Boxed<T> copy { *this }; ++*this; return copy; }
    Boxed<T> operator-- (int) { Boxed<T> copy { *this }; --*this; return copy; }

    #undef IMPLEMENT_MUTATING_OP
    #undef IMPLEMENT_BINARY_OP
};

// Wrapper class becomes a typedef, doing otherwise would mess with type signatures
typedef Boxed<int> IntItem;

#endif // __int_item_h__
