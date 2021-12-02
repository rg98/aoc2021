//
// aoc02-2.cpp
//
// Advent of Code 2021 Day 02
//
// © Ralph Ganszky
//

#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

struct State {
    int position;
    int depth;
    int aim;
};

int main() {
    State state = {0, 0};
    std::string s;
    // Read input
    std::cin >> s;
    do {
        int value;
        if (s.compare("forward") == 0) {
            std::cin >> value;
            state.position += value;
            state.depth += state.aim * value;
        } else if (s.compare("down") == 0) {
            std::cin >> value;
            state.aim += value;
        } else if (s.compare("up") == 0) {
            std::cin >> value;
            state.aim -= value;
        }
        std::cin >> s;
    } while (!std::cin.eof());
    std::cout << "Position: " << state.position << ", Depth: " << state.depth << '\n';
    std::cout << "Result: " << state.position * state.depth << std::endl;

    return 0;
}
