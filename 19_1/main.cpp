#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#include <functional>
#include <algorithm>
#include <chrono>
#include <random>

#define ll long long int

const std::vector<std::vector<int>> permutations = {
        {1, 2, 3},
        {1, 3, -2},
        {1, -2, -3},
        {1, -3, 2},
        {3, 2, -1},
        {3, -1, -2},
        {3, -2, 1},
        {3, 1, 2},
        {2, 3, 1},
        {2, -1, 3},
        {2, -3, -1},
        {2, 1, -3},
        {-1, 2, -3},
        {-1, -3, -2},
        {-1, -2, 3},
        {-1, 3, 2},
        {-3, 2, 1},
        {-3, -1, 2},
        {-3, -2, -1},
        {-3, 1, -2},
        {-2, 3, -1},
        {-2, -1, -3},
        {-2, -3, 1},
        {-2, 1, 3}
};

struct Point
{
    int x = 0, y = 0, z = 0;
    Point rotated(const std::vector<int>& perm) const
    {
        std::vector<int> coords = {x, y, z};
        std::vector<int> rotatedCoords(3);
        for (int i = 0; i < 3; ++i) {
            rotatedCoords[i] = coords[std::abs(perm[i]) - 1];
            if (perm[i] < 0) {
                rotatedCoords[i] = -rotatedCoords[i];
            }
        }
        return Point{rotatedCoords[0], rotatedCoords[1], rotatedCoords[2]};
    }
    Point translated(const Point& dir) const
    {
        return Point{x + dir.x, y + dir.y, z + dir.z};
    }

    bool operator < (const Point& p) const
    {
        ll a = (ll)x << 36 | (ll)y << 16 | (ll)z;
        ll b = (ll)p.x << 36 | (ll)p.y << 16 | (ll)p.z;
        return a < b;
    }
    bool operator == (const Point& p) const { return x == p.x && y == p.y && z == p.z; }
};

struct Scaner
{
    Point pos;
    std::set<Point> points;
    Scaner rotated(const std::vector<int>& perm) const
    {
        Scaner scaner;
        for (auto& p : points) {
            scaner.points.insert(p.rotated(perm));
        }
        scaner.pos = pos.rotated(perm);
        return scaner;
    }
    Scaner aligned(const Point& point, const Point& anchor) const
    {
        Point dir{anchor.x - point.x, anchor.y - point.y, anchor.z - point.z};
        return translated(dir);
    }
    Scaner translated(const Point& dir) const
    {
        Scaner scaner;
        for (auto& p : points) {
            scaner.points.insert(p.translated(dir));
        }
        scaner.pos = pos.translated(dir);
        return scaner;
    }
};

std::ostream& operator << (std::ostream& os, const Point& p)
{
    return os << p.x << " " << p.y << " " << p.z;
}

int intersectionSize(const Scaner& a, const Scaner& b)
{
    std::vector<Point> res;
    std::set_intersection(a.points.begin(), a.points.end(),
                          b.points.begin(), b.points.end(),
                          std::back_inserter(res));
    return res.size();
}

std::list<Scaner> readScaners()
{
    std::list<Scaner> scaners;
    std::string line;
    while (std::getline(std::cin, line)) {
        scaners.emplace_back();
        while (std::getline(std::cin, line)) {
            if (line.empty()) {
                break;
            }
            Point p;
            std::stringstream ss(line);
            ss >> p.x;
            ss.ignore(1); // ','
            ss >> p.y;
            ss.ignore(1); // ','
            ss >> p.z;
            scaners.back().points.insert(p);
        }
    }
    return scaners;
}

int totalPoints(const std::list<Scaner>& scaners)
{
    int sum = 0;
    for (auto& s : scaners) {
        sum += s.points.size();
    }
    return sum;
}

std::list<Scaner> shuffled(std::list<Scaner>& scaners)
{
    std::vector<Scaner> vec(scaners.begin(), scaners.end());
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
    return {vec.begin(), vec.end()};
}

int main()
{
    auto scaners = readScaners();
    scaners = shuffled(scaners);
    int totalP = totalPoints(scaners);
    int total = scaners.size();
    std::vector<Scaner> fixed = {*scaners.begin()};
    scaners.erase(scaners.begin());
    std::set<Point> points(fixed[0].points.begin(), fixed[0].points.end());
    while (fixed.size() < total) {
        std::cout << fixed.size() << std::endl;
        std::cout << totalP << std::endl;
        for (auto first1 = fixed.begin(); first1 != fixed.end(); ++first1) {
            for (auto first2 = scaners.begin(); first2 != scaners.end(); ++first2) {
                bool found = false;
                for (auto& perm : permutations) {
                    Scaner rotated = first2->rotated(perm);
                    for (auto& p1 : first1->points) {
                        for (auto& p2 : rotated.points) {
                            Scaner aligned = rotated.aligned(p2, p1);
                            int size = intersectionSize(*first1, aligned);
                            if (size >= 12) {
                                totalP -= size;
                                std::cout << aligned.pos << std::endl;
                                std::cout << first1->pos << std::endl;
                                fixed.push_back(aligned);
                                points.insert(aligned.points.begin(), aligned.points.end());
                                scaners.erase(first2);
                                goto loop;
                            }
                        }
                    }
                }
            }
        }
        loop:
        int jumpLabel = 1;
    }
    std::cout << totalP << std::endl;

//    for (auto& p : points) {
//        std::cout << p.x << "," << p.y << "," << p.z << std::endl;
//    }
//    for (auto& s : fixed) {
//        std::cout << s.pos.x << " " << s.pos.y << " " << s.pos.z << std::endl;
//    }
}
