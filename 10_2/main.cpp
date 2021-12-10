#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>


int main()
{
    std::unordered_map<char, char> pairs = { {'(', ')'}, {'[', ']'}, {'{', '}'}, {'<', '>'} };
    std::unordered_map<char, int> costs = { {')', 1}, {']', 2}, {'}', 3}, {'>', 4} };
    std::vector<long long int> scores;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stack<char> stk;
        long long int score = 0;
        for (char c : line) {
            if (pairs.count(c) > 0) {
                stk.push(c);
            } else {
                char top = stk.top();
                stk.pop();
                if (c != pairs[top]) {
                    stk = std::stack<char>();
                    break;
                }
            }
        }
        while (!stk.empty()) {
            score = score * 5 + costs[pairs[stk.top()]];
            stk.pop();
        }
        if (score > 0) {
            scores.push_back(score);
        }
    }
    std::sort(scores.begin(), scores.end());
    std::cout << scores[scores.size() / 2] << std::endl;
}