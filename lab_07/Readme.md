# Lab 07

Lab Exercise 7: Reads in a file / lines of punctuation-delimited sentences, and converts it to a (potentially) prettier form where:
1) all letters / words are lowercased
2) except the 1st sentence of each word which is uppercased
3) all whitespace: tabs, spaces, newlines, etc., is replaced by a single ' ' after each word
4) (not required) terminal punctuation ('.', '!', '?') is not otherwise affected
5) proper nouns are NOT properly capitalized as doing so would require dictionaries or something and is non-trivial.

# Build instructions (\*nix)
    cd <some-temp-dir>
    git clone https://github.com/SeijiEmery/comp235
    cd comp235/lab_07/
    mkdir build; cd build
    cmake ..
    make run

# Testing instructions (example):
    follow the above instructions...

    cat ../input.txt | make run
