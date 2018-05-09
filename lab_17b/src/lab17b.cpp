#include <set>
#include <map>
#include <iterator> //for ostream_iterator
#include <regex>
#include <sstream>
#include <string>
#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    string gdp = { "GDP is commonly used as an indicator of the economic\
                    health of a country, as well as a gauge of a country's \
                    standard of living. Since the mode of measuring GDP is\
                     uniform from country to country, GDP can be used to \
                     compare the productivity of various countries with a \
                     high degree of accuracy. Adjusting for inflation from \
                     year to year allows for the seamless comparison of \
                     current GDP measurements with measurements from previous \
                     years or quarters. In this way, a nation's GDP from any \
                     period can be measured as a percentage relative to \
                     previous years or quarters. When measured in this way, \
                     GDP can be tracked over long spans of time and used in \
                     measuring a nation's economic growth or decline, as well \
                     as in determining if an economy is in recession. GDP's \
                     popularity as an economic indicator in part stems from \
                     its measuring of value added through economic processes. \
                     For example, when a ship is built, GDP does not reflect \
                     the total value of the completed ship, but rather the \
                     difference in values of the completed ship and of the \
                     materials used in its construction. Measuring total \
                     value instead of value added would greatly reduce GDP's \
                     functionality as an indicator of progress or decline, \
                     specifically within individual industries and sectors. \
                     Proponents of the use of GDP as an economic measure \
                     tout its ability to be broken down in this way and \
                     thereby serve as an indicator of the failure or success \
                     of economic policy as well. For example, from 2004 to \
                     2014 France's GDP increased by 53.1%, while Japan's \
                     increased by 6.9% during the same period." };

    //
    // PART 1
    //                    

    //Convert everthing to lowercase
    for (int i = 0; i < gdp.length(); i++)
        gdp[i] = tolower(gdp[i]);

    //Get rid of everything except a-z or space
    regex e("[^a-zA-Z\\s]"); 
    gdp = regex_replace (gdp, e, "");

    {
        std::set<std::string> words;
        std::istringstream ss { gdp };
        std::string word;
        while (std::getline(ss, word, ' ')) {
            words.insert(word);
        }
        words.erase(words.find(""));

        std::copy(
            words.begin(), words.end(), 
            std::ostream_iterator<string>(std::cout, " "));
        cout << std::endl;
    }

    //
    // PART 2
    //
    {
        std::cout << "\nWord counts:\n";
        std::unordered_map<std::string, size_t> words;
        std::istringstream ss { gdp };
        std::string word;
        while (std::getline(ss, word, ' ')) {
            auto it = words.find(word);
            if (it != words.end()) {
                ++words[word];
            } else {
                words.emplace(word, 1);
            }
        }
        words.erase(words.find(""));

        for (auto& kv : words) {
            std::cout << kv.first << ": " << kv.second << '\n';
        }
    }
    return 0;
}
