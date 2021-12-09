//
// aoc07-2.cpp
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

    // Calculate Average
    int64_t average =
        (std::accumulate(crabs.begin(), crabs.end(), 0) + crabs.size() / 2 + 1) / crabs.size();
    std::cout << "Average value: " << average << '\n';

    auto minmax = std::minmax_element(crabs.begin(), crabs.end());
    auto distance = *minmax.second - *minmax.first;
    std::cout << *minmax.first << ", " << *minmax.second << ", " << distance << '\n';

    // Precalculate fuel consumption for distance
    std::vector<int64_t> fuel_for_distance(1, 0);
    for (int i{1}; i <= distance; i++) {
        fuel_for_distance.push_back(i + fuel_for_distance.back());
    }

    auto result = std::accumulate(crabs.begin(), crabs.end(), 0LL, [&](int64_t a, int64_t b) {
        return a + fuel_for_distance[llabs(average - b)];
    });
    auto result_p = std::accumulate(crabs.begin(), crabs.end(), 0LL, [&](int64_t a, int64_t b) {
        return a + fuel_for_distance[llabs(average + 1 - b)];
    });
    auto result_m = std::accumulate(crabs.begin(), crabs.end(), 0LL, [&](int64_t a, int64_t b) {
        return a + fuel_for_distance[llabs(average - 1 - b)];
    });
    if (result_p < result) {
        average++;
        do {
            result = result_p;
            result_p =
                std::accumulate(crabs.begin(), crabs.end(), 0LL, [&](int64_t a, int64_t b) {
                    return a + fuel_for_distance[llabs(++average - b)];
                });
        } while (result_p < result);
    } else if (result_m < result) {
        average--;
        do {
            result = result_m;
            result_m =
                std::accumulate(crabs.begin(), crabs.end(), 0LL, [&](int64_t a, int64_t b) {
                    return a + fuel_for_distance[llabs(--average - b)];
                });
        } while (result_m < result);
    }

    std::cout << "Result: " << result << '\n';

    return 0;
}
