#include <iostream>
#include <string>
#include "utility/util/lineio.hpp"

bool isupper (char c) { return !(c < 'A' || c > 'Z'); }
bool islower (char c) { return !(c < 'a' || c > 'z'); }
char toupper (char c) { return islower(c) ? c + ('A' - 'a') : c; }
char tolower (char c) { return isupper(c) ? c + ('a' - 'A') : c; }
bool isspace (char c) { return 1UL << static_cast<size_t>(c - 11) & 0x800013 != 0; }
bool ispunct (char c) { return 1UL << static_cast<size_t>(c - 33) & 0x1 != 0; }
bool is_nonterm_punct (char c) { return 1UL << static_cast<size_t>(c - 44) & 0x1 != 0; }
bool is_any_punct     (char c) { return 1UL << static_cast<size_t>(c - 33) & 0x1 != 0; }
void skipspace (char*& s) { while (isspace(*s)) ++s; }

#define c(x) const x
#define m(x) x
#define h char
#define L(x) (size_t)(x)
#define S(x,s) (1UL << L(x - s))
#define C(s,b) S(x,s) & b != 0
#define A(n,m) !(x<n||x>m)
#define P(n,e) static bool n(h x){return e;}
#define F(n) static void n(h*&x)
#define f(x...) for(x)
#define W(x...) while(x)
#define B(x) {x}
#define ds *s
#define dd *d
#define dsp ds++
#define ddp dd++

P(u,A('A','Z'))
P(l,A('a','z'))
P(w,C(11,0x800013))
P(p,C(33,0x1))
P(t,C(0,0x1))
F(ss){W(w(*x))++x;}
F(pp){
    c(h)*s=x;
    m(h)*d=x;
    f(ss(ds),ddp=u(dsp))


    f(ss(*s),*d++=u(*s++))

    for()




    c h*s = x;
    h*s = x;

}







return S(x,s) & m != 0; }
P(u,11,0x800013)








void prettify (char* sbuf) {
    const char* src = sbuf;
    char*       dst = sbuf;

    for (skipspace(src), *dst++ = toupper(*src++); *src; )
        if (isspace(*src)) for (*dst++ = ' '; isspace(*(++src)); );
        else if (ispunct(*src)) 
            while (*src++ = *dst++, !isspaceorterm(*src) ||
                (*dst++ = ' ', skipspace(src), *dst++ = toupper(*src++), 0));
        else *dst++ = *src++;
}

int main (int argc, const char** argv) {
    static const size_t MAXLEN = 100;
    std::string line;
    char sbuf [100];
    
    while (1) {
        while (!std::getline(std::cin, line));
        memset(&sbuf[0], 0, sizeof(sbuf) / sizeof(sbuf[0]))
        strncpy(&sbuf[0], line.c_str(), sizeof(sbuf) / sizeof(sbuf[0]));
        prettify(&sbuf[0]);
        report() << sbuf;
    }
}






    //     else if (is_any_punct(*src)) {
    //         do { *src++ = *dst++; } while (*src && is_any_punct(*src));
    //         skipspace(src);
    //         *dst++ = toupper(*src++);
    //     } else *dst++ = *src++;
    // }
}



int main (int argc, const char** argv) {
    static const size_t MAXLEN = 100;
    std::string line;
    char input [100];
    char output[100];

    while (1) {
        // fetch line (could use any other method for multi-line)
        while (!std::getline(std::cin, line)) {}

        // clear buffers
        memset(&input[0], 0, sizeof(input) / sizeof(input[0]));
        memset(&output[0], 0, sizeof(output) / sizeof(output[0]));

        // copy string data from line to input buffer
        strncpy(&input[0], line.c_str(), sizeof(input) / sizeof(input[0]));
        size_t len = strlen(&input[0]);
        report() << &input[0];

        // fetch pointers to manipulate directly
        const char* src = &input[0];
        char*       dst = &output[0];

        // Search for 1st non-space character + capitalize it
        while (*src == ' ' || *src == '\t' || *src == '\n') ++src;
        *dst = *src + ((*src < 'a' || *src > 'z') ? 0 : 'A' - 'a');
        ++dst; ++src;

        // Process all other input as follows:
        // - copy from input to output
        // - capitalize the 1st letter of each sentence (1st non-space character after '.')
        // - uncapitalize everything else
        // - convert any / all sequences of 1+ spaces / tabs / newlines to a single space
        // - I will _assume_ that there are no buffer overflows, as the length of output
        //   should be <= input (we copy + remove / skip characters but do not add them;
        //   input itself is limited to 100/99 characters by strncpy, though this hasn't
        //   been tested)
        for (; *src; ++src, ++dst) {
            switch (*src) {
                case '.': case '!': case '?':
                    do { switch (*src) { case '.': case '!': case '?':
                        *dst++ = *src++; continue; default:; }
                        break; } while (1);
                    *dst++ = ' '; ++src;
                    while (*src == ' ' || *src == '\t' || *src == '\n') ++src;
                    *dst = *src + ((*src < 'a' || *src > 'z') ? 0 : 'A' - 'a');
                    break;
                case ' ': case '\t': case '\n':
                    for (*dst = ' '; *src == ' ' || *src == '\t' || *src == '\n'; ++src); --src;
                    break;
                default: *dst = *src + ((*src < 'A' || *src > 'Z') ? 0 : 'a' - 'A');
            }
        }
        info() << output;
    }
    return 0;
}
