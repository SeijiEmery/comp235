#include <iostream>
#include <string>
#include "utility/util/lineio.hpp"

int main (int argc, const char** argv) {
    static const size_t MAXLEN = 100;
    std::string line;
    char input [100];
    char output[100];

    while (1) {
        // fetch line (could use any other method for multi-line)
        while (!std::getline(std::cin, line)) {}

        // clear buffers
        memset(&input[0], 0, sizeof(input) / sizeof(input[0]));
        memset(&output[0], 0, sizeof(output) / sizeof(output[0]));

        // copy string data from line to input buffer
        strncpy(&input[0], line.c_str(), sizeof(input) / sizeof(input[0]));
        size_t len = strlen(&input[0]);
        report() << &input[0];

        // fetch pointers to manipulate directly
        const char* src = &input[0];
        char*       dst = &output[0];

        // Search for 1st non-space character + capitalize it
        while (*src == ' ' || *src == '\t' || *src == '\n') ++src;
        *dst = *src + ((*src < 'a' || *src > 'z') ? 0 : 'A' - 'a');
        ++dst; ++src;

        // Process all other input as follows:
        // - copy from input to output
        // - capitalize the 1st letter of each sentence (1st non-space character after '.')
        // - uncapitalize everything else
        // - convert any / all sequences of 1+ spaces / tabs / newlines to a single space
        // - I will _assume_ that there are no buffer overflows, as the length of output
        //   should be <= input (we copy + remove / skip characters but do not add them;
        //   input itself is limited to 100/99 characters by strncpy, though this hasn't
        //   been tested)
        for (; *src; ++src, ++dst) {
            switch (*src) {
                case '.': case '!': case '?':
                    do { switch (*src) { case '.': case '!': case '?':
                        *dst++ = *src++; continue; default:; }
                        break; } while (1);
                    *dst++ = ' '; ++src;
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
