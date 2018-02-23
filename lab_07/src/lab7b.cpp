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

        size_t i = 0;
        while (i < str.size()) {
            // Find next space
            i        = str.find_first_of(" \t\n", i);
            size_t j = str.find_first_not_of(" \t\n", i);

            info() << str;
            warn() << i << ", " << j;
            report() << str[i] << ", " << str[j];

            if (std::max(i, j) < string::npos) {
                str.erase(i + 1, j - i - 1);
                str[i] = ' ';
            }
            i = j;
        }
        info() << str;
    }
    return 0;
}
