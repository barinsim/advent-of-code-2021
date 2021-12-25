#include <iostream>
#include <tuple>
#include <set>
#include <string>
#include <numeric>
#include <vector>

int main()
{
    std::set<std::tuple<int, int, int>> on;
    std::string str;
    while (std::cin >> str) {
        bool turnOn = str == "on";
        std::vector<int> v(6);
        for (int i = 0; i < 3; ++i) {
            std::cin.ignore(3);
            std::cin >> v[2 * i];
            std::cin.ignore(2);
            std::cin >> v[2 * i + 1];
            v[2 * i] = std::max(-50, v[2 * i]);
            v[2 * i + 1] = std::min(50, v[2 * i + 1]);
        }
        for (int x = v[0]; x <= v[1]; ++x) {
            for (int y = v[2]; y <= v[3]; ++y) {
                for (int z = v[4]; z <= v[5]; ++z) {
                    if (turnOn) {
                        on.insert({x, y, z});
                    } else {
                        on.erase({x, y, z});
                    }
                }
            }
        }
    }
    std::cout << on.size() << std::endl;
}
