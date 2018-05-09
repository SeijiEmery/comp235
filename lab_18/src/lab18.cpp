#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>

template <typename T>
void bubbleSort (std::vector<T>& values, bool (*less)(const T&, const T&)) {
    for (size_t i = 0; i < values.size(); ++i) {
        for (size_t j = i; j < values.size(); ++j) {
            if (!less(values[i], values[j])) {
                std::swap(values[i], values[j]);
            }
        }
    }
}

template <typename T>
bool compareLess (const T& a, const T& b) {
    return a < b;
}
template <typename T>
bool compareGreater (const T& a, const T& b) {
    return a > b;
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

    std::vector<int> values (20);
    std::generate(values.begin(), values.end(), [](){ return rand() % 50; });
    std::cout << "\nGenerated values:\n" << values << '\n';

    bubbleSort(values, &compareLess);
    std::cout << "\nSorted (less):\n" << values << '\n';

    bubbleSort(values, &compareGreater);
    std::cout << "\nSorted (greater):\n" << values << '\n';

    std::cout << '\n';
    return 0;
}
