#include <iostream>
#include <string>
#include <cstring>
#include "utility/util/lineio.hpp"

int main (int argc, const char** argv) {
    static const size_t MAXLEN = 100;
    std::string line;
    char input [100];
    char output[100];

    while (1) {
        while (!std::getline(std::cin, line)) {}

        strncpy(&input[0], line.c_str(), sizeof(input) / sizeof(input[0]));
        size_t len = strlen(&input[0]);
        report() << &input[0];

        const char* src = &input[0];
        char*       dst = &output[0];

        while (*src == ' ' || *src == '\t' || *src == '\n') ++src;
        *dst = *src + ((*src < 'a' || *src > 'z') ? 0 : 'A' - 'a');
        ++dst; ++src;

        for (; *src; ++src, ++dst) {
            switch (*src) {
                case '.': 
                    *dst++ = '.'; *dst++ = ' '; ++src;
                    while (*src == ' ' || *src == '\t' || *src == '\n') ++src;
                    *dst = *src + ((*src < 'a' || *src > 'z') ? 0 : 'A' - 'a');
                    break;
                case ' ': case '\t': case '\n':
                    for (*dst = ' '; *src == ' ' || *src == '\t' || *src == '\n'; ++src); --src;
                    break;
                default: *dst = *src + ((*src < 'A' || *src > 'Z') ? 0 : 'a' - 'A');
            }
        }
        info() << output;
    }
    return 0;
}
