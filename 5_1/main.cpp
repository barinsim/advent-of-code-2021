#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>

struct Line {
    int x1, x2, y1, y2;
};

int main() {
    std::vector<Line> lines;
    std::string l;
    while (std::getline(std::cin, l)) {
        if (l.empty()) {
            continue;
        }
        std::stringstream ss(l);
        Line line;
        ss >> line.x1;
        ss.ignore(1);
        ss >> line.y1;
        ss.ignore(4);
        ss >> line.x2;
        ss.ignore(1);
        ss >> line.y2;
        lines.push_back(line);
    }
    std::unordered_map<int, std::unordered_map<int, int>> points; // x -> y -> cnt
    for (Line line : lines) {
        if (line.x1 != line.x2 && line.y1 != line.y2) {
            continue;
        }
        while (line.x1 != line.x2 || line.y1 != line.y2 ) {
            ++points[line.x1][line.y1];
            if (line.x1 != line.x2) {
                line.x1 += line.x1 < line.x2 ? 1 : -1;
            }
            if (line.y1 != line.y2) {
                line.y1 += line.y1 < line.y2 ? 1 : -1;
            }
        }
        ++points[line.x2][line.y2];
    }
    int res = 0;
    for (const auto& [x, m] : points) {
        for (const auto& [y, cnt] : m) {
            res += cnt > 1;
        }
    }
    std::cout << res << std::endl;
}
