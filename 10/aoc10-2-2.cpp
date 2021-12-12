//
// aoc10-2.cpp
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

int64_t get_score(std::string oppo) {
    static std::map<char, int64_t> score_map = {{'(', 1}, {'[', 2}, {'{', 3}, {'<', 4}};
    std::reverse(oppo.begin(), oppo.end());
    int64_t score{0};
    for (auto c : oppo)
        score = score * 5 + score_map[c];
    return score;
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
    std::vector<int64_t> scores;
    for (auto& line : code) {
        auto rest = remove_matches(line);
        auto found = false;
        for (auto pair : invalid_pairs) {
            if (rest.find(pair.first) != std::string::npos) {
                found = true;
                break;
            }
        }
        if (!found) {
            scores.push_back(get_score(rest));
            std::cout << "line: " << line << " -> " << rest << '\n';
        }
    }

    std::sort(scores.begin(), scores.end());
    std::cout << "Result: " << scores[scores.size() / 2] << '\n';
    return 0;
}
