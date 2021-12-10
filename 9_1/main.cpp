#include <iostream>
#include <vector>
#include <sstream>

int main()
{
    std::vector<std::vector<int>> board;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        board.push_back({});
        char c;
        while (ss >> c) {
            board.back().push_back(c - '0');
        }
    }
    int res = 0;
    int rows = board.size();
    int cols = board[0].size();
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int curr = board[row][col];
            if (col > 0 && board[row][col - 1] <= curr) {
                continue;
            }
            if (col + 1 < cols && board[row][col + 1] <= curr) {
                continue;
            }
            if (row > 0 && board[row - 1][col] <= curr) {
                continue;
            }
            if (row + 1 < rows && board[row + 1][col] <= curr) {
                continue;
            }
            res += curr + 1;
        }
    }
    std::cout << res << std::endl;
}