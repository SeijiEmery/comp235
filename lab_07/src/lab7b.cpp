#include <iostream>
#include <string>
#include "utility/util/lineio.hpp"
using namespace std;

bool isupper (char c) { return !(c < 'A' || c > 'Z'); }
bool islower (char c) { return !(c < 'a' || c > 'z'); }
char toupper (char c) { return islower(c) ? c : c - 'a' + 'A'; }
char tolower (char c) { return isupper(c) ? c : c - 'A' + 'a'; }
bool isspace (char c) { switch (c) { case ' ': case '\t': case '\n': return true; } return false; }

int main (int argc, const char** argv) {
    std::string str;

    while (1) {
        // fetch line (could use any other method for multi-line)
        while (!std::getline(std::cin, str)) {}
        report() << str;

        // Search for 1st non-space character + capitalize it
        if (isspace(str[0])) {
            str.erase(0, str.find_first_not_of(" \t\n"));
        }
        str[0] += ((str[0] < 'a' || str[0] > 'z') ? 0 : 'A' - 'a');

        // Process all other input as follows:
        // - copy from input to output
        // - capitalize the 1st letter of each sentence (1st non-space character after '.')
        // - uncapitalize everything else
        // - convert any / all sequences of 1+ spaces / tabs / newlines to a single space
        // - I will _assume_ that there are no buffer overflows, as the length of output
        //   should be <= input (we copy + remove / skip characters but do not add them;
        //   input itself is limited to 100/99 characters by strncpy, though this hasn't
        //   been tested)
        // for (; *src; ++src, ++dst) {
        //     switch (*src) {
        //         case '.': case '!': case '?':
        //             do { switch (*src) { case '.': case '!': case '?':
        //                 *dst++ = *src++; continue; default:; }
        //                 break; } while (1);
        //             *dst++ = ' '; ++src;
        //             while (*src == ' ' || *src == '\t' || *src == '\n') ++src;
        //             *dst = *src + ((*src < 'a' || *src > 'z') ? 0 : 'A' - 'a');
        //             break;
        //         case ' ': case '\t': case '\n':
        //             for (*dst = ' '; *src == ' ' || *src == '\t' || *src == '\n'; ++src); --src;
        //             break;
        //         default: *dst = *src + ((*src < 'A' || *src > 'Z') ? 0 : 'a' - 'A');
        //     }
        // }
        info() << str;
    }
    return 0;
}
