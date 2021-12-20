#include <iostream>
#include <numeric>
#include <utility>
#include <cmath>
#include <vector>
#include <set>

int main()
{
    int ax, bx, ay, by;
    std::cin.ignore(15); // 'target area: x='
    std::cin >> ax;
    std::cin.ignore(2); // '..'
    std::cin >> bx;
    std::cin.ignore(4); // ', y='
    std::cin >> ay;
    std::cin.ignore(2); // '..'
    std::cin >> by;

    std::set<std::pair<int, int>> ans;
    for (int y = ay; y <= std::abs(ay); ++y) {
        for (int x = 1; x <= bx; ++x) {
            int xd = x;
            int yd = y;
            int xpos = 0;
            int ypos = 0;
            while (xpos <= bx && (yd >= 0 || ypos >= ay)) {
                xpos += xd;
                ypos += yd;
                if (xd > 0) { --xd; }
                --yd;
                if (xpos >= ax && xpos <= bx && ypos >= ay && ypos <= by) {
                    ans.insert({x, y});
                    break;
                }
            }
        }
    }
    std::cout << ans.size() << std::endl;
}
