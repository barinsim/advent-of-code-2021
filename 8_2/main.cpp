#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

int interSize(const std::string& a, const std::string& b)
{
    std::string inter;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(inter));
    return inter.size();
}

int main()
{
    std::string line;
    int res = 0;
    while (std::getline(std::cin, line)) {
        auto midIdx = line.find('|');
        auto valsRaw = line.substr(midIdx + 1);
        auto sigsRaw = line.substr(0, midIdx);
        std::stringstream ss(sigsRaw);
        std::string sig;
        std::unordered_map<int, std::vector<std::string>> signals; // size -> signals
        std::unordered_map<int, std::string> known;
        while (ss >> sig) {
            std::sort(sig.begin(), sig.end());
            if (sig.size() == 3) {
                known[7] = sig;
            } else if (sig.size() == 2) {
                known[1] = sig;
            } else if (sig.size() == 7) {
                known[8] = sig;
            } else if (sig.size() == 4) {
                known[4] = sig;
            } else {
                signals[sig.size()].push_back(sig);
            }
        }
        for (auto& str : signals[6]) {
            if (interSize(str, known[7]) == 2) {
                known[6] = str;
            } else if (interSize(str, known[4]) == 3) {
                known[0] = str;
            } else if (interSize(str, known[4]) == 4) {
                known[9] = str;
            }
        }
        for (auto& str : signals[5]) {
            if (interSize(str, known[7]) == 3) {
                known[3] = str;
            } else if (interSize(str, known[4]) == 2) {
                known[2] = str;
            } else if (interSize(str, known[4]) == 3) {
                known[5] = str;
            }
        }
        std::unordered_map<std::string, int> lookup;
        for (auto& [key, val] : known) {
            lookup[val] = key;
        }
        ss = std::stringstream(valsRaw);
        int val = 0;
        while (ss >> sig) {
            std::sort(sig.begin(), sig.end());
            val *= 10;
            val += lookup[sig];
        }
        res += val;
    }
    std::cout << res << std::endl;
}
