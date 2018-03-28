// File: recursion.cpp
// Name: Seiji Emery
// Compiler: gcc, apple llvm 9.0.0
// Compiler flags: -std=c++11
// https://github.com/SeijiEmery/comp235/tree/master/lab_11
//
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;


// template <typename Iterator>
// void insertionSort (Interator begin, Iterator end) {
//     if (begin == end) return;
//     for (auto it = begin; ++it != end; ) {
//         if (*it < *begin) {
//             std::swap(*it, *begin);
//         }
//     }
//     insertionSort(begin + 1, end);
// }

//
// Exercise 1: insertion sort
//

// Helper function
template <typename It>
void sortMin (It first, It next, It end) {
    if (next != end) {
        if (*first > *next) {
            std::swap(*first, *next);
        }
        sortMin(first, next + 1, end);
    }
}

// Insert sort
template <typename It>
void insertionSort (It begin, It end) {
    if (begin != end) {
        sortMin(begin, begin + 1, end);
        insertionSort(begin + 1, end);
    }
}

template <size_t N>
void insertionSort (int (&array)[N]) {
    insertionSort(&array[0], &array[N]);
}

template <size_t N>
std::ostream& operator << (std::ostream& os, const int (&array)[N]) {
    if (N > 0) {
        os << array[0];
        for (size_t i = 1; i < N; ++i) {
            os << ' ' << array[i];
        }
    }
    return os;
}

int main()
{

    int array[] = { 23, 64, 99, 1, 8 };
    cout << "Initial array: " << array << '\n';
    insertionSort(array);
    cout << "After sorted:  " << array << '\n';
    return 0;
}
