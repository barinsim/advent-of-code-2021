#include <iostream>
#include <cmath>
#include <vector>

int main()
{
        std::vector<int> nums;
        int val;
        while (std::cin >> val) {
            nums.push_back(val);
            std::cin.ignore(1);
        }
        sort(nums.begin(), nums.end());
        int median = 0;
        if (nums.size() % 2 == 0) {
            median = (nums[nums.size() / 2] + nums[nums.size() / 2 - 1]) / 2;
        } else {
            median = nums[nums.size() / 2];
        }
        int res = 0;
        for (int n : nums) {
            res += std::abs(median - n);
        }
        std::cout << res << std::endl;
}
