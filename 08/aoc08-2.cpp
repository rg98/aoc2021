//
// aoc08-2.cpp
//
// Advent of Code 2021 Day 08
//
// © Ralph Ganszky
//

#include <cstdlib>
#include <iostream>
#include <iterator>
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

// Digits:
//
//  aaaa
// b    c
// b    c
//  dddd
// e    f
// e    f
//  gggg
//
// 0 -> abcefg  (len: 6) -> (6, 7, 8) -> 0 | 6 | 9
// 1 -> cf      (len: 2) -> 0
// 2 -> acdeg   (len: 5) -> (3, 4, 5) -> 2 | 3 | 5
// 3 -> acdfg   (len: 5) -> (3, 4, 5) -> 2 | 3 | 5
// 4 -> bcdf    (len: 4) -> 2
// 5 -> abdfg   (len: 5) -> (3, 4, 5) -> 2 | 3 | 5
// 6 -> abdefg  (len: 6) -> (6, 7, 8) -> 0 | 6 | 9
// 7 -> acf     (len: 3) -> 1
// 8 -> abcdefg (len: 7) -> 9
// 9 -> abcdfg  (len: 6) -> (6, 7, 8) -> 0 | 6 | 9
//
// Deduction by input:
// Map
// be cfbegad cbdgef fgaecd cgeb fdcge agebfd fecdb fabcd edb
// sort by length ->
// be edb cgeb fdcge fecdb fabcd cbdgef fgaecd agebfd cfbegad
//  1   7    4                                              8
//
// a = 7 - 1
// a, d, g in all five character strings -> a, d, g -> d, g (because a is known)
// 4 - 1 -> b, d -> d is one of the above -> d, g, b (four characters known)
// c is missing in one six character words -> c, f (six characters known)
// the remaining character need to be e.

std::vector<std::string> analyze_digits(std::vector<std::string>& digits) {
    // Sort digits by length:
    std::sort(digits.begin(), digits.end(),
              [](auto& a, auto& b) -> bool { return a.size() < b.size(); });

    // Solve by lenght
    std::string one = digits[0];
    std::sort(one.begin(), one.end());
    std::string seven = digits[1];
    std::sort(seven.begin(), seven.end());
    std::string four = digits[2];
    std::sort(four.begin(), four.end());
    std::string eight = digits[9];
    std::sort(eight.begin(), eight.end());
    // std::cout << "one:   " << one << '\n';
    // std::cout << "seven: " << seven << '\n';
    // std::cout << "four:  " << four << '\n';
    // std::cout << "eight: " << eight << '\n';

    std::string cand_two = digits[3];
    std::sort(cand_two.begin(), cand_two.end());
    std::string cand_three = digits[4];
    std::sort(cand_three.begin(), cand_three.end());
    std::string cand_five = digits[5];
    std::sort(cand_five.begin(), cand_five.end());

    std::string cand_zero = digits[6];
    std::sort(cand_zero.begin(), cand_zero.end());
    std::string cand_six = digits[7];
    std::sort(cand_six.begin(), cand_six.end());
    std::string cand_nine = digits[8];
    std::sort(cand_nine.begin(), cand_nine.end());

    // Deduct segments
    std::string segment_a;
    std::set_difference(seven.begin(), seven.end(), one.begin(), one.end(),
                        std::back_inserter(segment_a));
    // std::cout << "segment_a: " << segment_a << '\n';
    std::string segment_dg_1;
    std::set_intersection(cand_two.begin(), cand_two.end(), cand_three.begin(),
                          cand_three.end(), std::back_inserter(segment_dg_1));
    // std::cout << "segment_dg_1: " << segment_dg_1 << '\n';
    std::string segment_dg_2;
    std::set_intersection(segment_dg_1.begin(), segment_dg_1.end(), cand_five.begin(),
                          cand_five.end(), std::back_inserter(segment_dg_2));
    // std::cout << "segment_dg_2: " << segment_dg_2 << '\n';
    std::string segment_dg;
    std::set_difference(segment_dg_2.begin(), segment_dg_2.end(), segment_a.begin(),
                        segment_a.end(), std::back_inserter(segment_dg));
    // std::cout << "segment_dg: " << segment_dg << '\n';
    std::string segment_bd;
    std::set_difference(four.begin(), four.end(), one.begin(), one.end(),
                        std::back_inserter(segment_bd));
    // std::cout << "segment_bd: " << segment_bd << '\n';
    std::string segment_d;
    std::set_intersection(segment_dg.begin(), segment_dg.end(), segment_bd.begin(),
                          segment_bd.end(), std::back_inserter(segment_d));
    // std::cout << "segment_d: " << segment_d << '\n';
    std::string segment_g;
    std::set_difference(segment_dg.begin(), segment_dg.end(), segment_d.begin(),
                        segment_d.end(), std::back_inserter(segment_g));
    // std::cout << "segment_g: " << segment_g << '\n';
    std::string segment_b;
    std::set_difference(segment_bd.begin(), segment_bd.end(), segment_d.begin(),
                        segment_d.end(), std::back_inserter(segment_b));
    // std::cout << "segment_b: " << segment_b << '\n';
    std::string segment_ce_1;
    std::set_symmetric_difference(cand_zero.begin(), cand_zero.end(), cand_six.begin(),
                                  cand_six.end(), std::back_inserter(segment_ce_1));
    // std::cout << "segment_ce_1: " << segment_ce_1 << '\n';
    std::string segment_ce_2;
    std::set_symmetric_difference(cand_zero.begin(), cand_zero.end(), cand_nine.begin(),
                                  cand_nine.end(), std::back_inserter(segment_ce_2));
    // std::cout << "segment_ce_2: " << segment_ce_2 << '\n';
    std::string segment_ce;
    std::set_union(segment_ce_1.begin(), segment_ce_1.end(), segment_ce_2.begin(),
                   segment_ce_2.end(), std::back_inserter(segment_ce));
    // std::cout << "segment_ce: " << segment_ce << '\n';
    auto pos_a = segment_ce.find(segment_a);
    auto pos_b = segment_ce.find(segment_b);
    auto pos_d = segment_ce.find(segment_d);
    auto pos_g = segment_ce.find(segment_g);
    if (pos_a != std::string::npos) {
        segment_ce.erase(pos_a, 1);
    } else if (pos_b != std::string::npos) {
        segment_ce.erase(pos_b, 1);
    } else if (pos_d != std::string::npos) {
        segment_ce.erase(pos_d, 1);
    } else if (pos_g != std::string::npos) {
        segment_ce.erase(pos_g, 1);
    }
    // std::cout << "segment_ce: " << segment_ce << '\n';

    std::string segment_c;
    std::set_intersection(segment_ce.begin(), segment_ce.end(), one.begin(), one.end(),
                          std::back_inserter(segment_c));
    // std::cout << "segment_c: " << segment_c << '\n';
    std::string segment_f;
    std::set_difference(one.begin(), one.end(), segment_c.begin(), segment_c.end(),
                        std::back_inserter(segment_f));
    // std::cout << "segment_f: " << segment_f << '\n';
    std::string segment_e;
    std::set_difference(segment_ce.begin(), segment_ce.end(), segment_c.begin(),
                        segment_c.end(), std::back_inserter(segment_e));
    // std::cout << "segment_e: " << segment_e << '\n';

    // Solve by deduction
    std::string zero = segment_a + segment_b + segment_c + segment_e + segment_f + segment_g;
    std::sort(zero.begin(), zero.end());
    std::string two = segment_a + segment_c + segment_d + segment_e + segment_g;
    std::sort(two.begin(), two.end());
    std::string three = segment_a + segment_c + segment_d + segment_f + segment_g;
    std::sort(three.begin(), three.end());
    std::string five = segment_a + segment_b + segment_d + segment_f + segment_g;
    std::sort(five.begin(), five.end());
    std::string six = segment_a + segment_b + segment_d + segment_e + segment_f + segment_g;
    std::sort(six.begin(), six.end());
    std::string nine = segment_a + segment_b + segment_c + segment_d + segment_f + segment_g;
    std::sort(nine.begin(), nine.end());
    // std::cout << "zero:  " << zero << '\n';
    // std::cout << "two:   " << two << '\n';
    // std::cout << "three: " << three << '\n';
    // std::cout << "five:  " << five << '\n';
    // std::cout << "six:   " << six << '\n';
    // std::cout << "nine:  " << nine << '\n';

    // Choose zero, six and nine
    if (zero == cand_zero)
        zero = cand_zero;
    else if (zero == cand_six)
        zero = cand_six;
    else if (zero == cand_nine)
        zero = cand_nine;
    else
        throw std::runtime_error("Internal error: could not find zero!");
    if (six == cand_zero)
        six = cand_zero;
    else if (six == cand_six)
        six = cand_six;
    else if (six == cand_nine)
        six = cand_nine;
    else
        throw std::runtime_error("Internal error: could not find six!");
    if (nine == cand_zero)
        nine = cand_zero;
    else if (nine == cand_six)
        nine = cand_six;
    else if (nine == cand_nine)
        nine = cand_nine;
    else
        throw std::runtime_error("Internal error: could not find nine!");

    // Choose two, three and five
    if (two == cand_two)
        two = cand_two;
    else if (two == cand_three)
        two = cand_three;
    else if (two == cand_five)
        two = cand_five;
    else
        throw std::runtime_error("Internal error: could not find two!");
    if (three == cand_two)
        three = cand_two;
    else if (three == cand_three)
        three = cand_three;
    else if (three == cand_five)
        three = cand_five;
    else
        throw std::runtime_error("Internal error: could not find three!");
    if (five == cand_two)
        five = cand_two;
    else if (five == cand_three)
        five = cand_three;
    else if (five == cand_five)
        five = cand_five;
    else
        throw std::runtime_error("Internal error: could not find five!");

    return {zero, one, two, three, four, five, six, seven, eight, nine};
}

int64_t code2number(std::vector<std::string>& output,
                    std::vector<std::string>& analyzed_digits) {
    int64_t number{0};
    std::cout << output << '\n';
    for (auto& code : output) {
        std::sort(code.begin(), code.end());
        int64_t digit =
            std::distance(analyzed_digits.begin(),
                          std::find(analyzed_digits.begin(), analyzed_digits.end(), code));
        std::cout << " " << digit << '\n';
        number = number * 10 + digit;
    }
    std::cout << number << '\n';
    return number;
}

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

    int64_t result{0};

    for (auto i{0}; i < digits.size(); i++) {
        auto analyzed_digits = analyze_digits(digits[i]);
        std::cout << analyzed_digits << '\n';
        result += code2number(output[i], analyzed_digits);
    }

    std::cout << "Result: " << result << '\n';

    return 0;
}
