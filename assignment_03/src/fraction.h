// File: fraction.h
// Name: Seiji Emery
// Compiler: clang++
// Compiler flags: -std=c++11
// https://github.com/SeijiEmery/comp235/tree/master/assignment_03
//
#pragma once
#include <iostream>

class Fraction {
    int m_numerator   = 0;
    int m_denominator = 1;
public:
    // Constructors
    Fraction () {}
    Fraction (int num, int denom = 1);
    Fraction (const Fraction&) = default;

    // Assignment operator
    Fraction& operator= (const Fraction&) = default;

    #define DEFN_BINARY_FCN(R,A,B,name) friend R name (A a, B b)
    #define OVERLOAD_BINARY_FCN(R,name) DEFN_BINARY_FCN(R,const Fraction&, const Fraction&, name)
    #define OVERLOAD_BINARY_OP(op)      OVERLOAD_BINARY_FCN(Fraction, operator op)
    #define OVERLOAD_IOSTREAM(stream,op) DEFN_BINARY_FCN(stream,stream,const Fraction&,operator op)
    #define N m_numerator
    #define D m_denominator

    // Arithmetic operators
    OVERLOAD_BINARY_OP(+) { return { a.N * b.D + b.N * a.D, a.D * b.D }; }
    OVERLOAD_BINARY_OP(-) { return { a.N * b.D - b.N * a.D, a.D * b.D }; }
    OVERLOAD_BINARY_OP(*) { return { a.N * b.N, a.D * b.D }; }
    OVERLOAD_BINARY_OP(/) { return { a.N * b.D, a.D * b.N }; }

    // Comparison operators
    OVERLOAD_BINARY_FCN(int, cmp) { return a.N * b.D - b.N * a.D; }
    bool operator== (const Fraction& other) const { return cmp(*this, other) == 0; }
    bool operator!= (const Fraction& other) const { return cmp(*this, other) != 0; }
    bool operator>= (const Fraction& other) const { return cmp(*this, other) >= 0; }
    bool operator<= (const Fraction& other) const { return cmp(*this, other) <= 0; }
    bool operator>  (const Fraction& other) const { return cmp(*this, other) >  0; }
    bool operator<  (const Fraction& other) const { return cmp(*this, other) <  0; }

    // Mutating / assignment arithmetic operators
    Fraction& operator+= (const Fraction& other) { return *this = (*this + other); }
    Fraction& operator-= (const Fraction& other) { return *this = (*this - other); }
    Fraction& operator*= (const Fraction& other) { return *this = (*this * other); }
    Fraction& operator/= (const Fraction& other) { return *this = (*this / other); }

    // Increment & decrement
    Fraction& operator++ () { return (*this) += { 1 }; }
    Fraction& operator-- () { return (*this) -= { 1 }; }
    Fraction  operator++ (int _) { auto copy { *this }; (*this) += { 1 }; return copy; }
    Fraction  operator-- (int _) { auto copy { *this }; (*this) -= { 1 }; return copy; }


    // Conversion operators (implicitely convert to double)
    operator double () const { 
        return static_cast<double>(m_numerator) / static_cast<double>(m_denominator); 
    }

    friend std::ostream& operator << (std::ostream& os, const Fraction& a) {
        int d = static_cast<int>(a.D), n = a.N / d, r = a.N % d;
        if (n != 0 && r != 0) {
            return os << n << (r > 0 ? "+" : "") << r << "/" << d;
        } else if (r != 0) {
            return os << r << "/" << d;
        } else {
            return os << n;
        }
    }
    friend std::istream& operator >> (std::istream& is, Fraction& a);

    #undef DEFN_BINARY_FCN
    #undef OVERLOAD_BINARY_FCN
    #undef OVERLOAD_BINARY_OP
    #undef N
    #undef D
};
