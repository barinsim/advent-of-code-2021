#include <iostream>
#include <vector>

int main()
{
    int val;
    std::vector<int> nums;
    while (std::cin >> val) {
        nums.push_back(val);
        std::cin.ignore(1);
    }
    for (int day = 0; day < 80; ++day) {
        int cnt = 0;
        for (auto& n : nums) {
            --n;
            if (n == -1) {
                n = 6;
                ++cnt;
            }
        }
        std::vector<int> tmp(cnt, 8);
        nums.insert(nums.end(), tmp.begin(), tmp.end());
    }
    std::cout << nums.size() << std::endl;
}
