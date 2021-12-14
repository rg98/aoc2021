//
// aoc14-1.cpp
//
// Advent of Code 2021 Day 14
//
// © Ralph Ganszky
//

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::map<std::string, char> production;
    std::string product;

    // Read input
    std::cin >> product;
    std::string s;

    std::cin >> s;
    do {
        std::string pair;
        char gen;
        pair = s;
        std::cin >> s;
        std::cin >> gen;
        production[pair] = gen;
        std::cin >> s;
    } while (!std::cin.eof());

    // Generate Polymer
    std::vector<std::pair<int, char>> inserts;
    std::string new_product;
    std::string pair;
    for (auto step{0}; step < 10; step++) {
        for (auto c : product) {
            pair.push_back(c);
            if (pair.size() == 2) {
                auto prod = production[pair];
                new_product.push_back(prod);
                pair.erase(0, 1);
            }
            new_product.push_back(c);
        }
        product = std::move(new_product);
        pair.clear();
    }

    // Count characters and print out result
    std::map<char, int> char_count;
    for (auto c : product) {
        char_count[c]++;
    }

    std::vector<int> counts;
    for (auto cc : char_count) {
        counts.push_back(cc.second);
    }

    std::sort(counts.begin(), counts.end());

    std::cout << "Result: " << counts.back() - counts.front() << '\n';

    return 0;
}
