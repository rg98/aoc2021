//
// aoc06-1.cpp
//
// Advent of Code 2021 Day 06
//
// © Ralph Ganszky
//

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

std::vector<int64_t> calc_one_fish(int days, int n) {
    std::vector<int64_t> n_fishes(1, 1);
    std::vector<int8_t> fishes(1, 0);
    for (auto day{1}; day <= days; day++) {
        auto new_fishes{0};
        for (auto& fish : fishes) {
            if (--fish < 0) {
                fish = 6;
                new_fishes++;
            }
        }
        for (auto i{0LL}; i < new_fishes; i++) {
            fishes.push_back(8);
        }
        n_fishes.push_back(fishes.size());
    }
    std::vector<int64_t> result;
    for (auto day{0}; day < n; day++) {
        result.push_back(n_fishes.back());
        n_fishes.pop_back();
    }
    return result;
}

int main() {
    std::vector<int64_t> fish;

    auto fish_80 = calc_one_fish(80, 7);

    std::cout << "fishs: " << fish_80 << '\n';

    // Read input
    std::string s;
    std::cin >> s;
    std::size_t pos{0};
    do {
        if (pos)
            s.erase(0, pos + 1);
        fish.push_back(std::stoi(s, &pos));
    } while (pos < s.size());

    // Print input
    std::cout << fish << '\n';

    int64_t result =
        std::accumulate(fish.begin(), fish.end(), 0LL,
                        [&](int64_t a, int64_t b) -> int64_t { return a + fish_80[b]; });

    std::cout << "Result: " << result << '\n';

    return 0;
}
