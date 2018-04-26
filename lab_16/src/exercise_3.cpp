#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>


struct ProductNotFoundException : public std::runtime_error {
    ProductNotFoundException (const std::string& msg)
        : std::runtime_error(msg) {}
};

int getProductID (int* ids, std::string* names, size_t numProducts, const std::string& target) {
    for (int i = 0; i < numProducts; ++i) {
        if (names[i] == target) {
            return ids[i];
        }
    }
    throw ProductNotFoundException(
        (std::stringstream() << "Could not find product: " << target << '\n').str());
}
void displayProductId (int* ids, std::string* names, size_t numProducts, const std::string& target) {
    try {
        std::cout << "Product '" << target << "' => " << getProductID(ids, names, numProducts, target) << "\n";
    } catch (const ProductNotFoundException& e) {
        std::cerr << e.what() << '\n';
    }
}

int main () {
    int products[]      = { 4, 5, 8, 10, 13 };
    std::string names[] = { "computer", "flash drive", "mouse", "printer", "camera" };

    #define DISPLAY_PRODUCT(x) displayProductId(&products[0], &names[0], 5, x)
    DISPLAY_PRODUCT("mouse");
    DISPLAY_PRODUCT("camera");
    DISPLAY_PRODUCT("laptop");
    return 0;
}
