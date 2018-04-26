#include <iostream>
#include <array>
#include <vector>

template <typename Array>
void tryAccess (Array& array, int i) {
    try {
        std::cout << "Accessing array[" << i << "]: ";
        array.at(i) = 10;
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of range error: " << e.what() << '\n';
        return;
    }
    std::cout << "Ok\n";
}

int main () {
    std::vector<int> array (4);
    tryAccess(array, 1);
    tryAccess(array, 4);
    tryAccess(array, -1);
    return 0;
}
