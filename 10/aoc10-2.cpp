//
// aoc10-2.cpp
//
// Advent of Code 2021 Day 10
//
// © Ralph Ganszky
//

#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <optional>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

static std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v) {
    os << std::accumulate(std::next(v.begin()), v.end(), v[0], [](std::string a, auto b) {
        return a + '\n' + b;
    }) << '\n';
    return os;
}

static std::ostream& operator<<(std::ostream& os, const std::vector<int64_t>& v) {
    os << std::accumulate(std::next(v.begin()), v.end(), std::to_string(v[0]),
                          [](std::string a, auto b) { return a + ',' + std::to_string(b); });
    return os;
}

// Helper functions

int bracket_error(int c) {
    if (c == ')')
        return 3;
    else if (c == ']')
        return 57;
    else if (c == '}')
        return 1197;
    else if (c == '>')
        return 25137;
    return -1;
}

int current(std::string& line) {
    if (line.size() > 0)
        return line.front();
    return -1;
}

int next(std::string& line) {
    if (line.size() > 0) {
        char c = line.front();
        line.erase(0, 1);
        return c;
    }
    return -1;
}

// Grammar:
//
// START: BRACKET*
// BRACKET: PARENTHESES | SQUARE | BRACES | ANGLE;
// PARENTHESES: '(' BRACKET* ')'
// SQUARE:      '[' BRACKET* ']'
// BRACES:      '{' BRACKET* '}'
// ANGLE:       '<' BRACKET* '>'

int bracket(std::string& line, std::string& oppo, int level = 0) {
    static std::map<int, int> opposite = {{'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'}};
    static std::vector<int> closing = {')', ']', '}', '>'};
    // Read next character
    auto c = next(line);
    oppo.push_back(opposite[c]);
    if (c == -1)
        return 0;
    // If the following character is the opposite of it
    if (current(line) == opposite[c]) {
        // directly read and close the pair and return.
        c = next(line);
        oppo.pop_back();
        if (c == -1)
            return 0;
        return 0;
    } else {
        // start new pair if found.
        do {
            auto rc = bracket(line, oppo, level + 1);
            if (rc)
                return rc;
            // After the new pair the old need to get closed too
            if (current(line) < 0)
                return 0;
        } while (std::find(closing.begin(), closing.end(), current(line)) == closing.end());
        if (current(line) == opposite[c]) {
            c = next(line);
            oppo.pop_back();
            if (c == -1)
                return 0;
            return 0; // bracket(line, level + 1);
        } else {
            return bracket_error(next(line));
        }
    }
}

int parse(std::string& line, std::string& oppo) {
    while (current(line) > 0) {
        return bracket(line, oppo);
    }
    return 0;
}

int64_t get_score(std::string oppo) {
    static std::map<char, int64_t> score_map = {{')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
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
    auto result{0};
    std::vector<int64_t> scores;
    for (auto& line : code) {
        std::string input = line;
        auto score{0};
        std::string oppo;
        do {
            score = parse(input, oppo);
            result += score;
            // std::cout << "oppo: " << oppo << '\n';
        } while (input.size() > 0 && score == 0);
        // auto oppo_score = get_score(oppo);
        if (score == 0) {
            scores.push_back(get_score(oppo));
            std::cout << "line: " << line << ", oppo: " << oppo << '\n';
            std::cout << "scorer: " << scores.back() << '\n';
            std::cout << line << " -> " << score << " -- " << input << '\n';
        } else {
            std::cout << line << " -> " << score << " -- " << input << '\n';
        }
    }

    std::cout << "scores: " << scores << '\n';
    std::sort(scores.begin(), scores.end());
    std::cout << "scores: (" << scores.size() << ") " << scores << '\n';
    std::cout << "Result: " << scores[scores.size() / 2] << '\n';
    return 0;
}
