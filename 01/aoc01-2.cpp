//
// aoc01-2.cpp
//
// Advent of Code 2021 Day 01
//
// © Ralph Ganszky
//

#include <iostream>
#include <iterator>
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
    // Accumulate scans
    std::vector<int> tripple_scans;
    auto scans_begin = scans.begin();
    auto scans_end = scans.begin();
    std::advance(scans_end, 3);
    for (auto i{0}; i < scans.size() - 3; i++) {
        tripple_scans.push_back(std::accumulate(scans_begin, scans_end, 0));
        std::advance(scans_begin, 1);
        std::advance(scans_end, 1);
    }
    // Count increments in tripple_scans
    auto keep{std::numeric_limits<int>::max()};
    auto increasing_scans = std::accumulate(tripple_scans.begin(), tripple_scans.end(), 0,
                                            [&](int a, int b) -> int {
                                                if (b > keep)
                                                    a++;
                                                keep = b;
                                                return a;
                                            });

    std::cout << increasing_scans << std::endl;

    return 0;
}
