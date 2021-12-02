//
// aoc01-1.cpp
//
// Advent of Code 2021 Day 01
//
// © Ralph Ganszky
//

#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::vector<int> scans;
    std::string s;
    // Read input
    while (!std::cin.eof()) {
        std::cin >> s;
        scans.push_back(std::stoi(s));
    }
    // Count increments in scans
    auto keep{std::numeric_limits<int>::max()};
    auto increasing_scans =
        std::accumulate(scans.begin(), scans.end(), 0, [&](int a, int b) -> int {
            if (b > keep)
                a++;
            keep = b;
            return a;
        });

    std::cout << increasing_scans << std::endl;

    return 0;
}
