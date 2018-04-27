//Testing functions from the algorithm header
//Note: New syntax to you, passing functions as arguments 
#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

int myRandGenerator()
{ 
    return 50 + rand() % (100 - 50 + 1); 
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v) {
    for (const auto& x : v) {
        os << x << ' ';
    }
    return os;
}
#include "utility/util/lineio.hpp"

int main()
{
    srand(time(nullptr));
    vector<int> a(10);
    cout << "Vector size = " << a.size() << endl;

    {
        generate(a.begin(), a.end(), myRandGenerator);
        writeln() << "Generate:                 " << a;
    }
    {
        reverse(a.begin(), a.end());
        writeln() << "Reversed:                 " << a;
    }
    {
        random_shuffle(a.begin(), a.end());
        writeln() << "Shuffled:                 " << a;
    }
    {
        sort(a.begin(), a.end());
        writeln() << "Sorted:                   " << a;
    }
    {
        rotate(&a[0], &a[2], &a[a.size()]);
        writeln() << "Rotated (to element 3):   " << a;
    }
    {
        std::vector<int> b; b.resize(a.size());
        rotate_copy(&a[0], &a[3], &a[a.size()], b.begin());
        writeln() << "rotate_copy (to element 4)";
        writeln() << "copy:                     " << b;
        writeln() << "original:                 " << a;
    }
    {
        int n = a[4];
        writeln() << "Searching for 4th element " << n;
        auto it = find(a.begin(), a.end(), n);

        writeln() << "valid iterator?           " << (it != a.end() ? "true" : "false")
                  << ", got " << *it;
    }
    {
        a[1] = a[3] = a[6] = 22;
        writeln() << "set several values to 22  " << a;
        replace(a.begin(), a.end(), 22, 31);
        writeln() << "Replaced with 31          " << a;
    }
    {
        fill(&a[0], &a[4], 15);
        writeln() << "Filled [0, 4) with 15     " << a;
    }
    {
        auto end = remove(a.begin(), a.end(), 15);
        a.resize(end - a.begin());
        writeln() << "Removed all 15s           " << a;
    }
    {
        std::vector<int> sequence { 22, 33, 44 };
        a.insert(a.end(), sequence.begin(), sequence.end());
        writeln() << "Inserted " << sequence << "     => " << a;
        while (a.size() < 10) {
            a.push_back(myRandGenerator());
        }
        writeln() << "Inserted random(s)        " << a;

        auto it = search(a.begin(), a.end(), sequence.begin(), sequence.end());
        writeln() << "Search: found sequence at " << (it - a.begin());
    }
    {
        int x = myRandGenerator();
        swap(a[0], x);
        writeln() << "Swapped with random value " << a;
        writeln() << "got                       " << x;

    }
    {
        swap_ranges(&a[1], &a[5], &a[6]);
        writeln() << "Swapped [1, 5), [6, 10)   " << a;
    }
    {
        size_t n = count(a.begin(), a.end(), a[0]);
        writeln() << "Counting elements equal to " << a[0] << ": " << n;
    }
    {
        auto it = min_element(a.begin(), a.end());
        writeln() << "min element:              " << *it << " at " << (it - a.begin());
    }
    {
        auto it = max_element(a.begin(), a.end());
        writeln() << "max element:              " << *it << " at " << (it - a.begin());
    }
    {
        writeln() << "[0, 4) == [1, 5)?         " 
            << (equal(&a[0], &a[4], &a[1]) ? "true" : "false");
        writeln() << "[0, 4) == [0, 4)?         " 
            << (equal(&a[0], &a[4], &a[0]) ? "true" : "false");
    }
    {
        std::cout << "find_if odd values:       ";
        for (auto it = a.begin();
            (it = find_if(it, a.end(), [](int i) { return i & 1; })),
            it != a.end();
            ++it
        ) {
            std::cout << *it << " ";
        }
        std::cout << '\n';
    }
    {
        sort(a.begin(), a.end());
        writeln() << "Sorted:                   " << a;
        auto x = myRandGenerator();
        writeln() << "binary_search: contains " << x << "? "
            << (binary_search(a.begin(), a.end(), x) ? "true" : "false"); 
    }
    {
        std::vector<int> b (7);
        generate(b.begin(), b.end(), myRandGenerator);
        sort(b.begin(), b.end());
        writeln() << "Generated new sorted array:  " << b;

        std::vector<int> c (a.size() + b.size());
        merge(a.begin(), a.end(), b.begin(), b.end(), c.begin());
        writeln() << "Merged both sorted arrays:   " << c;
    }
    {
        std::vector<int> b (6);
        copy(&a[4], &a[11], &b[0]);
        writeln() << "Copied [4, 10]:              " << b;
        writeln() << "Elements are >= those in original? "
            << (lexicographical_compare(a.begin(), a.end(), b.begin(), b.end())
                ? "true" : "false");
    }
    return 0;
}
