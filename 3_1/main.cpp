#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::vector<std::string> in;
    std::string s;
    while (std::cin >> s) {
            in.push_back(s);
    }
    std::vector<int> cnt (in[0].size(), 0);
    for (auto& bin : in) {
        for (int i = 0; i < bin.size(); ++i) {
            cnt[i] += bin[i] - '0';
        }
    }
    unsigned gamma = 0;
    for (int c : cnt) {
        gamma <<= 1;
        if (c > in.size() - c) {
            gamma |= 1;
        }
    }
    unsigned epsilon = ~gamma & 0xFFF;
    std::cout << "gamma: " << gamma << '\n';
    std::cout << "epsilon: " << epsilon << '\n';
    std::cout << "result: " << gamma * epsilon << '\n';
}
