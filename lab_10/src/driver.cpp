#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

#define ENFORCE(cond) \
    if (!(cond)) { throw std::runtime_error("enforce() failure: " __FILE__ ": " + __LINE__); }

bool seekTo (std::fstream &file, std::string search) {
    std::string line; size_t offset = 0;
    file.seekp(0, std::ios::beg);
    while (std::getline(file, line)) {
        auto loc = line.find(search);
        if (loc != std::string::npos) {
            file.seekp(offset + loc + search.size(), std::ios::beg);
            return true;
        }
        offset += line.size();
    }
    return false;

    // std::cout << file.tellg() << ", " << file.tellp() << '\n';

    // char c;
    // while (file.good() && (file >> c, c) != search[0]) {
    //     for (size_t i = 1; i < search.size(); ++i) {
    //         if (!file.good()) return false;
    //         if ((file >> c, c) != search[i]) goto retry;
    //     }
    //     std::cout << file.tellg() << ", " << file.tellp() << '\n';
    //     file.seekp(file.tellg(), std::ios::beg);
    //     // file.seekp(file.tellg(), std::ios::beg);
    //     return true;
    // retry:;
    // }
    // return false;
}

 
int main (int argc, const char** argv) {
    std::cout << argv[0] << '\n';
    std::cout << __FILE__ "\n";

    // Part 1
    {
        std::ofstream file { "vegetables.txt" };
        file << "asparagus#$23.34\n";
    }
    {
        std::ifstream file { "vegetables.txt" };
        std::string vegetable; ENFORCE(std::getline(file, vegetable, '#'));
        char   ds   ; file >> ds;
        double price; file >> price;

        std::cout << vegetable << ": ";
        std::cout << ds << price << '\n';
    }

    // Part 2:
    // Re-open the file, this time as an random access file. 
    // Using seekp, position the file position pointer at the end of the file, and add two more items into the file. 
    // At the end, check your file content and it should contain:
    //      asparagus#$23.34
    //      black truffles#$230.99
    //      angus beef#$88.23
    // Using seekp, and for “black truffles”, position the file position pointer at position after the dollar sign, 
    // and change the price to 330.50
    {
        std::fstream file { "vegetables.txt", std::ios::in | std::ios::out };
        file.seekp(0, std::ios::end);
        file << "black truffles#$230.99\n";
        file << "angus beef#$88.23\n";

        ENFORCE(seekTo(file, "black truffles#$"));
        file << "330.50";

        std::cout << '\n';

        // Display output
        file.seekg(0, std::ios::beg);

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << '\n';
        }


        // int i = 0;
        // while (file.good()) {
        //     std::cout << i++ << ' ';
        //     std::string vegetable; ENFORCE(std::getline(file, vegetable, '#'));
        //     char   ds   ; file >> ds;
        //     double price; file >> price;
        //     std::cout << vegetable << ": ";
        //     std::cout << ds << price;
        // }
    }
    return 0;
}
