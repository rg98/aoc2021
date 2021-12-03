//
// aoc03-2.cpp
//
// Advent of Code 2021 Day 03
//
// © Ralph Ganszky
//

#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

enum class FilterFlag { Oxygen, CO2 };

std::string filter_oxygen_or_co2(const std::vector<std::string>& binaries,
                                 const FilterFlag flag = FilterFlag::Oxygen) {
    std::vector<std::string> input_binaries = binaries;
    std::vector<std::string> filtered_binaries;
    size_t bit_length = binaries[0].size();
    for (auto i{0}; i < bit_length; i++) {
        size_t majority = (input_binaries.size() + 1) / 2;
        auto n = std::count_if(input_binaries.begin(), input_binaries.end(),
                               [&](const auto& s) -> bool { return s[i] == '1'; });
        if (((flag != FilterFlag::Oxygen) && (n < majority)) ||
            ((flag == FilterFlag::Oxygen) && (n >= majority))) {
            std::copy_if(input_binaries.begin(), input_binaries.end(),
                         std::back_inserter(filtered_binaries),
                         [&](auto s) -> bool { return s[i] == '1'; });
        } else {
            std::copy_if(input_binaries.begin(), input_binaries.end(),
                         std::back_inserter(filtered_binaries),
                         [&](auto s) -> bool { return s[i] == '0'; });
        }
        if (filtered_binaries.size() == 1) {
            return filtered_binaries[0];
        }
        input_binaries.clear();
        input_binaries = std::move(filtered_binaries);
    }
    return "";
}

int main() {
    std::vector<std::string> binaries;
    // Read input
    while (!std::cin.eof()) {
        std::string s;
        std::cin >> s;
        binaries.push_back(s);
    }
    int oxygen = std::stoi(filter_oxygen_or_co2(binaries, FilterFlag::Oxygen), nullptr, 2);
    int co2 = std::stoi(filter_oxygen_or_co2(binaries, FilterFlag::CO2), nullptr, 2);
    std::cout << "Result: " << oxygen * co2 << std::endl;

    return 0;
}
