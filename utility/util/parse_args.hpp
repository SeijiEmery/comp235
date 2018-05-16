// utility/util/parse_args.hpp
// Copyright (C) 2018 Seiji Emery 
//
// Implements a basic, pretty nice command-line argument parser akin to D's std.getopt.
// Features are limited but it is easily extensible.
// For a working example see lab_18/generate.cpp
//
// Basic usage:
//  int main (int argc, const char** argv) {
//      int foo = 10;
//      double bar = 12;
//      int baz = 22;
//      parseArgs(argc, argv)
//          .parse("--foo", foo)
//          .parse({ "--bar", "-b" }, bar)
//          .parse("--baz", [&](int x){ baz = x; })     // takes a lambda, equivalent to 1st case
//          .parse("--hello", [&](){ std::cout << "Hello world!\n"; })
//          .parseDefault([](const char* arg) {
//              std::cerr << "Unexpected argument '" << arg << "'\n";
//           });
//
//      // do stuff with arguments grabbed above...
//  }
//
#pragma once

namespace detail {

template <typename T> struct Reader;
template <> struct Reader<int> { static int read (const char* arg) { return atoi(arg); }};
template <> struct Reader<double> { static double read (const char* arg) { return atof(arg); }};
template <> struct Reader<std::string> { static std::string read (const char* arg) { return { arg }; }};

template <typename T>
static T read (const char* arg) { return Reader<T>::read(arg); }

class ArgParser {
    int          argc;
    const char** argv;
    int          i = 1;
    std::vector<std::function<bool()>> parseCases;
    std::function<void(const char*)> defaultCase;
public:
    typedef ArgParser This;
    
    ArgParser (int argc, const char** argv)
        : argc(argc), argv(argv) {}
    ~ArgParser () { parseAll(); }

    void parseAll () {
        while (i < argc) {
            // fprintf(stderr, "parsing argument %d '%s'\n", i, argv[i]);
            int j = 0;
            for (const auto& parseCase : parseCases) {
                if (parseCase()) {
                    // fprintf(stderr, "handled with case %d\n", j);
                    goto continue_;       
                }
                ++j;
            }
            defaultCase(argv[i++]);
        continue_:;
        }
    }
    This& parseDefault (std::function<void(const char*)> callback) {
        defaultCase = callback;
        return *this;
    }
    template <typename... Args>
    This& parse (std::string name, std::function<void(Args...)> callback) {
        return parse({ name }, callback);
    }
    This& parse (std::initializer_list<std::string> argNames, std::function<void()> callback) {
        // fprintf(stderr, "case 1\n");
        parseCases.emplace_back([argNames, callback, this]() -> bool {
            if (argc - i >= 1 && match(argv[i], argNames)) {
                callback();
                i += 1;
                return true;
            }
            return false;
        });
        return *this;
    }
    template <typename T>
    This& parse (std::initializer_list<std::string> argNames, std::function<void(T)> callback) {
        // fprintf(stderr, "case 2\n");
        parseCases.emplace_back([argNames, callback, this]() -> bool {
            if (argc - i >= 2 && match(argv[i], argNames)) {
                callback(read<T>(argv[i + 1]));
                i += 2;
                return true;
            }
            return false;
        });
        return *this;
    }

    template <typename T>
    This& parse (const std::string& name, T& value) {
        return parse(
            std::initializer_list<std::string> { name }, 
            std::function<void(T)> { [&](T x) { 
                // fprintf(stderr, "setting value = %d\n", x); 
                return value = x; 
            } 
        });
    }
    template <typename T>
    This& parse (std::initializer_list<std::string> argNames, T& value) {
        return parse(
            argNames, 
            std::function<void(T)> { [&](T x) { 
                // fprintf(stderr, "setting value = %d\n", x); 
                return value = x; 
            } 
        });
    }
private:
    static bool match (const char* arg, const std::string& name) { return arg == name; }
    static bool match (const char* arg, const std::initializer_list<std::string>& names) {
        for (auto name : names) {
            if (arg == name) {
                return true;
            }
        }
        return false;
    }
};
}; // namespace detail
detail::ArgParser parseArgs (int argc, const char** argv) { return { argc, argv }; }
