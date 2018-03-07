#include "f.h"
#include "g.h"
#include "user.h"
#include "password.h"
#include <iostream>
using namespace std;

int main () {
    A::f();
    A::g();

    using Authenticate::inputUserName;
    using Authenticate::inputPassword;
    using Authenticate::getUserName;
    using Authenticate::getPassword;

    inputUserName();
    inputPassword();
    std::cout << "Your username is: " << getUserName()
        << "and your password is: " << getPassword() << '\n';
    return 0;
}