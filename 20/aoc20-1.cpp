//
// aoc20-1.cpp
//
// Advent of Code 2021 Day 20
//
// © Ralph Ganszky
//

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <tuple>
#include <vector>

static std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    os << std::accumulate(
        std::next(v.begin()), v.end(), std::to_string(v[0]),
        [](std::string a, int b) { return std::move(a) + std::to_string(b); });
    return os;
}

int count_neighbourhood(int i, int j, const std::vector<std::vector<int>>& image) {
    int n{0};
    if (image[i - 1][j - 1])
        n |= 0x100;
    if (image[i - 1][j])
        n |= 0x080;
    if (image[i - 1][j + 1])
        n |= 0x040;
    if (image[i][j - 1])
        n |= 0x020;
    if (image[i][j])
        n |= 0x010;
    if (image[i][j + 1])
        n |= 0x008;
    if (image[i + 1][j - 1])
        n |= 0x004;
    if (image[i + 1][j])
        n |= 0x002;
    if (image[i + 1][j + 1])
        n |= 0x001;
    return n;
}

int main() {
    std::vector<int> enhancement_data(512, 0);
    std::vector<std::vector<int>> image;

    constexpr int updates = 2;
    constexpr int extend = 2;

    // Read input
    std::string enhancement_input;
    std::cin >> enhancement_input;

    for (auto i{0}; i < enhancement_input.size(); i++) {
        enhancement_data[i] = (enhancement_input[i] == '#') ? 1 : 0;
    }

    std::string s;
    std::cin >> s;
    auto image_width = s.size() + 2 * (updates + extend);
    for (auto u{0}; u < updates + extend; u++)
        image.emplace_back(std::vector<int>(image_width, 0));
    auto line{image.size()};
    do {
        image.emplace_back(std::vector<int>(image_width, 0));
        for (auto i{0}; i < s.size(); i++) {
            image[line][i + updates + extend] = (s[i] == '#') ? 1 : 0;
        }
        line++;
        std::cin >> s;
    } while (!std::cin.eof());
    for (auto u{0}; u < updates + extend; u++)
        image.emplace_back(std::vector<int>(image_width, 0));

    for (auto line{0}; line < image.size(); line++) {
        std::cout << image[line] << '\n';
    }
    std::cout << '\n';

    for (auto update{0}; update < updates; update++) {
        auto enhanced_image = image;
        for (auto i{1}; i < image.size() - 1; i++) {
            for (auto j{1}; j < image[i].size() - 1; j++) {
                enhanced_image[i][j] = enhancement_data[count_neighbourhood(i, j, image)];
            }
        }
        // Correct extension for infinity when enhancement_data[0] == 1
        if (enhancement_data[0] == 1 && enhancement_data[511] == 0) {
            std::cout << "fix infinity\n";
            enhanced_image[0][0] ^= 1;
            enhanced_image[0][image[0].size() - 1] ^= 1;
            enhanced_image[image.size() - 1][0] ^= 1;
            enhanced_image[image.size() - 1][image[0].size() - 1] ^= 1;
            for (auto i{0}; i < image[0].size(); i++) {
                enhanced_image[0][i] ^= 1;
                enhanced_image[i][0] ^= 1;
                enhanced_image[i][image[0].size() - 1] ^= 1;
                enhanced_image[image[0].size() - 1][i] ^= 1;
            }
        }
        image = enhanced_image;
        for (auto line{0}; line < image.size(); line++) {
            std::cout << image[line] << '\n';
        }
        std::cout << '\n';
    }

    size_t result{0};

    for (auto i{0}; i < image.size(); i++) {
        for (auto j{0}; j < image[i].size(); j++) {
            result += image[i][j];
        }
    }

    std::cout << "Result: " << result << std::endl;

    return 0;
}
