// utility/parsers/simple_regex_parser.hpp
// Copyright (C) 2017 Seiji Emery 
//
// This forms part of the implicit utility library I originally wrote for part
// of a data structures class; since additional source files were prohibited I
// copied + pasted code and it grew more or less organically.
//
// This file in particular implements a "simple regex parser", aka a 
// fuzzily-matched stack-like language that ignores bad syntax and matches 
// only user-defined structures defined using a regex-like syntax.
//
// Such a parser is remarkably useful as a tool to implement minimalistic
// interactive programs to test the behavior of other code. Initially, I
// wrote this to test a hashtable, with code that looked something like
// the following:
//
// #include "utility/util/lineio.hpp"
// #include "utility/simple_regex_parser.hpp"
// #include "some_hashtable.hpp"
//
// int main () {
//    Hashtable hashtable;
//
//    SimpleRegexParser()
//      .caseOf("quit", [&](Match match) {
//          warn() << "exiting";
//          exit(0);
//      })
//      .caseOf("capacity", [&](Match match) {
//          report() << hashtable.capacity();
//      })
//      .caseOf("length|size", [&](Match match) {
//          report() << hashtable.size();
//      })
//      .caseOf("display|show", [&](Match match) {
//          report() << hashtable;
//      })
//      .caseOf("resize {}", [&](Match match) {
//          auto size = atoi(match[1].str().c_str());
//          report() << "Resizing to " << size << " (current size " << hashtable.size() << ")";
//          hashtable.resize(size);
//      })
//      .caseOf("clear", [&](Match match) {
//          hashtable.clear();
//      })
//      .caseOf("del {}", [&](Match match) {
//          auto key = match[1].str();
//          if (hashtable.containsKey(key)) {
//              report() << "deleted " << key;
//              hashtable.deleteKey(key);
//          } else {
//              warn() << "missing key " << key;
//          }
//      })
//      .caseOf("{} = {}", [&](Match match) {
//          auto key = match[1].str(), value = match[2].str();
//          hashtable[key] = value;
//          report() << key << " = " << value;
//      })
//      .caseOf("{}", [&](Match match) {
//          auto key = match[1].str();
//          if (hashtable.containsKey(key)) {
//              report() << hashtable[key];
//          } else {
//              warn() << "undefined";
//          }
//      })
//      .parse(std::cin);
//    return 0;
// }
//
//  SYNTAX:
//      " "     spaces converted to  'match 1+ whitespace: `\s*`'
//      "{}"    curly brackets converted to 'match 1 word: `(\w+)`'
//      anything else is properly escaped and handled as a normal regex
//      (ie. treated as a literal for most cases; may use further regex syntax)
//
//  USAGE:
//      SimpleRegexParser()
//          .caseOf(<syntax 1>, [](const std::smatch& match) { /* ... */ })
//          .caseOf(<syntax 2>, [](const std::smatch& match) { /* ... */ })
//          ...
//          .parse(std::cin);       
//
//  Note: std::cin may be replaced by any std::istream, including files, strings, etc.
//  .parse(<input>) will exit when its input is exhausted; for std::cin, it will never
//  exit so you should implement eg. "quit" in your DSL grammar (ie. call exit(0)).
//
#pragma once
#include <functional>       // std::function
#include <utility>          // std::pair 
#include <vector>           // std::vector
#include <regex>            // std::regex, regex_replace, smatch

struct SimpleRegexParser {
    typedef std::function<void(const std::smatch&)> callback_t;
    typedef std::pair<std::regex, callback_t> case_t;
    std::vector<case_t> cases;
public:
    SimpleRegexParser () {}
    SimpleRegexParser (std::initializer_list<case_t> cases) 
        : cases(cases) {}

private:
    static std::string replace_whitespace (std::string input) {
        static std::regex r { "([ ]+)"};
        return std::regex_replace(input, r, "\\s*");
    }
    static std::string replace_group (std::string input) {
        static std::regex r { "\\{[^\\}]*\\}" };
        return std::regex_replace(input, r, "(\\w+)");
    }
    static std::string escape_chars (std::string input) {
        static std::regex r { "([\\.\\+\\=\\[\\]\\(\\)\\-\\?\\:])" };
        return std::regex_replace(input, r, ("\\$1"));
    }
    static std::string to_regex (std::string input) {
        return "^\\s*" + replace_group(replace_whitespace(escape_chars(input)));
    }
public:
    SimpleRegexParser& caseOf (const char* pattern, callback_t callback) {
        auto regex = to_regex(pattern);
        // info() << "Creating case from " << pattern;
        // info() << "Generated regex:   " << regex;
        cases.emplace_back(std::regex(regex), callback);
        return *this;
    }
    bool parse (std::string& line, std::smatch &match) const {
        for (auto& case_ : cases) {
            if (std::regex_search(line, match, case_.first)) {
                case_.second(match);
                line = match.suffix().str();
                return true;
            }
        }
        return false;
    }
    void parse (std::istream& is) const {
        std::string line;
        std::smatch match;
        while (is) {
            while (!getline(is, line));
            while (parse(line, match));
        }
    }
};
