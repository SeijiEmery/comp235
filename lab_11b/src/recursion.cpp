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

// Returns the sum of the decimal digits in an integer.
// ie. sumOfDigits(12345) = 1 + 2 + 3 + 4 + 5 = 15
int sumOfDigits(long n) 
{
    if (n == 0) { return 0; }
    else { return n % 10 + sumOfDigits(n / 10); }
}

void writeNChars (char c, int n) {
    if (n > 0) {
        std::cout << c;
        writeNChars(c, n - 1);
    }
}

// Prints an "hour glass" shape indicating recursion
// 1) prints n asterisks
// 2) recursively prints using halfHourGlass(n - 1)
// 3) prints n asterisks (if n > 1)
void halfHourGlass(int n)
{
    writeNChars('*', n); std::cout << '\n';
    if (n > 1) {
        halfHourGlass(n - 1);
        writeNChars('*', n); std::cout << '\n';
    }
}

// Returns the maximum value in an array of integers.
// Assumes array size >= 1
int findMax(int arr[], int arrSize)
{
    assert(arrSize > 0);
    if (arrSize == 1) {
        return arr[arrSize-1];
    } else {
        return std::max(arr[arrSize-1], 
            findMax(arr, arrSize - 1));
    }
}

// Returns the index of the smallest element in the array.
// Assumes array size >= 1
int findMinIndex(int arr[], int arrSize)
{
    assert(arrSize > 0);
    if (arrSize == 1) {
        return arrSize - 1;
    } else {
        int i = arrSize - 1, j = findMinIndex(arr, i);
        return arr[i] <= arr[j] ? i : j;
    }
}

// Helper function for displayArray
void _displayArray (int array[], int size) {
    if (size > 0) {
        _displayArray(array, size - 1);
        std::cout << array[size - 1] << ' ';
    }
}

// Prints an array (in order).
// Assumes array size >= 1
void displayArray (int array[], int size) {
    assert(size > 0);
    _displayArray(array, size);
    std::cout << "\b\n";
}


// helper function for bubbleSort
bool bubbleSortOnce (int arr[], int arrSize) {
    if (arrSize < 2) return false;
    bool didSwap = bubbleSortOnce(arr, arrSize - 1);
    if (arr[arrSize - 1] < arr[arrSize - 2]) {
        // std::cout << "SWAP " << (arrSize - 1) << ", " << (arrSize - 2) << '\n';
        // displayArray(arr, arrSize);
        std::swap(arr[arrSize - 1], arr[arrSize - 2]);
        // displayArray(arr, arrSize);
        return true;
    }
    return didSwap;
}

// Recursive bubblesort.
// works by recursively sorting one "strand" (using bubbleSortOnce)
// until no swaps have been made / array is sorted
void bubbleSort(int arr[], int arrSize)
{
    if (arrSize > 0 && bubbleSortOnce(arr, arrSize)) {
        // std::cout << "STILL NOT SORTED\n";
        // displayArray(arr, arrSize);
        bubbleSort(arr, arrSize - 1);
    } else {
        // std::cout << "SORTED\n";
    }
}

int main()
{
    cout << "sumOfDigits(1234) =\t" << sumOfDigits(1234) << endl;
    halfHourGlass(5);
    const int SIZE = 5;
    int myArr[] = { 23, 64, 99, 1, 8 };
    cout << "Array content:\t";
    displayArray(myArr, SIZE);
    cout << "Max in the array =\t" << findMax(myArr, SIZE) << endl;
    cout << "Index of minimum =\t" << findMinIndex(myArr, SIZE) << endl;
    cout << "Sorting...\n";
    bubbleSort(myArr, SIZE);
    displayArray(myArr, SIZE);
    return 0;
}
