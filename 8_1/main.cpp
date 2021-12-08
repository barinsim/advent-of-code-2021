#include <iostream>
#include <sstream>

int main()
{
    int res = 0;
    std::string line;
    while (std::getline(std::cin, line)) {
        auto midIdx = line.find('|');
        auto vals = line.substr(midIdx, std::string::npos);
        std::stringstream ss(vals);
        std::string val;
        while (ss >> val) {
            if (val.size() == 2 ||
                val.size() == 4 ||
                val.size() == 3 ||
                val.size() == 7) {
                    ++res;
                }
        }
    }
    std::cout << res << std::endl;
}
