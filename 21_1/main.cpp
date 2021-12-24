#include <iostream>

int roll(int& last)
{
    ++last;
    if (last >= 101) {
        last -= 100;
    }
    return last;
}

int main()
{
    int a;
    int b;
    std::cin.ignore(28);
    std::cin >> a;
    std::cin.ignore(29);
    std::cin >> b;
    int ascore = 0;
    int bscore = 0;
    int* curr = &a;
    int* currscore = &ascore;
    int last = 0;
    int cnt = 0;
    while (ascore < 1000 && bscore < 1000) {
        int sum = roll(last) + roll(last) + roll(last);
        *curr += sum;
        while (*curr > 10) { *curr -= 10; }
        *currscore += *curr;
        cnt += 3;
        if (cnt % 2 == 1) {
            curr = &b;
            currscore = &bscore;
        } else {
            curr = &a;
            currscore = &ascore;
        }
    }
    std::cout << ascore << " " << bscore << std::endl;
    std::cout << cnt << std::endl;
    std::cout << cnt * std::min(ascore, bscore) << std::endl;
}
