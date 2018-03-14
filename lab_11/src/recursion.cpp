#include <iostream>
using namespace std;

int sumOfDigits(long n) 
{
    //TO DO
}

void halfHourGlass(int n)
{
    //TO DO
}

//Find array of positive numbers
int findMax(int arr[], int arrSize)
{

    //TO DO
}

//Assume array size is at least 1
int findMinIndex(int arr[], int arrSize)
{
    //TO DO
}

void bubbleSort(int arr[], int arrSize)
{
    //TO DO
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
