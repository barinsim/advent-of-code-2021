#include <iostream>
#include <tuple>
#include <map>

#define ll long long int

ll resolvePos(ll pos)
{
    if (pos > 10) {
        return pos - 10;
    }
    return pos;
}

struct Pair{
    ll a = 0;
    ll b = 0;
    Pair& operator += (const Pair& p) {
        a += p.a;
        b += p.b;
        return *this;
    }
};

Pair solve(ll a, ll b, ll ascore, ll bscore, ll cnt, bool aturn,
           std::map<std::tuple<ll, ll, ll, ll, ll, bool>, Pair>& dp)
{
    if (cnt > 0 && cnt % 3 == 0) {
        if (aturn) { ascore += a; }
        else { bscore += b; }
        aturn = !aturn;
    }
    if (dp.contains({a, b, ascore, bscore, cnt % 3, aturn})) {
        return dp[{a, b, ascore, bscore, cnt % 3, aturn}];
    }
    if (ascore >= 21) {
        return {1, 0};
    }
    if (bscore >= 21) {
        return {0, 1};
    }
    Pair sum;
    if (aturn) {
        sum += solve(resolvePos(a + 1), b, ascore, bscore, cnt + 1, aturn, dp);
        sum += solve(resolvePos(a + 2), b, ascore, bscore, cnt + 1, aturn, dp);
        sum += solve(resolvePos(a + 3), b, ascore, bscore, cnt + 1, aturn, dp);
    } else {
        sum += solve(a, resolvePos(b + 1), ascore, bscore, cnt + 1, aturn, dp);
        sum += solve(a, resolvePos(b + 2), ascore, bscore, cnt + 1, aturn, dp);
        sum += solve(a, resolvePos(b + 3), ascore, bscore, cnt + 1, aturn, dp);
    }
    return dp[{a, b, ascore, bscore, cnt % 3, aturn}] = sum;
}

int main()
{
    int a;
    int b;
    std::cin.ignore(28);
    std::cin >> a;
    std::cin.ignore(29);
    std::cin >> b;
    std::map<std::tuple<ll, ll, ll, ll, ll, bool>, Pair> dp;
    auto ans = solve(a, b, 0, 0, 0, true, dp);
    std::cout << ans.a << " " << ans.b << std::endl;
}
