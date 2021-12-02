#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>

int main() {
    int x = 0, y = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string command;
        int val;
        ss >> command >> val;
        if (command == "up") {
            y = std::max(0, y - val);
        } else if (command == "down") {
            y += val;
        } else {
            assert(command == "forward");
            x += val;
        }
    }
    std::cout << "x: " << x << " y: " << y << std::endl;
}
