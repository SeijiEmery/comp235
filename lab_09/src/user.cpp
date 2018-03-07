#include "user.h"
#include <iostream>
#include <string>

static std::string username;
static bool isValid () {
    return username.size() == 8;
}

namespace Authenticate {
    void inputUserName () {
        do {
            std::cout << "Enter your username (8 letters only): ";
            std::cin >> username;
        } while (!isValid());
    }
    std::string getUserName () {
        return username;
    }
}
