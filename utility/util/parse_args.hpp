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
//      int firstArg = -1;
//      double secondArg = 20;
//      
//      parseArgs(argc, argv)
//          .parse(firstArg, secondArg, [](int x) { std::cout << "Last arg: " << x << '\n'; })
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
#include <functional>   // std::function
#include <vector>       // std::vector
#include <string>       // std::string

namespace detail {

bool isDigit (char c) { return !(c < '0' || c > '9'); }

bool parseInt (const char*& input, long long& result, long long& divisor) {
    long long sign = 1;
    if (input[0] == '-' && isDigit(input[1])) {
        sign = -1;
        ++input;
    } else if (input[0] == '+' && isDigit(input[1])) {
        ++input;
    } else if (!isDigit(input[0])) {
        return false;
    }
    result = 0;
    if (input[0] == '0' && (input[1] == 'b' || input[1] == 'B')) {
        input += 2;
        while (*input == '0' || *input == '1') {
            result *= 2;
            result += static_cast<long long>(*input++ - '0');
            divisor *= 2;
        }
    } else if (input[0] == '0' && (input[1] == 'x' || input[1] == 'B')) {
        input += 2;
        do {
            char c = *input++;
            if (c >= '0' && c <= '9') { c -= '0'; }
            else if (c >= 'A' && c <= 'F') { c -= 'A'; }
            else if (c >= 'a' && c <= 'f') { c -= 'a'; }
            else { break; }
            result *= 16;
            result += static_cast<long long>(c);
            divisor *= 16;
        } while (1);
    } else {
        while (*input >= '0' && *input <= '9') {
            result *= 10;
            result += static_cast<long long>(*input++ - '0');
            divisor *= 10;
        }
    }
    return result *= sign, true;
}
bool parseInt (const char*& input, long long& result) {
    long long divisor;
    return parseInt(input, result, divisor);
}
bool parseNumber (const char*& input, long long& integer, long long& decimal, long long& divisor, long long& exponent) {
    if (!parseInt(input, integer)) {
        return false;
    }
    decimal = 0, divisor = 0, exponent = 0;
    if (*input == '.') {
        if (!parseInt(++input, decimal, divisor)) {
            return true;
        }
    }
    if (*input == 'e' || *input == 'E') {
        if (!parseInt(++input, exponent)) {
            --input;
            assert(*input == 'e' || *input == 'E');
        }
    }
    return true;
}
bool parse (const char*& input, double& value) {
    long long integer, decimal, divisor, exponent;
    if (parseNumber(input, integer, decimal, divisor, exponent)) {
        value = static_cast<double>(integer)
              + static_cast<double>(decimal) / static_cast<double>(divisor);
        if (exponent != 0) {
            integer = 0;
            for (int n = abs(exponent); n --> 0; ) {
                integer *= 10;
            } 
            if (exponent > 0) { value *= static_cast<double>(integer); }
            else if (exponent < 0) { value /= static_cast<double>(integer); }
        }
        return true;
    }
    return false;
}
bool parse (const char*& input, long long& integer) {
    long long decimal, divisor, exponent;
    if (parseNumber(input, integer, decimal, divisor, exponent)) {
        if (decimal) {
            integer *= 10;
            ++exponent;
            for (; exponent > 0; --exponent) {
                integer *= 10;
                divisor /= 10;
                integer += decimal / divisor;
                decimal %= divisor;
            }
            for (; exponent < 0; ++exponent) {
                integer /= 10;
            }
            if (integer % 10 >= 5) {
                integer += 10;
            }
            integer /= 10;
        } else if (exponent) {
            for (; exponent > 0; --exponent) {
                integer *= 10;
            }
            for (; exponent < 0; ++exponent) {
                integer /= 10;
            }
        }
        return true;
    }
    return false;
}
bool parse (const char* input, int& value) {
    long long integer;
    if (parse(input, integer)) {
        value = static_cast<int>(integer);
        return true;
    }
    return false;
}
bool parse (const char* input, unsigned& value) {
    long long integer;
    if (parse(input, integer)) {
        value = static_cast<unsigned>(abs(integer));
        return true;
    }
    return false;
}
bool parse (const char* input, std::string& value) {
    return value = input, true;
}



template <typename T> struct Reader {
    static T read (const char* arg) {
        T value;
        bool ok = parse(arg, value);
        assert(ok);
        return value;
    }  
};
// template <> struct Reader<int> { static int read (const char* arg) { return atoi(arg); }};
// template <> struct Reader<double> { static double read (const char* arg) { return atof(arg); }};
// template <> struct Reader<std::string> { static std::string read (const char* arg) { return { arg }; }};

template <typename T>
static T read (const char* arg) { return Reader<T>::read(arg); }

class ArgParser {
    int          argc;
    const char** argv;
    int          i = 1;
    int          nextDefaultArg = 0;
    std::vector<std::function<bool()>> parseCases;
    std::vector<std::function<bool()>> defaultCases;
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
            if (nextDefaultArg < defaultCases.size()) {
                if (defaultCases[nextDefaultArg]()) {
                    ++nextDefaultArg;
                    goto continue_;
                }
            }
            defaultCase(argv[i++]);
        continue_:;
        }
    }
    void reset () {
        i = 1;
        nextDefaultArg = 0;
    }

    This& parseDefault (std::function<void(const char*)> callback) {
        defaultCase = callback;
        return *this;
    }

    template <typename T>
    This& parse (std::function<void(T)> callback) {
        defaultCases.emplace_back([callback, this]() -> bool {
            callback(read<T>(argv[i]));
            i += 1;
            return true;
        });
        return *this;
    }
    template <typename T, typename... Rest>
    This& parse (std::function<void(T)> callback, Rest... rest) {
        return parse(callback), parse(rest...);
    }

    template <typename T>
    This& parse (T& value) {
        return parse([&value](T x){ value = x; }); 
    }
    template <typename T, typename... Rest>
    This& parse (T& value, Rest... rest) {
        return parse(value), parse(rest...);
    }

    template <typename... Args>
    This& parse (std::string name, std::function<void(Args...)> callback) {
        return parse({ name }, callback);
    }
    This& parse (std::initializer_list<std::string> argNames, std::function<void()> callback) {
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
    template <typename T, typename U>
    This& parse (std::initializer_list<std::string> argNames, std::function<void(T, U)> callback) {
        parseCases.emplace_back([argNames, callback, this]() -> bool {
            if (argc - i >= 3 && match(argv[i], argNames)) {
                callback(read<T>(argv[i + 1]), read<U>(argv[i + 2]));
                i += 3;
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
