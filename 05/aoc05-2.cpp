//
// aoc04-1.cpp
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

// Output operators

struct Point {
    int x, y;
};

struct Line {
    Point a, b;
    operator std::string() const {
        return "(" + std::to_string(a.x) + ", " + std::to_string(a.y) + ") -> (" +
               std::to_string(b.x) + ", " + std::to_string(b.y) + ")";
    }
};

static std::ostream& operator<<(std::ostream& os, const Line l) {
    os << std::string(l);
    return os;
}

using Pixmap = std::vector<std::vector<int>>;

static std::ostream& operator<<(std::ostream& os, const Pixmap& p) {
    for (auto& row : p) {
        os << "-:";
        for (auto& col : row) {
            if (col)
                os << col;
            else
                os << '.';
        }
        os << ":\n";
    }
    return os;
}

static std::ostream& operator<<(std::ostream& os, const std::vector<Line>& v) {
    os << '{'
       << std::accumulate(
              std::next(v.begin()), v.end(), std::string(v[0]),
              [](std::string a, auto& b) { return std::move(a) + "\n" + std::string(b); })
       << "}";
    return os;
}

// Draw line with Bresenham Algorithm

void draw_line(Line line, Pixmap& pixmap) {
    int m = 2 * (line.b.y - line.a.y);
    int slope_error = m - (line.b.x - line.a.x);

    // std::cout << "draw line: " << line.a.x << ',' << line.a.y << " -> " << line.b.x << ','
    //           << line.b.y << ", m = " << m << ", slope_error = " << slope_error << '\n';
    if (slope_error == m) {
        if (line.a.y > line.b.y)
            for (int x = line.a.x, y = line.a.y; y >= line.b.y; y--) {
                // std::cout << "set pixel: " << x << ',' << y << '\n';
                pixmap[y][x]++;
            }
        else
            for (int x = line.a.x, y = line.a.y; y <= line.b.y; y++) {
                // std::cout << "set pixel: " << x << ',' << y << '\n';
                pixmap[y][x]++;
            }
    } else {
        // std::cout << "x = " << line.a.x << ", y = " << line.a.y << '\n';
        for (int x = line.a.x, y = line.a.y; x <= line.b.x; x++) {
            // std::cout << "set pixel: " << x << ',' << y << ", slope_error: " << slope_error
            //           << '\n';
            pixmap[y][x]++;
            slope_error += m;
            if (slope_error >= 0) {
                y++;
                slope_error -= 2 * (line.b.x - line.a.x);
            } else if (m != 0) {
                y--;
                slope_error += 2 * (line.b.x - line.a.x);
            }
        }
    }
}

int main() {
    std::vector<Line> lines;

    // Read input
    std::string s;
    std::cin >> s;
    do {
        Line l;
        std::size_t pos{0};
        l.a.x = std::stoi(s, &pos);
        s.erase(0, pos + 1);
        l.a.y = std::stoi(s, &pos);
        std::cin >> s;
        std::cin >> s;
        pos = 0;
        l.b.x = std::stoi(s, &pos);
        s.erase(0, pos + 1);
        l.b.y = std::stoi(s, &pos);
        // Swap points to get the lower first
        if (l.a.x > l.b.x) {
            Point h = l.b;
            l.b = l.a;
            l.a = h;
            lines.push_back(l);
        } else
            lines.push_back(l);
        std::cin >> s;
    } while (!std::cin.eof());

    // Print input
    std::cout << lines << '\n';

    int min_x = std::numeric_limits<int>::max();
    int max_x = std::numeric_limits<int>::min();
    int min_y = std::numeric_limits<int>::max();
    int max_y = std::numeric_limits<int>::min();
    for (auto& l : lines) {
        if (l.a.x < min_x)
            min_x = l.a.x;
        if (l.a.x > max_x)
            max_x = l.a.x;

        if (l.b.x < min_x)
            min_x = l.b.x;
        if (l.b.x > max_x)
            max_x = l.b.x;

        if (l.a.y < min_y)
            min_y = l.a.y;
        if (l.a.y > max_y)
            max_y = l.a.y;

        if (l.b.y < min_y)
            min_y = l.b.y;
        if (l.b.y > max_y)
            max_y = l.b.y;
    }
    std::cout << "Min x: " << min_x << ", y: " << min_y << '\n';
    std::cout << "Max x: " << max_x << ", y: " << max_y << '\n';

    Pixmap pixmap(max_y + 1, std::vector<int>(max_x + 1, 0));

    for (auto& l : lines) {
        draw_line(l, pixmap);
        // std::cout << pixmap << '\n';
    }

    // std::cout << pixmap << '\n';

    // Count pixels being higher or equal to two
    int count{0};
    for (auto& row : pixmap) {
        count += std::accumulate(row.begin(), row.end(), 0,
                                 [](int a, int b) { return (b >= 2) ? a + 1 : a; });
    }

    std::cout << "Result: " << count << '\n';

    return 0;
}
