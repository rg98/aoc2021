//
// aoc08-1.cpp
//
// Advent of Code 2021 Day 08
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

static std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v) {
    os << '{'
       << std::accumulate(std::next(v.begin()), v.end(), v[0],
                          [](std::string a, std::string b) { return a + " " + b; })
       << "}";
    return os;
}

static std::ostream& operator<<(std::ostream& os,
                                const std::vector<std::vector<std::string>>& v) {
    for (auto& e : v)
        os << e << '\n';
    return os;
}

int count_len(const std::vector<int> lengths, std::vector<std::string>& digits) {
    int cnt{0};
    for (auto& digit : digits)
        if (std::find(lengths.begin(), lengths.end(), (int)digit.size()) != lengths.end())
            cnt++;
    return cnt;
};

int main() {
    std::vector<std::vector<std::string>> digits;
    std::vector<std::vector<std::string>> output;

    // Read input
    std::string s;
    while (!std::cin.eof()) {
        digits.emplace_back(std::vector<std::string>());
        for (auto i{0}; i < 10; i++) {
            std::cin >> s;
            if (std::cin.eof()) {
                digits.pop_back();
                break;
            }
            digits.back().push_back(s);
        }
        if (std::cin.eof())
            break;
        std::cin >> s;
        if (s != "|") {
            throw std::runtime_error("Unexpected input: " + s);
        }
        output.emplace_back(std::vector<std::string>());
        for (auto i{0}; i < 4; i++) {
            std::cin >> s;
            output.back().push_back(s);
        }
    }

    auto result = std::accumulate(output.begin(), output.end(), 0, [](int a, auto& b) {
        return a + count_len({2, 3, 4, 7}, b);
    });

    std::cout << "Result: " << result << '\n';

    return 0;
}
