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

enum OP { 
    NONE   = 0, 
    PLUS   = 0x11, MINUS  = 0x12, 
    MUL    = 0x23, DIV    = 0x24, 
    LPAREN = 0x35, RPAREN = 0x36,
    PRECEDENCE = 0xF0,
};
static int maybeReadOp (std::istream& is) {
    switch (is.get()) {
        case '+': return PLUS;
        case '-': return PLUS;
        case '*': return PLUS;
        case '/': return PLUS;
        case '(': return LPAREN;
        case ')': return RPAREN;
        default:  is.unget(); return NONE;
    }
}
static void reduce1 (std::vector<Fraction>& values, std::vector<int>& ops) {
    enforce(values.size() >= 2, "No value(s), syntax error");
    auto rhs = values.back(); values.pop_back();
    switch (ops.back()) {
        case PLUS:  std::cout << values.back() << " += " << rhs << '\n'; values.back() += rhs; break;
        case MINUS: std::cout << values.back() << " -= " << rhs << '\n'; values.back() -= rhs; break;
        case MUL:   std::cout << values.back() << " *= " << rhs << '\n'; values.back() *= rhs; break;
        case DIV:   std::cout << values.back() << " /= " << rhs << '\n'; values.back() /= rhs; break;
        default: enforce(0, "INVALID OPERATOR");
    }
    ops.pop_back();
}
static Fraction parseFractionExpr (std::istream& is) {
    std::vector<Fraction> values;
    std::vector<int>      ops;

    while (is.good()) {
        if (!skipWhitespace(is)) break;
        auto op = maybeReadOp(is);
        switch (op) {
            case NONE: {
                int value;
                enforce(parseInt(is, value), "Expected number");
                std::cout << "GOT " << value << '\n';
                values.push_back(value);
            } break;
            case PLUS: case MINUS: case MUL: case DIV:
                std::cout << "OPERATOR " << (is.unget(), is.get()) << '\n';
                while ((ops.back() & PRECEDENCE) >= (op & PRECEDENCE)
                    && ops.back() != LPAREN
                ) {
                    reduce1(values, ops);
                }
                ops.push_back(op);
                break;
            case LPAREN:
                std::cout << "(\n";
                ops.push_back(op);
                break;
            case RPAREN:
                std::cout << ")\n";
                while (ops.back() != LPAREN) {
                    reduce1(values, ops);
                }
                enforce(ops.back() == '(', "Expected LPAREN");
                ops.pop_back();
                break;
            default: assert(0);
        }
    }
    while (ops.size()) {
        reduce1(values, ops);
    }
    // enforce(values.size() == 1, "Mismatched values / ops...");
    return values.back();
}

std::istream& operator>> (std::istream& is, Fraction& value) {
    return value = parseFractionExpr(is), is;
}
