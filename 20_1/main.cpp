#include <iostream>
#include <vector>
#include <cmath>
#include <utility>

char get(int row, int col, std::vector<std::vector<char>>& board, bool inverted)
{
    if (row < 0 || col < 0 || row >= board.size() || col >= board[0].size()) {
        return inverted ? '#' : '.';
    }
    return board[row][col];
}

int toIndex(const std::vector<char>& raw)
{
    int num = 0;
    for (int i = raw.size() - 1; i >= 0; --i) {
        if (raw[i] == '#') {
            num += std::pow(2, raw.size() - i - 1);
        }
    }
    return num;
}

void printBoard(std::vector<std::vector<char>>& b)
{
    for (auto& row : b) {
        for (auto& c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::string line;
    std::getline(std::cin, line);
    std::vector<char> algo(line.begin(), line.end());
    std::vector<std::vector<char>> board;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        board.emplace_back(line.begin(), line.end());
    }
    std::vector<std::pair<int, int>> dirs = {{-1, -1}, {-1, 0}, {-1, 1},
                                             {0, -1}, {0, 0}, {0, 1},
                                             {1, -1}, {1, 0}, {1, 1}};
    const int steps = 2;
    for (int step = 0; step < steps; ++step) {
        int rows = board.size();
        int cols = board[0].size();
        std::vector<std::vector<char>> out(rows + 2, std::vector<char>(cols + 2, '.'));
        for (int row = -1; row <= rows; ++row) {
            for (int col = -1; col <= cols; ++col) {
                std::vector<char> kernel;
                for (auto& [rd, cd] : dirs) {
                    bool inverted = algo[0] == '#' && step % 2 == 1;
                    kernel.push_back(get(row + rd, col + cd, board, inverted));
                }
                char c = algo[toIndex(kernel)];
                out[row + 1][col + 1] = c;
            }
        }
        board = out;
    }
    int ans = 0;
    for (auto& row : board) {
        for (char c : row) {
            if (c == '#') {
                ++ans;
            }
        }
    }
    std::cout << ans << std::endl;
}
