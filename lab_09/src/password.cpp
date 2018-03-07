#include "password.h"
#include <iostream>
#include <string>
#include <cctype>

static std::string password;
static bool isValid () {
    if (password.size() < 8) {
        return false;
    }
    for (auto& chr : password) {
        if (!isalpha(chr)) {
            return true;
        }
    }
    return false;
}

namespace Authenticate {
    void inputPassword () {
        do {
            std::cout << "Enter your password (at at least 8 characters and at least one non-letter): ";
            std::cin >> password;
        } while (!isValid());
    }
    std::string getPassword () {
        return password;
    }
}
