# Lab 06 / 07

Demonstrates c++ operator overloading.
Went a bit above the assignment spec, and implemented
1) a generic Boxed<T> type (instead of just IntItem) that should work for all numeric types
2) all operator overloads (pretty much, albeit excepting bitwise + logical operators)
3) a mini pseudo-interpreter to test everything interactively

Note: The interpreter supports simple expressions like 'x = 10', 'x += 10', '1 > 2', but not parentheses or things with more than one operator. And it uses a super crappy parser that just greedily tries to match everything using regexes, and is order dependent (tries matching A, then B, then C, etc). Some of these properties were useful for earlier projects (note: I imported a lot of code from my comp 220 class, see https://github.com/SeijiEmery/comp235/commit/5dce7af44dbfd2407d985f07e7b6842bfabeb772). Said "features" (or bugs) are much less useful (ie. annoying) now but sadly, I don't have time to write a SimpleRegexParser replacement atm, and the code is, well, somewhat elegant (when it's not being a PITA).

Note 2: There's a lot of junk code in there as I was originally just gonna use lab 6 to test features from my 'utility' library, but later reporposed / finished it to finish lab 7 as well.

Note 3: Output is colored text and expects a posix-ish terminal (or anything that supports ANSI escape sequences for output). Other than that it should be pretty multi-platform...

# Build instructions (\*nix)
    cd <some-temp-dir>
    git clone https://github.com/SeijiEmery/comp235
    cd comp235/lab_06/
    mkdir build; cd build
    cmake ..
    make run
