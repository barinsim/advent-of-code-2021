#include <iostream>
#include <vector>

int main() {
    std::vector<int> in;
    int val;
    while(std::cin >> val) {
        in.push_back(val);
    }
    int res = 0;
    for (auto it = in.begin() + 1; it != in.end(); ++it) {
        res += *it > *(it-1);
    }
    std::cout << res << std::endl;
}
