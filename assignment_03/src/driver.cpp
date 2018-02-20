#include "fraction.h"
#include <iostream>
#include <vector>
#include <utility>
#include <regex>
#include <cassert>
#include <variant>
#include <map>
#include "utility/util/lineio.hpp"
using namespace std;

template <typename T>
class RegexMatcher {
    typedef std::regex                          Regex;
    typedef std::function<T(const std::smatch&)> Transform;
    typedef std::pair<Regex, Transform>         MatchPair;
    typedef std::vector<MatchPair>              MatchList;

    MatchList list;
public:
    RegexMatcher (const std::initializer_list<MatchPair>& values)
        : list(values) {}
    bool match (string& str, T& value) {
        std::smatch match;
        for (const auto& mp : list) {
            // if (std::regex_match(str, match, mp.first, std::regex_constants::match_continuous)) {
            if (std::regex_search(str, match, mp.first, std::regex_constants::match_continuous)) {
                value = mp.second(match);
                str   = match.suffix().str();
                return true;
            }
        }
        return false;
    }
};

enum {
    TOKEN_NONE = 0,
    TOKEN_NAME,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_WHITESPACE,
    TOKEN_EOL,
};

const static int SPACES_PER_TAB = 4;

class Token {
    int m_type;
    variant<int, string> m_value;
public:
    Token () : m_type(TOKEN_NONE) {}
    Token (int type, const std::string& str)
        : m_type(type)
    {
        assert(type == TOKEN_OPERATOR || type == TOKEN_EOL || type == TOKEN_NAME);
        if (type == TOKEN_NAME || type == TOKEN_OPERATOR) {
            m_value = str;
        } else if (type == TOKEN_EOL) {
            int indent = 0;
            for (char c : str) {
                switch (c) {
                    case ' ': ++indent; break;
                    case '\t': indent += SPACES_PER_TAB; break;
                    case '\n': break;
                    default: assert(0);
                }
            }
            m_value = indent;
        }
    }
    Token (int type, int value)
        : m_type(type), m_value(value)
    {
        assert(type == TOKEN_NUMBER);
    }
    Token (int type)
        : m_type(type)
    {
        assert(type == TOKEN_WHITESPACE);
    }
    Token (const Token&)            = default;
    Token& operator= (const Token&) = default;

    int type   () const { return m_type; }
    int value  () const { assert(type() == TOKEN_NUMBER); return std::get<int>(m_value); }
    int indent () const { assert(type() == TOKEN_EOL);    return std::get<int>(m_value); }
    const std::string& op   () const { assert(type() == TOKEN_OPERATOR); return std::get<string>(m_value); }
    const std::string& name () const { assert(type() == TOKEN_NAME);     return std::get<string>(m_value); }

    friend std::ostream& operator<< (std::ostream& os, const Token& t) {
        switch (t.type()) {
            case TOKEN_NAME:       return os << "TOKEN_NAME(name = " << t.name() << ")";
            case TOKEN_NUMBER:     return os << "TOKEN_NUMBER(value = " << t.value() << ")";
            case TOKEN_EOL:        return os << "TOKEN_EOL(indent = "   << t.indent() << ")";
            case TOKEN_WHITESPACE: return os << "TOKEN_WHITESPACE";
            case TOKEN_OPERATOR:   return os << "TOKEN_OPERATOR(op = " << t.op() << ")";
            case TOKEN_NONE:       return os << "TOKEN_NONE";
            default:               return os << "invalid token!";
        }
    }
    static void unittest () {
        { 
            Token tok; 
            assert(tok.type() == TOKEN_NONE);
            assert(!tok.type());
            tok = Token { TOKEN_NAME, "fubar" };
            assert(tok.type() == TOKEN_NAME);
            assert(tok.name() == "fubar");
            tok = Token { TOKEN_WHITESPACE };
            assert(tok.type() == TOKEN_WHITESPACE);
            tok = Token { TOKEN_NUMBER, -12345 };
            assert(tok.type() == TOKEN_NUMBER);
            assert(tok.value() == -12345);
            Token copy { tok };
            assert(tok.type() == TOKEN_NUMBER && tok.value() == -12345);
            tok = Token { TOKEN_EOL, "\n\t   \t  " };
            assert(tok.type() == TOKEN_EOL && tok.indent() == (5 + 2 * SPACES_PER_TAB));
            tok = Token { TOKEN_OPERATOR, "+=" };
            assert(tok.type() == TOKEN_OPERATOR && tok.op() == "+=");
            tok = Token { TOKEN_WHITESPACE };
            assert(tok.type() == TOKEN_WHITESPACE);
        }
    }
};

// Special "error" values
struct EmptyEval   {};  // nothing evalutated (empty line)
struct QuitCommand {};  // user entered "quit"

class RTokenizer {
    RegexMatcher<Token> matcher;
    Token               nextTok;
    std::string         line;
    bool                canMatch = false;
public:
    RTokenizer () : matcher {
        { std::regex("([0-9]+)"),   [](const std::smatch& match) -> Token { return { TOKEN_NUMBER, atoi(match[1].str().c_str()) }; }},
        { std::regex("(\n[ \t]*)"), [](const std::smatch& match) -> Token { return { TOKEN_EOL, match[1].str() }; }},
        { std::regex("([ \t]+)"),   [](const std::smatch& match) -> Token { return { TOKEN_WHITESPACE }; }},
        { std::regex("(\\+\\+|\\-\\-|[\\+\\-\\*\\/\\^\\>\\<\\!\\=]\\=?|[\\(\\)])"), [](const std::smatch& match) -> Token { return { TOKEN_OPERATOR, match[1].str() }; }},
        { std::regex("([a-zA-Z_$@][a-zA-Z_$@0-9]*)"), [](const std::smatch& match) -> Token { return { TOKEN_NAME, match[1].str() }; }}
    } {}

    void read (std::string line) { this->line = line; canMatch = true; ++(*this); }
    operator bool () const { return canMatch; }
    RTokenizer& operator++ () {
        if (canMatch && !(canMatch = matcher.match(line, nextTok))) {
            nextTok = Token {};
            if (line.size() != 0) {
                throw std::runtime_error("Syntax error");
                // std::cerr << "Syntax error: unparsed '" << line << "'\n";
            }
        }
        return *this;
    }
    const Token& operator*  () const { return nextTok; }
    const Token* operator-> () const { return &nextTok; }
};

class RInfixTokenizer {
    map<string, int>   prec;
    RTokenizer         tok;
    Token              token;
    std::vector<Token> operators;
    bool               dequeuing = false;
public:
    RInfixTokenizer () : prec {
        { "*", 3 },
        { "/", 3 },
        { "+", 2 },
        { "-", 2 },
        { "(", 1 },
    } {}
    void read (std::string line) { tok.read(line); ++(*this); }
    operator bool () const { return token.type() != TOKEN_NONE; }
    RInfixTokenizer& operator++ () {
        if (dequeuing) {
            if (!operators.size() || (operators.back().op() == "(" && (operators.pop_back(), true))) {
                dequeuing = false;
            } else {
                token = operators.back();
                operators.pop_back();
                return *this;
            }
        }
        switch (tok->type()) {
            case TOKEN_NAME: case TOKEN_NUMBER: case TOKEN_NONE: case TOKEN_EOL: case TOKEN_WHITESPACE: {
                token = *tok; ++tok;
            } break;
            case TOKEN_OPERATOR: {
                if (tok->op() == "(") {
                    operators.push_back(*tok);
                    ++tok;
                    ++(*this);
                } else if (tok->op() == ")") {
                    dequeuing = true;
                    ++tok;
                    ++(*this);
                } else {
                    operators.push_back(*tok);
                    ++tok;
                    ++(*this);
                }
            } break;
        }
        return *this;
    }
    const Token& operator*  () const { return token;  }
    const Token* operator-> () const { return &token; }
};

bool g_debugTokens = false;

template <typename Tok>
Fraction parsePostfix (Tok tok, map<string, Fraction>& dict) {
    std::vector<Fraction> values;
    for (; tok; ++tok) {
        if (g_debugTokens && tok->type() != TOKEN_WHITESPACE) {
            std::cout << *tok << '\n';
        }
        switch (tok->type()) {
            case TOKEN_NAME: {
                if (tok->name() == "quit") { throw QuitCommand(); }
                else if (tok->name() == "help") {
                    info() << "Supported syntax:"
                        << "\n\tquit                -- exits program"
                        << "\n\tdebug (on | off)    -- enables / disables token + line debugging"
                        << "\n\tlet <name> <expr>   -- assign variables"
                        << "\n\t<expr> + <expr>     -- note: +=, etc., NOT supported!"
                        << "\n\t<expr> - <expr>     -- note: prefix / unary '-' not supported (yet)"
                        << "\n\t<expr> * <expr>"
                        << "\n\t<expr> / <expr>"
                        << "\n\t<expr> <cmp> <expr> -- where <cmp>: ==, !=, >=, <=, >, <"
                        << "\nwhere"
                        << "\n\t<expr> := <integer> | <name>";
                    throw EmptyEval();
                } else if (tok->name() == "debug") {
                    while ((++tok)->type() == TOKEN_WHITESPACE) {}
                    if (tok->type() == TOKEN_NAME) {
                        if (tok->name() == "on")  { info() << "token logging enabled!"; g_debugTokens = true;  throw EmptyEval(); }
                        if (tok->name() == "off") { info() << "token logging disabled!"; g_debugTokens = false; throw EmptyEval(); }
                    }
                    warn() << "expected 'debug (on | off)', not '" << *tok << "'\n";
                    throw std::runtime_error("syntax error");
                } else if (tok->name() == "let") {
                    while ((++tok)->type() == TOKEN_WHITESPACE) {}
                    if (tok->type() == TOKEN_NAME) {
                        auto name = tok->name();
                        while ((++tok)->type() == TOKEN_WHITESPACE) {}
                        if (tok->type() == TOKEN_OPERATOR && tok->op() == "=") { ++tok; }
                        return dict[name] = parsePostfix(tok, dict);
                    }
                    warn() << "expected 'let <name> = <expression>', not '" << *tok << "'\n";
                    throw std::runtime_error("syntax error");
                } else {
                    auto it = dict.find(tok->name());
                    if (it != dict.end()) {
                        values.push_back(it->second);
                    } else {
                        throw std::runtime_error("variable is undefined!");
                    }
                }
            } break;
            case TOKEN_NUMBER:   values.emplace_back(tok->value()); break;
            case TOKEN_OPERATOR: {
                if (values.size() < 2) {
                    throw std::runtime_error("Syntax error (stack underflow while evaluating postfix)");
                    if (values.size()) return values.back();
                    else return {};
                }
                auto rhs = values.back(); values.pop_back();
                auto lhs = values.back(); values.pop_back();
                if (tok->op() == "+") {values.push_back(lhs + rhs); }
                else if (tok->op() == "-") { values.push_back(lhs - rhs); }
                else if (tok->op() == "*") { values.push_back(lhs * rhs); }
                else if (tok->op() == "/") { values.push_back(lhs / rhs); }
                else if (tok->op() == "=="){ report() << (lhs == rhs ? "true" : "false"); throw EmptyEval(); }
                else if (tok->op() == "!="){ report() << (lhs != rhs ? "true" : "false"); throw EmptyEval(); }
                else if (tok->op() == ">="){ report() << (lhs >= rhs ? "true" : "false"); throw EmptyEval(); }
                else if (tok->op() == "<="){ report() << (lhs <= rhs ? "true" : "false"); throw EmptyEval(); }
                else if (tok->op() == ">") { report() << (lhs >  rhs ? "true" : "false"); throw EmptyEval(); }
                else if (tok->op() == "<") { report() << (lhs <  rhs ? "true" : "false"); throw EmptyEval(); }
                else {
                    throw std::runtime_error("Syntax error (unrecognized operator)");
                    std::cerr << "Syntax error (unrecognized operation: '" << tok->op() << "'\n";
                    if (values.size()) return values.back();
                    else return {};
                }
            } break;
            default:;
        }
    }
    if (values.size() == 0) {
        throw EmptyEval();
    }
    if (values.size() != 1) {
        throw std::runtime_error("Syntax error (stack underflow)");
        if (values.size()) return values.back();
        else return {};
    }
    return values.back();
}
Fraction parsePostfix (string line, map<string, Fraction>& dict) {
    RTokenizer tok; tok.read(line);
    if (g_debugTokens) {
        info() << line;
    }
    return parsePostfix(tok, dict);
}

Fraction parseInfix (string line, map<string, Fraction>& dict) {
    // Precedence hack
    line = regex_replace(line, std::regex("\\("), "((((((");
    line = regex_replace(line, std::regex("\\)"), "))))))");
    line = regex_replace(line, std::regex("[\\=\\>\\<\\!]\\=?"), ")))))$0(((((");
    line = regex_replace(line, std::regex("\\+"), "))))+((((");
    line = regex_replace(line, std::regex("\\-"), ")))-(((");
    line = regex_replace(line, std::regex("\\*"), "))*((");
    line = regex_replace(line, std::regex("\\/"), ")/(");
    if (g_debugTokens) {
        info() << line;
    }
    RInfixTokenizer tok; tok.read(line);
    return parsePostfix(tok, dict);
}
Fraction parseEval (string line, map<string, Fraction>& dict) {
    return parseInfix("("+line+")", dict);
}

int main () {
    Token::unittest();

    map<string, Fraction> dict;
    Fraction fraction;
    std::string line;
    while (1) {
        try {
            while (!getline(cin, line) && line.size()) {}
            fraction = parseEval(line, dict);
            report() << fraction << " (" << static_cast<double>(fraction) << ")";
        } catch (EmptyEval _) {
            // Nothing evaluated, ignore
        } catch (QuitCommand _) {
            return 0;
        } catch (std::runtime_error error) {
            warn() << error.what();
        }
    }
    return 0;
}
