#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <utility>

struct Fold {
    char axis;
    int cord;
};

int main()
{
    std::set<std::pair<int, int>> points;
    std::string line;
    while (std::getline(std::cin, line) && !line.empty()) {
        std::stringstream ss(line);
        int x, y;
        ss >> x;
        ss.ignore(1);
        ss >> y;
        points.insert({x, y});
    }
    std::vector<Fold> folds;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        ss.ignore(11); // "fold along"
        Fold fold;
        ss >> fold.axis;
        ss.ignore(1); // "="
        ss >> fold.cord;
        folds.push_back(fold);
    }
    for (Fold fold : folds) {
        for (auto it = points.begin(); it != points.end();) {
            if (fold.axis == 'x' && it->first > fold.cord) {
                points.insert({2 * fold.cord - it->first , it->second});
                it = points.erase(it);
            } else if (fold.axis == 'y' && it->second < fold.cord) {
                points.insert({it->first, 2 * fold.cord - it->second});
                it = points.erase(it);
            } else {
                ++it;
            }
        }
        break;
    }
    std::cout << points.size() << std::endl;
}
