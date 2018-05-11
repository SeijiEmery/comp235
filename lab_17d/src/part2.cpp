#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>

template <typename T, typename F>
void bubbleSort (std::vector<T>& values, const F& less) {
    for (size_t i = 0; i < values.size(); ++i) {
        for (size_t j = i; j < values.size(); ++j) {
            if (!less(values[i], values[j])) {
                std::swap(values[i], values[j]);
            }
        }
    }
}

template <typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& values) {
    for (const auto& v : values) {
        os << v << ' ';
    }
    return os;
}

int main () {
    srand(time(nullptr));

    //
    // Part 1
    //

    std::vector<int> values (20);
    std::generate(values.begin(), values.end(), [](){ return rand() % 50; });
    std::cout << "\nGenerated values:\n" << values << '\n';

    bubbleSort(values, [](int a, int b) { return a < b; });
    std::cout << "\nSorted (less):\n" << values << '\n';

    bubbleSort(values, [](int a, int b) { return a > b; });
    std::cout << "\nSorted (greater):\n" << values << '\n';

    //
    // Part 2
    //

    int a = 0, b = 1;
    std::generate(values.begin(), values.end(), [&a,&b](){
        int sum = a + b;
        return a = b, b = sum, a;
    });
    std::cout << "\nFibonacci:\n" << values << '\n';

    std::cout << '\n';
    return 0;
}
