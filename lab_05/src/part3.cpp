#include <iostream>
#include <vector>
#include <cstdlib> // rand()
#include <cassert>
#include <algorithm>
using namespace std;

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& vec) {

    if (!vec.size()) {
        return os << "{}";
    } else {
        os << "{ " << vec[0];
        for (size_t i = 1; i < vec.size(); ++i) {
            os << ", " << vec[i];
        }
        return os << " }";
    }
}


int main () {
    srand(time(nullptr));

    const char EMPTY_CHAR = '~';

    vector<char> vec (100, EMPTY_CHAR);
    assert(vec.size() == 100);

    // Populate 20 unique random uppercase characters into the vector
    for (size_t n = 20; n --> 0; ) {
        char chr = 'A' + (rand() % 26);
        for (char v : vec) {
            if (v == chr) {
                ++n; goto retry;
            }
        }
        vec[chr - 'A'] = chr;
        // vec[n] = chr;
    retry:;
    }

    cout << vec << '\n';
    std::sort(vec.begin(), vec.end());

    cout << vec << '\n';

    for (int missing = 6; missing --> 0; ) {
        char nextChar = 'A';
        for (auto it = vec.begin(); it != vec.end(); ++it, ++nextChar) {
            if (*it != nextChar) {
                vec.insert(it, nextChar);
                break;  // must break b/c iterator now invalid
            }
        }
    }
    cout << vec << '\n';

    vec.resize(26);
    cout << vec << '\n';
    return 0;
}