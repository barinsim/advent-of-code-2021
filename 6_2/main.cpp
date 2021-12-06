#include <iostream>
#include <vector>
#include <map>

int main()
{
    int val;
    std::vector<long long unsigned> counts(9, 0);
    while (std::cin >> val) {
        ++counts[val];
        std::cin.ignore(1);
    }
    for (int day = 0; day < 256; ++day) {
        long long unsigned newBorn = counts[0];
        for (int i = 1; i < counts.size(); ++i) {
            counts[i - 1] = counts[i];
        }
        counts[8] = newBorn;
        counts[6] += newBorn;
    }
    long long unsigned res = 0;
    for (int i = 0; i < counts.size(); ++i) {
        res += counts[i];
    }
    std::cout << res << std::endl;
}
