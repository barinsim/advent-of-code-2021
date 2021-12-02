#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>

int main() {
    int x = 0, y = 0, aim = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        std::string command;
        int val;
        ss >> command >> val;
        if (command == "up") {
            aim -= val;
        } else if (command == "down") {
            aim += val;
        } else {
            assert(command == "forward");
            x += val;
            y += val * aim;
        }
    }
    std::cout << "x: " << x << " y: " << y << std::endl;
}
