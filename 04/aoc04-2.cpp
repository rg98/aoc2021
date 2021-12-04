//
// aoc04-2.cpp
//
// Advent of Code 2021 Day 04
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

using ResultTuple = std::tuple<int, int, int>;
using Board = std::vector<std::tuple<int, bool>>;

// Output operators

static std::ostream& operator<<(std::ostream& os, const Board& v) {
    os << '{'
       << std::accumulate(std::next(v.begin()), v.end(),
                          "(" + std::to_string(std::get<0>(v[0])) + ", " +
                              (std::get<1>(v[0]) ? "true)" : "false)"),
                          [](std::string a, std::tuple<int, bool> b) {
                              return std::move(a) + " (" + std::to_string(std::get<0>(b)) +
                                     ", " + (std::get<1>(b) ? "true)" : "false)");
                          })
       << "}";
    return os;
}

std::optional<ResultTuple> check_for_bingo(std::vector<Board>& boards, std::vector<int>& won,
                                           const int board_size) {
    bool got_bingo = false;
    ResultTuple bingo;
    for (auto& board : boards) {
        // std::cout << "Borad " << std::distance(boards.data(), &board) << " " << board <<
        // '\n';
        if (won[std::distance(boards.data(), &board)] == 1)
            continue;
        for (auto i{0}; i < board_size; i++) {
            // Check row
            auto count{0};
            for (auto j{0 + board_size * i}; j < board_size + board_size * i; j++) {
                if (std::get<1>(board[j]))
                    count++;
            }
            if (count == board_size) {
                // std::cout << "Bingo on board " << std::distance(boards.data(), &board)
                //           << " in row " << i << '\n';
                if (!got_bingo) {
                    bingo = std::make_tuple(std::distance(boards.data(), &board), i, -1);
                    got_bingo = true;
                }
                won[std::distance(boards.data(), &board)] = 1;
            }

            // Check col
            count = 0;
            for (auto j{i}; j < board_size * board_size; j += board_size) {
                if (std::get<1>(board[j]))
                    count++;
            }
            if (count == board_size) {
                // std::cout << "Bingo on board " << std::distance(boards.data(), &board)
                //           << " in col " << i << '\n';
                if (!got_bingo) {
                    bingo = std::make_tuple(std::distance(boards.data(), &board), -1, i);
                    got_bingo = true;
                }
                won[std::distance(boards.data(), &board)] = 1;
            }
        }
    }
    if (got_bingo)
        return bingo;
    return std::optional<ResultTuple>();
}

int get_final_result(int n, int board_idx, std::vector<Board>& boards, const int board_size) {
    // std::cout << "Count unmarked numbers: " << boards[board_idx] << '\n';
    auto& board = boards[board_idx];
    auto sum = std::accumulate(board.begin(), board.end(), 0, [](int a, auto b) -> int {
        return a + (std::get<1>(b) ? 0 : std::get<0>(b));
    });

    return n * sum;
}

int main() {
    std::vector<int> numbers;
    std::vector<Board> boards;
    std::vector<int> won;
    constexpr int board_size = 5;

    // Read input
    std::string s;
    std::cin >> s;
    do {
        if (numbers.size() == 0) {
            std::size_t pos{0};
            do {
                if (pos)
                    s.erase(0, pos + 1);
                numbers.push_back(std::stoi(s, &pos));
            } while (pos < s.size());
            // std::cout << "Numbers: " << numbers << '\n';
        } else {
            if (boards.size() == 0 || boards.back().size() == board_size * board_size) {
                boards.emplace_back(std::vector<std::tuple<int, bool>>(
                    1, std::make_tuple(std::stoi(s), false)));
            } else {
                boards.back().emplace_back(std::make_tuple(std::stoi(s), false));
            }
        }
        std::cin >> s;
    } while (!std::cin.eof());

    // std::cout << "Read " << numbers.size() << " numbers and " << boards.size() << "
    // boards.\n";

    // Play bingo
    won.resize(boards.size());
    std::fill(won.begin(), won.end(), 0);
    for (auto n : numbers) {
        // Call n
        for (auto& board : boards) {
            auto it =
                std::find_if(board.begin(), board.end(), [&](std::tuple<int, bool> t) -> bool {
                    return (std::get<0>(t) == n);
                });
            if (it != board.end()) {
                // std::cout << "Found " << n << " in board "
                //           << std::distance(boards.data(), &board) << '\n';
                std::get<1>(*it) = true;
            }
        }

        // Check for bingo
        // std::cout << "Check for bingo for " << n << "!\n";
        auto bingo = check_for_bingo(boards, won, board_size);
        if (bingo.has_value()) {
            // std::cout << "Bingo with " << n << " on board " << std::get<0>(*bingo) <<
            // std::endl; won[std::get<0>(*bingo)] = 1;
            if (std::accumulate(won.begin(), won.end(), 0) == won.size()) {
                std::cout << "Last Bingo: "
                          << get_final_result(n, std::get<0>(*bingo), boards, board_size)
                          << std::endl;
                break;
            }
        }
    }

    return 0;
}
