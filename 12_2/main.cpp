#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

int dfs(const std::string& str,
        std::unordered_map<std::string, int>& visited,
        std::unordered_map<std::string, std::vector<std::string>>& graph,
        bool& twice)
{
    if (str == "end") {
        return 1;
    }
    auto pred = [](auto c) { return std::islower(c); };
    bool isLowercase = std::all_of(str.begin(), str.end(), pred);
    if (isLowercase) {
        if (visited[str] == 2) {
            return 0;
        }
        if (visited[str] == 1 && twice) {
            return 0;
        }
        if (visited[str] == 1) {
            twice = true;
        }
    }
    ++visited[str];
    int sum = 0;
    for (auto& n : graph[str]) {
        if (n == "start") {
            continue;
        }
        sum += dfs(n, visited, graph, twice);
    }
    --visited[str];
    if (isLowercase && visited[str] == 1) {
        twice = false;
    }
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
    std::unordered_map<std::string, int> visited;
    bool twice = false;
    int ans = dfs("start", visited, graph, twice);
    std::cout << ans << std::endl;
}
