//
// aoc09-2.cpp
//
// Advent of Code 2021 Day 09
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

static std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    os << '{'
       << std::accumulate(std::next(v.begin()), v.end(), std::to_string(v[0]),
                          [](std::string a, auto b) { return a + " " + std::to_string(b); })
       << "}";
    return os;
}

static std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& v) {
    for (auto& e : v)
        os << e << '\n';
    return os;
}

void boundary_fill(int col, int row, int basin, std::vector<std::vector<int>>& pixel) {
    auto boundary = 0;
    if (pixel[row][col] != boundary && pixel[row][col] != basin) {
        pixel[row][col] = basin;
        if (col < pixel[row].size() - 1)
            boundary_fill(col + 1, row, basin, pixel);
        if (col > 0)
            boundary_fill(col - 1, row, basin, pixel);
        if (row < pixel.size() - 1)
            boundary_fill(col, row + 1, basin, pixel);
        if (row > 0)
            boundary_fill(col, row - 1, basin, pixel);
    }
}

int main() {
    std::vector<std::vector<int>> heights;
    std::vector<int> basins;

    // Read input
    std::string s;
    std::cin >> s;
    do {
        heights.push_back(std::vector<int>());
        for (auto c : s)
            heights.back().push_back((c < '9') ? 1 : 0);
        std::cin >> s;
    } while (!std::cin.eof());

    std::cout << "heights:\n" << heights << '\n';

    // Search clusters of ones separated by zeros.
    auto basin{2};
    for (auto row{0}; row < heights.size(); row++) {
        for (auto col{0}; col < heights[row].size(); col++) {
            if (heights[row][col] == 1) {
                boundary_fill(col, row, basin++, heights);
            }
        }
    }

    std::cout << basin - 1 << " basins\n\n";
    std::cout << "heights:\n" << heights << '\n';

    auto count{0};
    for (int b{2}; b <= basin; b++) {
        count = 0;
        std::for_each(heights.begin(), heights.end(), [&](auto& h) {
            count += std::count_if(h.begin(), h.end(), [&](auto a) { return a == b; });
        });
        basins.push_back(count);
    }
    std::sort(basins.begin(), basins.end(), std::greater<int>());

    std::cout << "Basins: " << basins << '\n';

    if (basins.size() < 3)
        throw std::runtime_error("too few basins");
    auto result = basins[0] * basins[1] * basins[2];

    std::cout << "Result: " << result << '\n';

    return 0;
}
