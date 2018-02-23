# Assignment 03

Implements a fraction class with a testdriver (assignment spec), and a simple repl / interpreter (b/c why not).

# Build instructions (\*nix)
    cd <some-temp-dir>
    git clone https://github.com/SeijiEmery/comp235
    cd comp235/assignment_03/
    mkdir build; cd build
    cmake ..

# To run the repl:
    make run

# To run the testdriver:
    make run_testdriver

# To _manually_ build the repl (depends on c++17 for <variant>)
    g++ -std=c++17 ../src/fraction.cpp ../src/repl.cpp -I ../..
    ./a.out

# Or
    /usr/bin/env clang++ -std=c++17 ../src/fraction.cpp ../src/repl.cpp -I ../..
    ./a.out

# Repl supported commands:
    help
    let x 10
    x * 12 - 14 / 12
    let x x * 2
    del x
    quit
