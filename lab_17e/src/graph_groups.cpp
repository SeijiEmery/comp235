// graph_groups.cpp
// copyright (c) Seiji Emery, 5/15/18
// https://github.com/SeijiEmery/comp235/tree/master/lab_17e
//
// Reads in graph edge information from stdin using the following line-based
// format, traces the edges to find all connected graphs ("groups"), then
// prints each group to stdout.
//
// input:
//      2 4
//      4 6
//      11 4
//      3 12
//
// output:
//      Group 1: 2 4 6 11
//      Group 2: 3 12
//
// Since reads in data from stdin, invoking without arguments will just consume
// and wait for input forever. 
//
// To run, pipe in data from either a file or generate.cpp:
//      cat <some_file> | make run
//  or  make generator; ./generator <args...> | make run
//
// Sample data is in ../data/connectedGraphs.txt
// For generator args, see generate.cpp
//
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdio>

template <typename T>
void append (std::vector<T>& a, std::vector<T>& b) {
    a.insert(a.end(), b.begin(), b.end());
}

int main (int argc, const char** argv) {
    std::unordered_map<int, int>  vertexOwnership;
    std::vector<std::vector<int>> groupVerts;

    std::string line;
    while (std::getline(std::cin, line)) {
        // std::cout << line << " => ";
        size_t first = line.find_first_not_of(" \t");
        size_t second = line.find_first_not_of(" \t", 
            line.find_first_of(" \t", first+1) + 1);
        int a = atoi(&line[first]);
        int b = atoi(&line[second]);
        if (a == b) {
            continue;
        }
        // std::cout << a << ", " << b << "\n";

        auto itA = vertexOwnership.find(a);
        auto itB = vertexOwnership.find(b);
        auto end = vertexOwnership.end();
        if (itA == end && itB == end) {
            // std::cout << "Adding " << a << ", " << b << '\n';
            // Simplest case: insert vertices into a new group
            int group = groupVerts.size();
            groupVerts.emplace_back();
            groupVerts[group].push_back(a);
            groupVerts[group].push_back(b);
            vertexOwnership[a] = group;
            vertexOwnership[b] = group;
        } else if (itA == end) {
            // std::cout << "Adding " << a << '\n';
            int group = itB->second;
            groupVerts[group].push_back(a);
            vertexOwnership[a] = group;
        } else if (itB == end) {
            // std::cout << "Adding " << b << '\n';
            int group = itA->second;
            groupVerts[group].push_back(b);
            vertexOwnership[b] = group;
        } else {
            // std::cout << "Linking " << a << ", " << b << '\n';
            int groupA = itA->second;
            int groupB = itB->second;
            if (groupA > groupB) {
                std::swap(groupA, groupB);
            }

            if (groupA != groupB) {
                // std::cout << "Merging groups " << groupA << " and " << groupB << '\n';
                // merge groups
                append(groupVerts[groupA], groupVerts[groupB]);
                for (int v : groupVerts[groupB]) {
                    vertexOwnership[v] = groupA;
                }
                // swap-delete group B (retaining packed ordering...)
                groupVerts[groupB].clear();

                int lastGroup = groupVerts.size() - 1;
                if (groupB != lastGroup) {
                    append(groupVerts[groupB], groupVerts[lastGroup]);
                    for (int v : groupVerts[lastGroup]) {
                        vertexOwnership[v] = groupB;
                    }
                }
                groupVerts.pop_back();
            }
        }
    }

    for (size_t i = 0; i < groupVerts.size(); ++i) {
        std::cout << "Group " << (i + 1) << ": ";
        std::sort(groupVerts[i].begin(), groupVerts[i].end());
        for (auto v : groupVerts[i]) {
            std::cout << v << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
