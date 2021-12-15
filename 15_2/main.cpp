#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <climits>
#include <sstream>

std::vector<std::vector<int>> readLengths()
{
    std::vector<std::vector<int>> in;
    std::string line;
    while (std::getline(std::cin, line)) {
        in.push_back({});
        std::stringstream ss(line);
        char val;
        while (ss >> val) {
            in.back().push_back(val - '0');
        }
    }
    std::vector<std::vector<int>> lengths(in.size() * 5, std::vector<int>(in[0].size() * 5));
    int xstride = in[0].size();
    int ystride = in.size();
    for (int i = 0; i < in.size(); ++i) {
        for (int j = 0; j < in[0].size(); ++j) {
            for (int row = 0; row < 5; ++row) {
                for (int col = 0; col < 5; ++col) {
                    int val = in[i][j] + row + col;
                    val = val > 9 ? val - 9 : val;
                    lengths[i + row * ystride][j + col * xstride] = val;
                }
            }
        }
    }
    return lengths;
}

int main()
{
    std::multimap<int, std::pair<int, int>> board; // curr shortest dist : node
    std::map<std::pair<int, int>, int> lookup; // node : curr shortest dist
    std::vector<std::vector<int>> lengths = readLengths(); // node : cost for entering
    std::string line;
    int rows = lengths.size();
    int cols = lengths[0].size();
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int dist = row == 0 && col == 0 ? 0 : INT_MAX;
            board.insert({dist, {row, col}});
            lookup.insert({{row, col}, dist});
        }
    }
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
