// File: recursion.cpp
// Name: Seiji Emery
// Compiler: gcc, apple llvm 9.0.0
// Compiler flags: -std=c++11
// https://github.com/SeijiEmery/comp235/tree/master/lab_11b
//
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

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

//
// 2nd exercise
//

bool even (size_t n);
bool odd  (size_t n) { return !even(n); }
bool even (size_t n) { return n == 0 || odd(n - 1); }

void testEvenOdd () {}

template <typename... Args>
void testEvenOdd (size_t n, Args... rest) {
    std::cout << n << " is " << 
        (even(n) ? "even" : "odd") << '\n';
    testEvenOdd(rest...);
}

void hanoi (int n, int start, int target, int temp) {
    if (n > 0) {
        hanoi(n - 1, start, temp, target);
        std::cout << "Move disk " << n << " from " << start << " to " << target << '\n';
        hanoi(n - 1, temp, target, start);
    }
}
void hanoi (int n) {
    std::cout << "Hanoi (" << n << ")\n";
    hanoi(n, 1, 2, 3);
}

int main()
{

    int array[] = { 23, 64, 99, 1, 8 };
    cout << "Initial array: " << array << '\n';
    insertionSort(array);
    cout << "After sorted:  " << array << '\n';

    testEvenOdd(0, 1, 2, 3, 4, 5, 23);

    hanoi(2);
    hanoi(3);
    return 0;
}
