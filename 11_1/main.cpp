#include <iostream>
#include <sstream>
#include <string>
#include <deque>
#include <algorithm>
#include <utility>
#include <vector>


int main()
{
    std::vector<std::vector<int>> board;
    std::string line;
    while (std::getline(std::cin, line)) {
        board.push_back({});
        std::stringstream ss(line);
        char val;
        while (ss >> val) {
            board.back().push_back(val - '0');
        }
    }
    int rows = board.size();
    int cols = board[0].size();
    int ans = 0;
    for (int step = 0; step < 100; ++step) {
        for (int row = 0; row < rows; ++row) {
            auto addOne = [](auto& x) { ++x; };
            std::for_each(board[row].begin(), board[row].end(), addOne);
        }
        std::deque<std::pair<int, int>> q;
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (board[row][col] > 9) {
                    q.push_back({row, col});
                }
            }
        }
        std::pair<int, int> dirs[] =
         {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
        while (!q.empty()) {
            auto row = q.front().first;
            auto col = q.front().second;
            q.pop_front();
            if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] == 0) {
                continue;
            }
            ++board[row][col];
            if (board[row][col] <= 9) {
                continue;
            }
            ++ans;
            board[row][col] = 0;
            for (auto dir : dirs) {
                q.push_back({row + dir.first, col + dir.second});
            }
        }
    }
    std::cout << ans << std::endl;
}
