#include <iostream>
#include <tuple>
#include <unordered_set>
#include <string>
#include <numeric>
#include <vector>

#define ll long long int

struct Cuboid
{
    ll xstart, xend;
    ll ystart, yend;
    ll zstart, zend;
};

struct CuboidWithInters
{
    Cuboid c;
    std::vector<Cuboid> inters;
};

std::vector<std::pair<bool, Cuboid>> readInput()
{
    std::vector<std::pair<bool, Cuboid>> input;
    std::string str;
    while (std::cin >> str) {
        bool turnOn = str == "on";
        Cuboid c;
        std::vector<std::pair<ll&, ll&>> mems = {{c.xstart, c.xend}, {c.ystart, c.yend}, {c.zstart, c.zend}};
        for (auto& [s, e] : mems) {
            std::cin.ignore(3);
            std::cin >> s;
            std::cin.ignore(2);
            std::cin >> e;
        }
        input.push_back({turnOn, c});
    }
    return input;
}

Cuboid intersection(const Cuboid& a, const Cuboid& b)
{
    Cuboid res;
    res.xstart = std::max(a.xstart, b.xstart);
    res.xend = std::min(a.xend, b.xend);
    res.ystart = std::max(a.ystart, b.ystart);
    res.yend = std::min(a.yend, b.yend);
    res.zstart = std::max(a.zstart, b.zstart);
    res.zend = std::min(a.zend, b.zend);
    return res;
}

bool intersect(const Cuboid& a, const Cuboid& b)
{
    auto c = intersection(a, b);
    return c.xstart <= c.xend && c.ystart <= c.yend && c.zstart <= c.zend;
}

ll size(const Cuboid& c)
{
    return (c.xend - c.xstart + 1) * (c.yend - c.ystart + 1) * (c.zend - c.zstart + 1);
}

struct Rectangle
{
    ll xstart, xend;
    ll ystart, yend;
};

std::vector<Rectangle> makeRectangles(const std::unordered_set<const Cuboid*>& cuboids)
{
    std::vector<Rectangle> res;
    for (auto c : cuboids) {
        Rectangle rect = {c->zstart, c->zend, c->ystart, c->yend};
        res.push_back(rect);
    }
    return res;
}

ll size(const std::vector<Rectangle>& rectangles)
{
    struct SweepData {
        ll x;
        const Rectangle* r;
        bool isEnd;
    };
    if (rectangles.empty()) {
        return 0;
    }
    std::vector<SweepData> events;
    for (auto& r : rectangles) {
        std::vector<std::pair<ll, bool>> mems = {{r.xstart, false}, {r.xend, true}};
        for (auto& [x, isEnd] : mems) {
            SweepData sd = {isEnd ? x + 1 : x, &r, isEnd};
            events.push_back(sd);
        }
    }
    std::sort(events.begin(), events.end(), [](auto& a, auto& b) { return a.x < b.x; });
    std::unordered_set<const Rectangle*> line;
    auto len = [](auto& line) {
        std::vector<std::pair<ll, bool>> vec;
        for (auto r : line) {
            std::vector<std::pair<ll, bool>> mems = {{r->ystart, false}, {r->yend, true}};
            for (auto& [y, isEnd] : mems) {
                vec.push_back({isEnd ? y + 1 : y, isEnd});
            }
        }
        std::sort(vec.begin(), vec.end());
        int state = 0;
        ll min = LLONG_MAX;
        ll res = 0;
        for (auto& [num, isEnd] : vec) {
            state += isEnd ? 1 : -1;
            min = std::min(min, num);
            if (state == 0) {
                res += num - min;
                min = LLONG_MAX;
            }
        }
        return res;
    };
    ll prev = events[0].x;
    ll res = 0;
    for (auto& event : events) {
        res += len(line) * (event.x - prev);
        prev = event.x;
        if (event.isEnd) {
            line.erase(event.r);
        } else {
            line.insert(event.r);
        }
    }
    return res;
}

ll size(const std::vector<Cuboid>& cuboids)
{
    struct SweepData {
        ll x;
        const Cuboid* c;
        bool isEnd;
    };
    if (cuboids.empty()) {
        return 0;
    }
    std::vector<SweepData> events;
    for (auto& c : cuboids) {
        std::vector<std::pair<ll, bool>> mems = {{c.xstart, false}, {c.xend, true}};
        for (auto& [x, isEnd] : mems) {
            SweepData sd = {isEnd ? x + 1 : x, &c, isEnd};
            events.push_back(sd);
        }
    }
    std::sort(events.begin(), events.end(), [](auto& a, auto& b) { return a.x < b.x; });
    std::unordered_set<const Cuboid*> rectangles;
    ll res = 0;
    ll prev = events[0].x;
    for (auto& event : events) {
        res += size(makeRectangles(rectangles)) * (event.x - prev);
        prev = event.x;
        if (event.isEnd) {
            rectangles.erase(event.c);
        } else {
            rectangles.insert(event.c);
        }
    }
    return res;
}

ll computeSize(CuboidWithInters& cwi)
{
    return size(cwi.c) - size(cwi.inters);
}

int main()
{
    auto input = readInput();
    std::vector<CuboidWithInters> cuboids;
    for (auto& [turnOn, cube] : input) {
        for (auto& existing : cuboids) {
            if (!intersect(cube, existing.c)) {
                continue;
            }
            Cuboid inter = intersection(cube, existing.c);
            existing.inters.push_back(inter);
        }
        if (turnOn) {
            CuboidWithInters cwi = {cube};
            cuboids.push_back(cwi);
        }
    }
    ll ans = 0;
    for (auto& cwi : cuboids) {
        ans += computeSize(cwi);
    }
    std::cout << ans << std::endl;
}
