//
// aoc11-1.cpp
//
// Advent of Code 2021 Day 11
//
// © Ralph Ganszky
//

#include <cstdlib>
#include <iostream>
#include <limits>
#include <numeric>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

using OctopusRow = std::vector<int>;
using Octopuses = std::vector<OctopusRow>;

static std::ostream& operator<<(std::ostream& os, const OctopusRow& v) {
    os << std::accumulate(std::next(v.begin()), v.end(), std::to_string(v[0]),
                          [](std::string a, auto b) { return a + std::to_string(b); });
    return os;
}

static std::ostream& operator<<(std::ostream& os, const Octopuses& v) {
    for (auto& e : v)
        os << e << '\n';
    return os;
}

void increment(Octopuses& octopuses) {
    std::for_each(octopuses.begin(), octopuses.end(), [](OctopusRow& row) {
        std::for_each(row.begin(), row.end(), [](auto& element) { element++; });
    });
}

bool increment_surrounding(const int row, const int col, Octopuses& octopuses) {
    if (row >= 0 && row < octopuses.size() && col >= 0 && col < octopuses[row].size()) {
        octopuses[row][col]++;
        return octopuses[row][col] > 9;
    }
    return false;
}

int flash(Octopuses& octopuses) {
    std::vector<std::pair<int, int>> queue;
    std::vector<std::pair<int, int>> flashed;
    for (int row{0}; row < octopuses.size(); row++) {
        for (int col{0}; col < octopuses[row].size(); col++) {
            if (octopuses[row][col] > 9) {
                auto coordinates = std::make_pair(row, col);
                if (std::find(flashed.begin(), flashed.end(), coordinates) == flashed.end()) {
                    flashed.push_back(coordinates);
                    queue.push_back(coordinates);
                }
            }
        }
    }
    while (queue.size() > 0) {
        auto check = queue.back();
        queue.pop_back();
        for (auto irow{check.first - 1}; irow <= check.first + 1; irow++) {
            for (auto icol{check.second - 1}; icol <= check.second + 1; icol++) {
                if (irow == check.first && icol == check.second)
                    continue;
                if (increment_surrounding(irow, icol, octopuses)) {
                    auto coordinates = std::make_pair(irow, icol);
                    if (std::find(flashed.begin(), flashed.end(), coordinates) ==
                        flashed.end()) {
                        flashed.push_back(coordinates);
                        queue.push_back(coordinates);
                    }
                }
            }
        }
    }
    return flashed.size();
}

void reset_flashed(Octopuses& octopuses) {
    std::for_each(octopuses.begin(), octopuses.end(), [](OctopusRow& row) {
        std::for_each(row.begin(), row.end(), [](auto& element) {
            if (element > 9)
                element = 0;
        });
    });
}

int main() {
    std::vector<std::vector<int>> octopuses;

    // Read input
    std::string s;
    std::cin >> s;
    do {
        octopuses.push_back(std::vector<int>());
        for (auto c : s)
            octopuses.back().push_back(c - '0');
        std::cin >> s;
    } while (!std::cin.eof());

    std::cout << "octopuses:\n" << octopuses << '\n';

    int flashes{0};
    int steps{0};
    do {
        increment(octopuses);
        flashes = flash(octopuses);
        reset_flashed(octopuses);
        steps++;
    } while (flashes < octopuses.size() * octopuses[0].size());

    std::cout << "octopuses:\n" << octopuses << '\n';

    std::cout << "Steps: " << steps << '\n';

    return 0;
}
