#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <sstream>

#define ll long long int

int main()
{
    std::unordered_map<std::string, ll> tmplt; // pair -> count
    std::string raw;
    std::cin >> raw;
    for (int i = 1; i < raw.size(); ++i) {
        std::string pair(2, '\0');
        pair[0] = raw[i - 1];
        pair[1] = raw[i];
        ++tmplt[pair];
    }
    std::string line;
    std::unordered_map<std::string, char> rules;
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
        rules[pair] = c;
    }
    int steps = 40;
    while (steps--) {
        std::unordered_map<std::string, ll> tmp;
        for (auto& [pair, cnt] : tmplt) {
            if (rules.contains(pair)) {
                std::string s(2, '\0');
                s[0] = pair[0]; s[1] = rules[pair];
                tmp[s] += cnt;
                s[0] = rules[pair]; s[1] = pair[1];
                tmp[s] += cnt;
            } else {
                tmp.insert({pair, cnt});
            }
        }
        tmplt = tmp;
    }
    std::unordered_map<char, ll> count;
    for (auto& [pair, cnt] : tmplt) {
        count[pair[0]] += cnt;
    }
    ++count[raw.back()];
    auto comp = [](auto& a, auto& b) { return a.second < b.second; };
    ll max = std::max_element(count.begin(), count.end(), comp)->second;
    ll min = std::min_element(count.begin(), count.end(), comp)->second;
    std::cout << max - min << std::endl;
}
