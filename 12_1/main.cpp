#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int dfs(const std::string& str,
        std::unordered_set<std::string>& visited,
        std::unordered_map<std::string, std::vector<std::string>>& graph)
{
    if (str == "end") {
        return 1;
    }
    if (std::all_of(str.begin(), str.end(), [](auto c) { return std::islower(c); }) &&
        visited.contains(str)) {
        return 0;
    }
    visited.insert(str);
    int sum = 0;
    for (auto& n : graph[str]) {
        sum += dfs(n, visited, graph);
    }
    visited.erase(str);
    return sum;
}

int main()
{
    std::unordered_map<std::string, std::vector<std::string>> graph;
    std::string line;
    while (std::cin >> line) {
        auto pos = line.find('-');
        std::string first = line.substr(0, pos);
        std::string second = line.substr(pos + 1);
        graph[first].push_back(second);
        graph[second].push_back(first);
    }
    std::unordered_set<std::string> visited;
    int ans = dfs("start", visited, graph);
    std::cout << ans << std::endl;
}
