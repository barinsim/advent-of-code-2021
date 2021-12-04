#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <sstream>
#include <array>
#include <unordered_set>

struct Pos {
    int row, col, board;
};

struct Input {
    std::unordered_map<int, std::vector<Pos>> nums;
    std::vector<int> drawnNums;
    int boards;
};

int computeUnmarked(int board,
                  const std::unordered_map<int, std::vector<Pos>>& nums,
                  const std::unordered_set<int>& drawn);

Input readInput();

int main()
{
    Input in = readInput();
    std::vector<std::pair<std::array<int, 5>, std::array<int, 5>>> counters(in.boards);
    std::unordered_set<int> alreadyWon;
    int res = 0;
    for (int drawnIdx = 0; drawnIdx < in.drawnNums.size(); ++drawnIdx) {
        int drawnNum = in.drawnNums[drawnIdx];
        if (!in.nums.contains(drawnNum)) {
            continue;
        }
        auto& positions = in.nums.at(drawnNum);
        bool done = false;
        for (const Pos& pos : positions) {
            auto& rowCnt = counters[pos.board].first[pos.row];
            auto& colCnt = counters[pos.board].second[pos.col];
            ++rowCnt;
            ++colCnt;
            if (rowCnt == 5 || colCnt == 5) {
                std::unordered_set<int> drawnSoFar(in.drawnNums.begin(),
                                                   in.drawnNums.begin() + drawnIdx + 1);
                res = computeUnmarked(pos.board, in.nums, drawnSoFar) * drawnNum;
                done = true;
                break;
            }
        }
        if (done) {
            break;
        }
    }
    std::cout << res << std::endl;
}

int computeUnmarked(int board,
                  const std::unordered_map<int, std::vector<Pos>>& nums,
                  const std::unordered_set<int>& drawn)
{
    int res = 0;
    for (const auto& [num, positions] : nums) {
        for (auto& pos : positions) {
            if (board != pos.board || drawn.contains(num)) {
                continue;
            }
            res += num;
        }
    }
    return res;
}

Input readInput() {
    Input in;
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss(line);
    int val;
    while (ss >> val) {
        in.drawnNums.push_back(val);
        ss.ignore(1);
    }
    std::cin.ignore(1);
    int boardIdx = 0;
    int row = 0, col = 0;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            ++boardIdx;
            continue;
        }
        ss = std::stringstream(line);
        while (ss >> val) {
            in.nums[val].push_back({row, col, boardIdx});
            col = (col + 1) % 5;
        }
        row = (row + 1) % 5;
    }
    in.boards = boardIdx + 1;
    return in;
}
