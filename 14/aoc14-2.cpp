//
// aoc14-2.cpp
//
// Advent of Code 2021 Day 14
//
// © Ralph Ganszky
//

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using Result = std::map<char, int64_t>;

Result generate_recursive(int level, char a, char b, std::map<int, char>& rules) {
    static std::unordered_map<int, Result> known_results;
    Result result;
    if (level > 0) {
        int key = (int(a) << 8) | int(b);
        char c = rules[key];
        result[c] = 1;
        auto it = known_results.find((level << 16) | (int(a) << 8) | int(c));
        if (it != known_results.end()) {
            for (auto c : it->second)
                result[c.first] += c.second;
        } else {
            auto r1 = generate_recursive(level - 1, a, c, rules);
            for (auto c : r1)
                result[c.first] += c.second;
            known_results[(level << 16) | (int(a) << 8) | int(c)] = r1;
        }
        it = known_results.find((level << 16) | (int(c) << 8) | int(b));
        if (it != known_results.end()) {
            for (auto c : it->second)
                result[c.first] += c.second;
        } else {
            auto r2 = generate_recursive(level - 1, c, b, rules);
            for (auto c : r2)
                result[c.first] += c.second;
        }
    }
    return result;
}

int main() {
    constexpr int Steps = 40;
    std::map<int, char> production;
    std::string product;

    // Read input
    std::cin >> product;
    std::string s;

    std::cin >> s;
    do {
        int pair;
        char gen;
        pair = (int(s[0]) << 8) | int(s[1]);
        std::cin >> s;
        std::cin >> gen;
        production[pair] = gen;
        std::cin >> s;
    } while (!std::cin.eof());

    // Generate Polymer
    Result result;
    for (auto c : product)
        result[c]++;
    for (int i{0}; i < product.size() - 1; i++) {
        auto generated = generate_recursive(Steps, product[i], product[i + 1], production);
        for (auto c : generated)
            result[c.first] += c.second;
    }

    for (auto c : result) {
        std::cout << c.first << " : " << c.second << '\n';
    }

    std::vector<int64_t> counts;
    for (auto cc : result) {
        counts.push_back(cc.second);
    }

    std::sort(counts.begin(), counts.end());

    std::cout << "Result: " << counts.back() - counts.front() << '\n';

    return 0;
}
