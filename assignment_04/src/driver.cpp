// string_operations.h
// Seiji Emery
// compiler: clang++
// compiler flags: -std=c++14
//
#include "stringops.h"
#include "utility/util/lineio.hpp"

void runStringOps (const char* a, const char* b) {
    char strbuf [2048];

    report() << "String A:";
    report() << "\t'" << a << "'";
    report() << "\tlength: " << length(a);
    report() << "\tcopied: '" << (insert(&strbuf[0], a), &strbuf[0]) << "'";
    report() << "\tcopy length: " << length(&strbuf[0]);
    report() << "\treversed:   '" << (reverse(&strbuf[0]), &strbuf[0]) << "'";
    report() << "\tunreversed: '" << (reverse(&strbuf[0]), &strbuf[0]) << "'";
    report() << "\tcontains B: "  << (search(a, b) ? "true" : "false");

    report() << "String B:";
    report() << "\t'" << b << "'";
    report() << "\tlength = " << length(b);
    report() << "\tcopied: '" << (insert(&strbuf[0], b), &strbuf[0]) << "'";
    report() << "\tcopy length: " << length(&strbuf[0]);
    report() << "\treversed:   '" << (reverse(&strbuf[0]), &strbuf[0]) << "'";
    report() << "\tunreversed: '" << (reverse(&strbuf[0]), &strbuf[0]) << "'";
    report() << "\tcontains A: "  << (search(b, a) ? "true" : "false");

    report() << "String A == String B?";
    report() << "\t" << (streq(a, b) ? "true" : "false");
}

void tryParseInt (const char* str) {
    report() << "\tparseInt('" << str << "') => " << parseInt(str)
        << ", remaining: '" << str << "'";
}

int main () {
    report() << "integer parsing tests: ";
    tryParseInt("");
    tryParseInt("asdf");
    tryParseInt("0");
    tryParseInt("-1");
    tryParseInt("+1234 hello world!");
    tryParseInt("-104981284");
    tryParseInt("0x2afc");
    tryParseInt("0b110101010");
    tryParseInt("0b123410101");
    tryParseInt("0x213za hello world!");

    std::string a, b;
    while (1) {
        std::cout << "string A: "; getline(std::cin, a);
        std::cout << "string B: "; getline(std::cin, b);
        runStringOps(a.c_str(), b.c_str());
    }
}
