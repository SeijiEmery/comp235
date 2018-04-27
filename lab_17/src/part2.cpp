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
        rotate(&a[0], &a[2], &a[a.size()-1]);
        writeln() << "Rotated (to element 3):   " << a;
    }
    return 0;
}
