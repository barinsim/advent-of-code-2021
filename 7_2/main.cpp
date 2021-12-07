#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <algorithm>
#include <numeric>

int main()
{
        std::vector<int> nums;
        int val;
        while (std::cin >> val) {
            nums.push_back(val);
            std::cin.ignore(1);
        }
        int res = std::numeric_limits<int>::max();
        int acc = std::accumulate(nums.begin(), nums.end(), 0);
        double mean = (double)acc / nums.size();
        for (int mid : {std::ceil(mean), std::floor(mean)}) {
            int sum = 0;
            for (int n : nums) {
                int dist = std::abs(n - mid);
                sum += std::round(dist / 2.0 * (2 + dist - 1));
            }
            res = std::min(res, sum);
        }
        std::cout << res << std::endl;
}
