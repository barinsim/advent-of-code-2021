#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

int dfs(int y, int x, std::vector<std::vector<int>>& board) 
{
    if (x < 0 || y < 0 || x >= board[0].size() || y >= board.size() || board[y][x] >= 9) {
        return 0;
    }    
    board[y][x] = 9;
    int sum = 0;
    sum += dfs(y + 1, x, board);
    sum += dfs(y - 1, x, board);
    sum += dfs(y, x + 1, board);
    sum += dfs(y, x - 1, board);
    return sum + 1;
}

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
    int rows = board.size();
    int cols = board[0].size();
    std::vector<int> sizes;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int size = dfs(row, col, board);
            sizes.push_back(size);
        }
    }
    std::sort(sizes.rbegin(), sizes.rend());
    std::cout << sizes[0] * sizes[1] * sizes[2] << std::endl;
}