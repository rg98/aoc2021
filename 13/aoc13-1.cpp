//
// aoc12-1.cpp
//
// Advent of Code 2021 Day 12
//
// © Ralph Ganszky
//

#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

static std::ostream& operator<<(std::ostream& os, const std::vector<std::pair<int, int>>& v) {
    std::for_each(v.begin(), v.end(),
                  [&](auto e) { os << e.first << ", " << e.second << '\n'; });
    return os;
}

void fold(const int x, const int y, std::vector<std::pair<int, int>>& dots) {
    if (x && !y) {
        std::for_each(dots.begin(), dots.end(),
                      [&](auto& dot) { dot.first = x - abs(dot.first - x); });
    } else if (!x && y) {
        std::for_each(dots.begin(), dots.end(),
                      [&](auto& dot) { dot.second = y - abs(dot.second - y); });
    } else {
        throw std::runtime_error("folds are only allowed along the axes!");
    }
}

int main() {
    std::vector<std::pair<int, int>> dots;
    std::vector<std::pair<int, int>> folds;
    std::string s;

    // Read input
    std::cin >> s;
    std::size_t pos{0};
    do {
        if (s == "fold") {
            std::cin >> s;
            std::cin >> s;
            auto axis = s[0] - 'x';
            auto n = std::stoi(s.substr(2));
            if (axis)
                folds.emplace_back(std::make_pair(0, n));
            else
                folds.emplace_back(std::make_pair(n, 0));
            auto x = folds.back().first;
            auto y = folds.back().second;
            std::cout << "fold: " << x << ", " << y << '\n';
        } else {
            auto x = std::stoi(s, &pos);
            s.erase(0, pos + 1);
            auto y = std::stoi(s, &pos);
            dots.emplace_back(std::make_pair(x, y));
            std::cout << x << ", " << y << '\n';
        }
        std::cin >> s;
    } while (!std::cin.eof());

    // Fold first fold
    auto x = folds.front().first;
    auto y = folds.front().second;
    fold(x, y, dots);

    // Count dots
    std::cout << '\n';
    std::cout << "Dots on sheet: " << dots.size() << '\n';
    std::sort(dots.begin(), dots.end());
    auto end = std::unique(dots.begin(), dots.end());
    dots.erase(end, dots.end());
    std::cout << dots << '\n';
    std::cout << "Dots remaining: " << dots.size() << '\n';

    return 0;
}
