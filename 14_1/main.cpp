#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <sstream>

int main()
{
    std::string tmplt;
    std::cin >> tmplt;
    std::string line;
    std::unordered_map<char, std::unordered_map<char, char>> rules;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string pair;
        ss >> pair;
        ss.ignore(4); // " -> "
        char c;
        ss >> c;
        rules[pair[0]][pair[1]] = c;
    }
    int steps = 10;
    while (steps--) {
        std::string tmp;
        for (int i = 1; i < tmplt.size(); ++i) {
            tmp.push_back(tmplt[i - 1]);
            if (rules.contains(tmplt[i - 1]) &&
                rules[tmplt[i - 1]].contains(tmplt[i])) {
                tmp.push_back(rules[tmplt[i - 1]][tmplt[i]]);
            }
        }
        tmp.push_back(tmplt.back());
        tmplt = tmp;
    }
    std::unordered_map<char, int> count;
    for (char c : tmplt) {
        ++count[c];
    }
    auto comp = [](auto& a, auto& b) { return a.second < b.second; };
    int max = std::max_element(count.begin(), count.end(), comp)->second;
    int min = std::min_element(count.begin(), count.end(), comp)->second;
    std::cout << max - min << std::endl;
}
