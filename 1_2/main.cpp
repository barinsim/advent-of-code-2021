#include <iostream>
#include <vector>

int main() {
    std::vector<int> in;
    int val;
    while(std::cin >> val) {
        in.push_back(val);
    }
    int res = 0;
    int curr = in[0] + in[1] + in[2];
    for (int i = 3; i < in.size(); ++i) {
        int prev = curr;
        curr += in[i] - in[i - 3];
        res += curr > prev;
    }
    std::cout << res << std::endl;
}
