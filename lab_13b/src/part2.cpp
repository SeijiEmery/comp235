#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// include to get memory usage report at end of program execution
#include "utility/util/mem_bench.hpp"


template <typename T>
class Set {
    std::vector<T> m_values;
public:
    Set () {}
    Set (std::initializer_list<T> values) {
        for (auto& value : values) {
            insert(value);
        }
    }
    Set (const Set&)            = default;
    Set& operator= (const Set&) = default;
    ~Set () {}

    size_t size () const { return m_values.size(); }
    void insert (const T& item) {
        for (auto & value : m_values) {
            if (value == item) {
                return;
            }
        }
        m_values.push_back(item);
    }

    // returns a new array of items, user is responsible for freeing memory
    // this is a terrible idea since we could just return a const ref,
    // buuuut I did not write this assignment, so...
    T* getNewArrayOfItems () const {
        T* values = new T[size()];
        std::copy(m_values.begin(), m_values.end(), &values[0]);
        return values;
    }

    const T* elements () const { return &m_values[0]; }
    T* elements () { return &m_values[0]; }

    auto begin () const -> decltype(m_values.begin()) { return m_values.begin(); }
    auto end   () const -> decltype(m_values.end())   { return m_values.end(); }

    auto begin () -> decltype(m_values.begin()) { return m_values.begin(); }
    auto end   () -> decltype(m_values.end())   { return m_values.end(); }

    friend std::ostream& operator<< (std::ostream& os, const Set<T>& set) {
        bool first = true;
        os << "{";
        for (auto& value : set) {
            if (first) { os << " "; first = false; }
            else       { os << ", "; }
            os << value;
        }
        if (set.size()) { os << " "; }
        os << "}";
        return os;
    }
};

int main () {
    {
        std::cout << "Set<int>\n";

        // Construct array. Supports std::initializer_list constructor ofc, since this is modern c++.
        Set<int> values { 1, 1, 2, 3, 4, 4, 5 };

        // Output values _properly_
        std::cout << values << '\n';

        // Insert some stuff
        values.insert(12);
        values.insert(22);
        std::cout << values << '\n';

        // Can also iterate, since proper iterators were implemented
        for (const auto& value : values) {
            std::cout << value << ", ";
        }
        std::cout << "\b\b\n";


        // Print stuff out, this time using the function required for this assignment

        // Names is appropriate, serves as a warning for future programmers that
        // this code was poorly designed and should be refactored (ie. removed).

        std::cout << "values:";
        int* arrayReturnedFromPoorlyDesignedAPI = values.getNewArrayOfItems();
        for (size_t i = 0; i < values.size(); ++i) {
            std::cout << '\t' << arrayReturnedFromPoorlyDesignedAPI[i] << '\n';
        }
        delete[] arrayReturnedFromPoorlyDesignedAPI;
        std::cout << '\n';

        // Note how we didn't leak any memory!!!
    }
    {
        // Repeat of the above, this time using strings

        std::cout << "Set<string>\n";
        Set<string> values { "foo", "foo", "bar", "baz", "bar", "foo" };
        std::cout << values << '\n';

        std::cout << "values:";
        std::string* arrayReturnedFromPoorlyDesignedAPI = values.getNewArrayOfItems();
        for (size_t i = 0; i < values.size(); ++i) {
            std::cout << '\t' << arrayReturnedFromPoorlyDesignedAPI[i] << '\n';
        }
        delete[] arrayReturnedFromPoorlyDesignedAPI;
        std::cout << '\n';

        // Fact that this code does not crash or leak memory should serve as proof that it works
    }
    return 0;
}
