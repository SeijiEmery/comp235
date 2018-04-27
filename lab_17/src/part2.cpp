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

template<class T>
void show(T item) 
{ 
    cout << ' ' << item; 
}

int main()
{
    vector<int> a(10);
    cout << "Vector size = " << a.size() << endl;

    cout << "Generate\t";
    generate(a.begin(), a.end(), myRandGenerator);
    for_each(a.begin(), a.end(), show<int>);
    cout << endl;

    cout << "Reversed\t";
    reverse(a.begin(), a.end());
    for_each(a.begin(), a.end(), show<int>);
    cout << endl;

    cout << "Shuffled\t";
    random_shuffle(a.begin(), a.end());
    for_each(a.begin(), a.end(), show<int>);
    cout << endl;

    cout << "Sorted\t\t";
    sort(a.begin(), a.end());
    for_each(a.begin(), a.end(), show<int>);
    cout << endl;   

    cout << "Rotated to element 3\t";
    rotate(a.begin(), &a[2], a.end());
    for_each(a.begin(), a.end(), show<int>);
    cout << endl;

    return 0;
}
