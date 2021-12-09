//
// aoc09-1.cpp
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

bool is_low(const int row, const int col, const std::vector<std::vector<int>>& heights) {
    auto height = heights[row][col];
    if (row == 0) {
        if (col == 0) {
            if (height < heights[row][col + 1] && height < heights[row + 1][col])
                return true;
            else
                return false;
        } else if (col == heights[row].size() - 1) {
            if (height < heights[row][col - 1] && height < heights[row + 1][col])
                return true;
            else
                return false;
        } else {
            if (height < heights[row][col + 1] && height < heights[row][col - 1] &&
                height < heights[row + 1][col])
                return true;
            else
                return false;
        }
    } else if (row == heights.size() - 1) {
        if (col == 0) {
            if (height < heights[row][col + 1] && height < heights[row - 1][col])
                return true;
            else
                return false;
        } else if (col == heights[row].size() - 1) {
            if (height < heights[row][col - 1] && height < heights[row - 1][col])
                return true;
            else
                return false;
        } else {
            if (height < heights[row][col + 1] && height < heights[row][col - 1] &&
                height < heights[row - 1][col])
                return true;
            else
                return false;
        }
    } else {
        if (col == 0) {
            if (height < heights[row][col + 1] && height < heights[row + 1][col] &&
                height < heights[row - 1][col])
                return true;
            else
                return false;
        } else if (col == heights[row].size() - 1) {
            if (height < heights[row][col - 1] && height < heights[row + 1][col] &&
                height < heights[row - 1][col])
                return true;
            else
                return false;
        } else {
            if (height < heights[row][col + 1] && height < heights[row][col - 1] &&
                height < heights[row + 1][col] && height < heights[row - 1][col])
                return true;
            else
                return false;
        }
    }
}

int main() {
    std::vector<std::vector<int>> heights;

    // Read input
    std::string s;
    std::cin >> s;
    do {
        heights.push_back(std::vector<int>());
        for (auto c : s)
            heights.back().push_back(c - '0');
        std::cin >> s;
    } while (!std::cin.eof());

    std::cout << "heights:\n" << heights << '\n';

    int result{0};
    for (auto row{0}; row < heights.size(); row++) {
        for (auto col{0}; col < heights[row].size(); col++) {
            if (is_low(row, col, heights)) {
                std::cout << row << ", " << col << '\n';
                result += heights[row][col] + 1;
            }
        }
    }

    std::cout << "Result: " << result << '\n';

    return 0;
}
