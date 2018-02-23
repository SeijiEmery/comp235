#include <stdexcept>
#include <vector>
#include <string>
#include <cassert>
#include "fraction.h"

static unsigned gcd (unsigned a, unsigned b) {
    while (b != 0) {
        auto t = a; a = b; b = t % b;
    }
    return a;
}
// static unsigned abs (int a) {
//     return a >= 0 ?
//         static_cast<unsigned>(a) :
//         static_cast<unsigned>(-a);
// }
static void reduceFraction (int& n, int& d) {
    unsigned num = abs(n), denom = abs(d), cf = gcd(num, denom);
    n = n * d >= 0 ?
        static_cast<int> (num / cf) :
        -static_cast<int>(num / cf);
    d = static_cast<int>(denom / cf);
}
Fraction::Fraction (int n, int d)
    : m_numerator(n), m_denominator(d)
{
    if (m_denominator > 1) {
        reduceFraction(m_numerator, m_denominator);
    }
}


static bool skipWhitespace (std::istream& is) {
    while (isspace(is.get())) {}
    is.unget();
    return is.good();
}
static bool parseInt (std::istream& is, int& result) {
    std::cout << "parseInt() " << is.peek() << " " << isdigit(is.peek()) << '\n';
    if (isdigit(is.peek())) {
        result = 0;
        do {
            result *= 10;
            result += static_cast<int>(is.get() - '0');
        } while (isdigit(is.peek()));
        return true;
    }
    return false;
}

static void enforce (bool cond, const char* msg) {
    if (!cond) {
        throw std::runtime_error(msg);
    }
}
std::istream& operator>> (std::istream& is, Fraction& value) {
    int first = 0, second = 0, third = 1;
    is >> first;
    if (!is.eof()) {
        switch (is.get()) {
            case '+': is >> second; break;
            case '-': is.unget(); is >> second; break;
            case '/': is.unget(); std::swap(first, second); break;
        }
        switch (is.get()) {
            case '/': is >> third; break;
            default:  is.unget();
        }
        value = { first * third + second, third };
    }
    return is;
}
