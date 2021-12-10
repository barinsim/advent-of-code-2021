#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>


int main()
{
    std::unordered_map<char, char> pairs = { {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'} };
    std::unordered_map<char, int> costs = { {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137} };
    std::string line;
    int res = 0;
    while (std::getline(std::cin, line)) {
        std::stack<char> stk;
        for (char c : line) {
            if (pairs.count(c) > 0) {
                stk.push(c);
            } else {
                char top = stk.top();
                stk.pop();
                if (c != pairs[top]) {
                    res += costs[c];
                    break;
                }
            }
        }
    }
    std::cout << res << std::endl;
}