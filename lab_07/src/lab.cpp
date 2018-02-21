#include <iostream>
#include <string>
#include <cstring>
#include "utility/util/lineio.hpp"

int main (int argc, const char** argv) {
    static const size_t MAXLEN = 100;
    std::string line;

    while (1) {
        while (!std::getline(std::cin, line)) {}
        report() << line;
    }
    return 0;
}
