//
// aoc10-1.cpp
//
// Advent of Code 2021 Day 10
//
// © Ralph Ganszky
//

#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

static std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v) {
    os << std::accumulate(std::next(v.begin()), v.end(), v[0], [](std::string a, auto b) {
        return a + '\n' + b;
    }) << '\n';
    return os;
}

std::string remove_matches(std::string s) {
    std::vector<std::string> pairs = {"()", "[]", "{}", "<>"};
    while (s.size() > 0) {
        size_t replace{0};
        for (auto& pair : pairs) {
            auto pos = s.find(pair);
            if (pos != std::string::npos) {
                s.erase(pos, 2);
                replace++;
            }
        }
        if (replace == 0)
            break;
    }
    return s;
}

int main() {
    std::vector<std::string> code;

    // Read input
    std::string s;
    std::cin >> s;
    do {
        code.push_back(s);
        std::cin >> s;
    } while (!std::cin.eof());

    std::cout << code << '\n';

    // Check code line by line
    std::map<std::string, int> invalid_pairs = {
        {"(]", 57}, {"(}", 1197}, {"(>", 25137}, {"[)", 3}, {"[}", 1197}, {"[>", 25137},
        {"{)", 3},  {"{]", 57},   {"{>", 25137}, {"<)", 3}, {"<]", 57},   {"<}", 1197}};
    auto result{0};
    for (auto& line : code) {
        auto rest = remove_matches(line);
        for (auto pair : invalid_pairs) {
            if (rest.find(pair.first) != std::string::npos) {
                std::cout << "line: " << line << " - " << pair.second << '\n';
                result += pair.second;
                break;
            }
        }
    }

    std::cout << "Result: " << result << '\n';
    return 0;
}
