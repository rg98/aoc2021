//
// aoc07-1.cpp
//
// Advent of Code 2021 Day 07
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

static std::ostream& operator<<(std::ostream& os, const std::vector<int64_t>& v) {
    os << '{'
       << std::accumulate(
              std::next(v.begin()), v.end(), std::to_string(v[0]),
              [](std::string a, int64_t b) { return std::move(a) + " " + std::to_string(b); })
       << "}";
    return os;
}

int main() {
    std::vector<int64_t> crabs;

    // Read input
    std::string s;
    std::cin >> s;
    std::size_t pos{0};
    do {
        if (pos)
            s.erase(0, pos + 1);
        crabs.push_back(std::stoi(s, &pos));
    } while (pos < s.size());

    // Print input
    std::cout << crabs << '\n';

    auto median = crabs.begin() + crabs.size() / 2;
    std::nth_element(crabs.begin(), median, crabs.end());
    auto median_value = crabs[crabs.size() / 2];
    std::cout << "Mean value: " << median_value << '\n';

    // Check median and both neighbors
    auto fuel =
        std::accumulate(crabs.begin(), crabs.end(), 0LL, [&](int64_t a, int b) -> int64_t {
            return a + llabs(median_value - b);
        });
    auto fuel_p =
        std::accumulate(crabs.begin(), crabs.end(), 0LL, [&](int64_t a, int b) -> int64_t {
            return a + llabs(median_value + 1 - b);
        });
    auto fuel_m =
        std::accumulate(crabs.begin(), crabs.end(), 0LL, [&](int64_t a, int b) -> int64_t {
            return a + llabs(median_value - 1 - b);
        });
    if (fuel_p < fuel) {
        median_value++;
        do {
            fuel = fuel_p;
            fuel_p = std::accumulate(
                crabs.begin(), crabs.end(), 0LL,
                [&](int64_t a, int b) -> int64_t { return a + llabs(++median_value + 1 - b); });
        } while (fuel_p < fuel);
    } else if (fuel_m < fuel) {
        median_value--;
        do {
            fuel = fuel_m;
            fuel_m = std::accumulate(
                crabs.begin(), crabs.end(), 0LL,
                [&](int64_t a, int b) -> int64_t { return a + llabs(--median_value + 1 - b); });
        } while (fuel_m < fuel);
    }

    std::cout << "Result: " << fuel << '\n';

    return 0;
}
