#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <climits>
#include <sstream>

int main()
{
    std::multimap<int, std::pair<int, int>> board; // curr shortest dist : node
    std::map<std::pair<int, int>, int> lookup; // node : curr shortest dist
    std::vector<std::vector<int>> lengths; // node : cost for entering
    std::string line;
    for (int row = 0; std::getline(std::cin, line); ++row) {
        lengths.push_back({});
        std::stringstream ss(line);
        char val;
        for (int col = 0; ss >> val; ++col) {
            int dist = row == 0 && col == 0 ? 0 : INT_MAX;
            board.insert({dist, {row, col}});
            lookup.insert({{row, col}, dist});
            lengths[row].push_back(val - '0');
        }
    }
    int rows = lengths.size();
    int cols = lengths[0].size();
    int ans;
    while (!board.empty()) {
        auto it = board.begin();
        int y = it->second.first;
        int x = it->second.second;
        int curr = it->first;
        if (y == rows - 1 && x == cols - 1) {
            ans = curr;
            break;
        }
        board.erase(it);
        lookup.erase({y, x});
        std::vector<std::pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto dir : dirs) {
            int yd = dir.first;
            int xd = dir.second;
            if (!lookup.contains({y + yd, x + xd}) || y + yd < 0 || y + yd >= rows || x + xd < 0 || x + xd >= cols) {
                continue;
            }
            int newDist = curr + lengths[y + yd][x + xd];
            if (newDist < lookup[{y + yd, x + xd}]) {
                lookup[{y + yd, x + xd}] = newDist;
                auto pred = [&](auto& param) { return param.second == std::pair<int, int>(y + yd, x + xd); };
                auto it = std::find_if(board.begin(), board.end(), pred);
                board.erase(it);
                board.insert({newDist, {y + yd, x + xd}});
            }
        }
    }
    std::cout << ans << std::endl;
}
