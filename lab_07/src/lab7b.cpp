#include <iostream>
#include <fstream>
#include <string>
#include "utility/util/lineio.hpp"
using namespace std;

bool isupper (char c) { return !(c < 'A' || c > 'Z'); }
bool islower (char c) { return !(c < 'a' || c > 'z'); }
char toupper (char c) { return islower(c) ? c - 'a' + 'A' : c; }
char tolower (char c) { return isupper(c) ? c - 'A' + 'a' : c; }
bool isspace (char c) { switch (c) { case ' ': case '\t': case '\n': return true; } return false; }

int main (int argc, const char** argv) {
    // std::string str;
    std::ifstream file { "../input.txt" };

    std::string str((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());


    // while (1) {
        // fetch line (could use any other method for multi-line)
        // while (!std::getline(std::cin, str)) {}
        // report() << str;


        // Remove whitespace
        if (isspace(str[0])) {
            str.erase(0, str.find_first_not_of(" \t\n"));
        }
        size_t i = 0;
        while (i < str.size()) {
            i = std::min(str.find_first_of(" \t\n", i), str.size());
            if (i >= str.size()) break;

            // Find end of whitespace and erase
            size_t j = str.find_first_not_of(" \t\n", i);
            if (j < str.size()) {
                str[i] = ' ';
                str.erase(i + 1, j - i - 1);
            }
            i = j;
        }
        // Lowercase everything (all words)
        for (i = 0; i < str.size(); ++i) {
            str[i] = tolower(str[i]);
        }
        // Uppercase words at beginning of sentences
        i = 0;
        while (i < str.size()) {
            str[i] = toupper(str[i]);
            i = str.find_first_of(".!?", i);
            while (str[i] == '.' || str[i] == '!' || str[i] == '?') ++i;
            i = str.find_first_not_of(" \n\t", i);
        }
        info() << str;
    // }
    return 0;
}
