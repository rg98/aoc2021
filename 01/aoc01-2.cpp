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
    std::vector<int> accumulated_scans;
    auto range_start = scans.begin();
    auto range_end = range_start;
    std::advance(range_start, 3);
    for (auto i{0}; i < scans.size() - 3; i++) {
        accumulated_scans.push_back(std::accumulate(range_start, range_end, 0));
        std::advance(range_start, 1);
        std::advance(range_end, 1);
    }
    // Count increments in accumulated_scans
    auto keep{std::numeric_limits<int>::max()};
    auto increasing_scans = std::accumulate(accumulated_scans.begin(), accumulated_scans.end(),
                                            0, [&](int a, int b) -> int {
                                                if (b > keep)
                                                    a++;
                                                keep = b;
                                                return a;
                                            });

    std::cout << increasing_scans << std::endl;

    return 0;
}
