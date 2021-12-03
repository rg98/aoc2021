//
// aoc03-1.cpp
//
// Advent of Code 2021 Day 03
//
// © Ralph Ganszky
//

#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> binaries;
    // Read input
    while (!std::cin.eof()) {
        std::string s;
        std::cin >> s;
        binaries.push_back(s);
    }
    uint64_t gamma{0};
    size_t bit_length = binaries[0].size();
    size_t majority = binaries.size() / 2;
    for (auto i{0}; i < bit_length; i++) {
        auto n = std::count_if(binaries.begin(), binaries.end(),
                               [&](const auto& s) -> bool { return s[i] == '1'; });
        if (n > majority)
            gamma = (gamma << 1) | 1;
        else
            gamma <<= 1;
    }
    uint64_t epsilon = ~(std::numeric_limits<uint64_t>::max() << bit_length) ^ gamma;
    std::cout << "Result: " << gamma * epsilon << std::endl;

    return 0;
}
