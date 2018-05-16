#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdio>

int main (int argc, const char** argv) {
    std::unordered_map<int, int>  vertexOwnership;
    std::vector<std::vector<int>> groupVerts;

    std::string line;
    while (std::getline(std::cin, line)) {
        std::cout << line << " => ";
        size_t first = line.find_first_not_of(" \t");
        size_t second = line.find_first_not_of(" \t", 
            line.find_first_of(" \t", first+1) + 1);

        char *sptr = const_cast<char*>(line.c_str());
        int a = atoi(&line[first]);
        int b = atoi(&line[second]);

        std::cout << a << ", " << b << "\n";;
    }
    return 0;
}
