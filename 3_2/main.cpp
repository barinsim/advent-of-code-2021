#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    std::vector<std::string> in;
    std::string s;
    while (std::cin >> s) {
            in.push_back(s);
    }

    auto countOnes = [](auto begin, auto end, int pos) {
        int cnt = 0;
        while (begin != end) {
            cnt += (*begin)[pos] - '0';
            ++begin;
        }
        return cnt;
    };

    auto reduceToOne = [&](auto comp) {
        int start = 0, end = in.size() - 1, i = 0;
        while (start != end) {
            int ones = countOnes(in.begin() + start, in.begin() + end + 1, i);
            int zeros = end - start + 1 - ones;
            if (comp(ones, zeros)) {
                start += zeros;
            } else {
                end -= ones;
            }
            i++;
        }
        return start;
    };

    auto toDec = [](const auto& str) {
        unsigned res = 0;
        for (char c : str) { res <<= 1; res |= c - '0'; }
        return res;
    };

    std::sort(in.begin(), in.end());
    int OxIdx = reduceToOne([](auto ones, auto zeros) { return ones >= zeros; });
    int CoIdx = reduceToOne([](auto ones, auto zeros) { return ones < zeros; });
    std::cout << "Oxygen: " << toDec(in[OxIdx]) << '\n';
    std::cout << "CO2: " << toDec(in[CoIdx]) << '\n';
    std::cout << "result: " << toDec(in[CoIdx]) * toDec(in[OxIdx]) << '\n';
}
