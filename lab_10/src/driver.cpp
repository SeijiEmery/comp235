#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

#define ENFORCE(cond) \
    if (!(cond)) { throw std::runtime_error("enforce() failure: " __FILE__ ": " + __LINE__); }
 
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

        file.seekp(33, std::ios::beg);
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
