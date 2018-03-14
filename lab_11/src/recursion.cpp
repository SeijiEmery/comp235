#include <iostream>
#include <cassert>
using namespace std;

int sumOfDigits(long n) 
{
    if (n == 0) { return 0; }
    else { return n % 10 + sumOfDigits(n / 10); }
}

void halfHourGlass(int n)
{
    for (auto i = n; i --> 0; ) { std::cout << '*'; } std::cout << '\n';
    if (n > 1) {
        halfHourGlass(n - 1);
        for (auto i = n; i --> 0; ) { std::cout << '*'; } std::cout << '\n';
    }
}

//Find array of positive numbers
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

//Assume array size is at least 1
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

void displayArray (int array[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << "\b\n";
}

bool bubbleSortElement (int arr[], int arrSize) {
    if (arrSize < 2) return false;
    bool didSwap = bubbleSortElement(arr, arrSize - 1);
    if (arr[arrSize - 1] < arr[arrSize - 2]) {
        std::cout << "SWAP " << (arrSize - 1) << ", " << (arrSize - 2) << '\n';
        displayArray(arr, arrSize);
        std::swap(arr[arrSize - 1], arr[arrSize - 2]);
        displayArray(arr, arrSize);
        return true;
    }
    return didSwap;
}

void bubbleSort(int arr[], int arrSize)
{
    if (arrSize > 0 && bubbleSortElement(arr, arrSize)) {
        std::cout << "STILL NOT SORTED\n";
        displayArray(arr, arrSize);
        bubbleSort(arr, arrSize);
    } else {
        std::cout << "SORTED\n";
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
