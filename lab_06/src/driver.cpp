// File: driver.cpp
// Programmer: Seiji Emery
// Compiler: Apple LLVM version 9.0.0 (clang-900.0.39.2)
// Compiler Flags: -std=c++11
//
// Purpose: Test operator overloading in the IntItem class.
//
#include "int_item.h"
#include <cassert>

#include <utility>
template <size_t i, size_t n>
struct TuplePrinter {
    template <typename... Args>
    static void print (std::ostream& os, std::tuple<Args...> tuple) {
        os << std::get<i>(tuple) << ", ";
        TuplePrinter<i+1,n-1>::print(os, tuple);
    }
};
template <size_t i>
struct TuplePrinter<i, 1> {
    template <typename... Args>
    static void print (std::ostream& os, std::tuple<Args...> tuple) {
        os << std::get<i>(tuple);
    }
};
template <size_t i>
struct TuplePrinter<i, 0> {
    // Invalid, no implementation
};
template <typename... Types>
std::ostream& operator<< (std::ostream& os, std::tuple<Types...> tuple) {
    return os << "(", 
        TuplePrinter<0, std::tuple_size<std::tuple<Types...>>::value>::print(os, tuple),
        os << ")";
}
#include "utility/util/lineio.hpp"
#include "utility/util/mem_bench.hpp"
#include "utility/range/range.hpp"
#include "utility/parsers/simple_regex_parser.hpp"
#include <unordered_map>
#include <vector>
#include <utility>  // std::tuple
#include <cstdlib>  // exit
using namespace std;


template <typename First, typename Second>
std::ostream& operator<< (std::ostream& os, const std::pair<First, Second> pair) {
    return os << "(" << pair.first << ", " << pair.second << ")";
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& vec) {
    return os << writeAsList(sequence(vec.begin(), vec.end()));
}

int main()
{
    report() << std::make_tuple(1);
    report() << std::make_tuple(1, 2);
    report() << std::make_tuple(1, "hello", 3, "world!");

    // report() << std::vector<std::tuple<int, std::string, float>> {
    //     { 1, "asdf", 0.5f },
    //     { 2, "blarg", 0.0f },
    //     { 22, "t", 1209839108049.0f }
    // };

    IntItem myIntObj01{ 111 };
    IntItem myIntObj02{ 222 };
    
    myIntObj01 = myIntObj02 + myIntObj01;
    report() << "Object 1 = " << myIntObj01 << "  Object 2 = " << myIntObj02;

    if (myIntObj01 < myIntObj02)
        report() << "Object 1 is smaller.";
    else
        report() << "Object 2 is smaller.";

    // cout << "Get object 1: ";
    // cin >> myIntObj01;
    // report() << "Got " << myIntObj01;

    // Just testing library stuff, ignore this
    std::vector<Boxed<int>> vec { 1, 2, 3, 4, 5, 6 };
    report() << writeAsList(sequence(vec.begin(), vec.end()));
    report() << writeAsList(
        map([](const Boxed<int>& value) { return value * 2 + 1; },
            sequence(vec.begin(), vec.end())));

    typedef Boxed<int> Value;
    std::unordered_map<std::string, Value> values;

    auto tryGetRef = [&](const std::string& name) -> bool {
        auto it = values.find(name);
        if (it == values.end()) {
            warn() << "Undefined: '" << name << "'";
            return false;
        } else {
            return true;
        }
    };
    auto tryGetValue = [&](const std::string& valueOrName, Value& value) -> bool {
        if (isdigit(valueOrName[0])) {
            return value = Value(atoi(valueOrName.c_str())), true;
        } else if (tryGetRef(valueOrName)) {
            return value = values[valueOrName], true;
        } else {
            return false;
        }
    };

    auto doBinOp = [&](const std::string& first, const std::string& second, const std::string& last) {
        if ((first == "+" && second == "+") || (first == "-" && second == "-")) {
            if (tryGetRef(last)) {
                switch (first[0]) {
                    case '+': report() << (++values[last]); break;
                    case '-': report() << (--values[last]); break;
                    default: assert(0);
                }
            }
        } else if ((second == "+" && last == "+") || (second == "-" && last == "-")) {
            if (tryGetRef(first)) {
                switch (second[0]) {
                    case '+': report() << (values[first]++); break;
                    case '-': report() << (values[first]--); break;
                    default: assert(0);
                }
            }
        } else if (second == "=") {
            Value value = 0;
            if (tryGetValue(last, value)) {
                values[first] = value;
            }
        } else if (second == "+=" || second == "-=" || second == "*=" || second == "/=") {
            Value value = 0;
            if (tryGetRef(first) && tryGetValue(last, value)) {
                if      (second == "+=") { report() << (values[first] += value); }
                else if (second == "-=") { report() << (values[first] -= value); }
                else if (second == "*=") { report() << (values[first] *= value); }
                else if (second == "/=") { report() << (values[first] /= value); }
                else { warn() << "syntax error"; }
            }
        } else {
            Value lhs, rhs;
            if (tryGetValue(first, lhs) && tryGetValue(last, rhs)) {
                if      (second == "+=") { report() << (lhs += rhs); }
                else if (second == "-=") { report() << (lhs -= rhs); }
                else if (second == "*=") { report() << (lhs *= rhs); }
                else if (second == "+")  { report() << (lhs +  rhs);  }
                else if (second == "-")  { report() << (lhs -  rhs);  }
                else if (second == "*")  { report() << (lhs *  rhs);  }
                else if (second == "/")  { report() << (lhs /  rhs);  }
                else if (second == "==") { report() << (lhs == rhs ? "true" : "false"); }
                else if (second == "!=") { report() << (lhs != rhs ? "true" : "false"); }
                else if (second == ">=") { report() << (lhs >= rhs ? "true" : "false"); }
                else if (second == "<=") { report() << (lhs <= rhs ? "true" : "false"); }
                else if (second == ">")  { report() << (lhs >  rhs ? "true" : "false");  }
                else if (second == "<")  { report() << (lhs <  rhs ? "true" : "false");  }
                else { warn() << "syntax error"; }
            }
        }
    };

    typedef const std::smatch& Match;
    SimpleRegexParser()
        .caseOf("quit", [&](Match match) { exit(0); })
        .caseOf("dump", [&](Match match) {
            report() << writeAsList(sequence(values.begin(), values.end()));
        })
        .caseOf("del {}", [&](Match match) {
            auto it = values.find(match[1].str());
            if (it != values.end()) {
                info() << "del " << match[1].str();
                values.erase(it);
            } else {
                warn() << "undefined: " << match[1].str();
            }
        })
        .caseOf("{} {} {}", [&](Match match) {
            info() << match[1].str() << " " << match[2].str() << " " << match[3].str();
            doBinOp(match[1].str(), match[2].str(), match[3].str());
        })
        .caseOf("{}", [&](Match match) {
            auto it = values.find(match[1].str());
            if (it != values.end()) {
                info() << match[1].str();
                report() << it->second;
            } else {
                warn() << "undefined";
            }
        })
        .caseOf("\\.*", [&](Match match) {
            warn() << "Syntax error";
        })
        .parse(std::cin);
    return 0;
}
