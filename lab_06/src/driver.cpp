// File: driver.cpp
// Programmer: Seiji Emery
// Compiler: Apple LLVM version 9.0.0 (clang-900.0.39.2)
// Compiler Flags: -std=c++11
//
// Purpose: Test operator overloading in the IntItem class.
//
#include "int_item.h"
#include "utility/util/lineio.hpp"
#include "utility/util/mem_bench.hpp"
#include "utility/range/range.hpp"
#include "utility/parsers/simple_regex_parser.hpp"
#include <unordered_map>
#include <vector>
#include <cstdlib>  // exit
using namespace std;

int main()
{
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

    std::vector<Boxed<int>> vec { 1, 2, 3, 4, 5, 6 };
    report() << "[ " << join(", ", sequence(vec.begin(), vec.end())) << " ]";
    report() << "[ " << join(", ", 
        map([](const Boxed<int>& value) { return value * 2 + 1; },
            sequence(vec.begin(), vec.end())
        )
    ) << " ]";

    std::unordered_map<std::string, Boxed<int>> values;

    typedef const std::smatch& Match;
    SimpleRegexParser()
        .caseOf("quit", [&](Match match) { exit(0); })
        .caseOf("{} = {}", [&](Match match) {
            values[match[1].str()] = atoi(match[2].str().c_str());
        })
        #define DO_BIN_OP(syntax, op) \
            .caseOf(syntax, [&](Match match) {\
                auto a = values.find(match[1].str());\
                if (a == values.end()) {\
                    warn() << "undefined: " << match[1].str();\
                    warn() << "in " << match[1].str() << " " #op " " << match[2].str();\
                } else {\
                    auto b = values.find(match[2].str());\
                    if (b == values.end()) {\
                        warn() << "undefined: " << match[2].str();\
                        warn() << "in " << match[1].str() << " " #op " " << match[2].str();\
                    } else {\
                        info() << match[1].str() << " " #op " " << match[2].str();\
                        report() << ((a->second) op (b->second));\
                    }\
                }\
            })
        DO_BIN_OP("{} := {}", =)
        DO_BIN_OP("{} + {}", +)
        DO_BIN_OP("{} - {}", -)
        DO_BIN_OP("{} \\* {}", *)
        DO_BIN_OP("{} / {}", /)
        DO_BIN_OP("{} > {}", >)
        DO_BIN_OP("{} < {}", <)
        DO_BIN_OP("{} >= {}", >=)
        DO_BIN_OP("{} <= {}", <=)
        DO_BIN_OP("{} == {}", ==)
        DO_BIN_OP("{} != {}", !=)
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
