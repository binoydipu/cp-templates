#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll inf = 8e18;

#define int long long
#define nl '\n'
#define all(v) v.begin(), v.end()
template<typename T> istream& operator>>(istream& in, vector<T>& a) {for(auto &x : a) in >> x; return in;};

using T = long long;

const T Inf = 8e18;
int sign(T x) { return x == 0 ? 0 : x > 0 ? 1 : -1; }

struct Point {
    T x, y;
    Point() : x(0), y(0) {}
    Point(T _x, T _y) : x(_x), y(_y) {}
    Point(const Point &p) : x(p.x), y(p.y) {}

    bool operator<(const Point &other) const { return sign(x - other.x) == 0 ? y < other.y : x < other.x; }
    bool operator<=(const Point &other) const { return sign(x - other.x) == 0 ? y <= other.y : x <= other.x; }
};
istream &operator>>(istream &in, Point &p) { return in >> p.x >> p.y; }
ostream &operator<<(ostream &out, Point p) { return out << "(" << p.x << "," << p.y << ")"; }

ll SQ(ll x) { return x * x; }
ll dist2(const Point &a, const Point &b) { return SQ(a.x - b.x) + SQ(a.y - b.y); }

// Returns squared smallest smallest distance between any two pair of points from a set
// takes points sorted by x-axis, and sorted by y-axis
ll smallest_distance(const vector<Point>& points, const vector<Point>& points_by_y) { // O(nlogn)
    int n = points.size();
    if(n <= 1) return Inf;
    vector<Point> left = vector<Point>(points.begin(), points.begin() + n / 2);
    vector<Point> right = vector<Point>(points.begin() + n / 2, points.end());
    vector<Point> left_by_y, right_by_y;
    for(Point a : points_by_y) {
        if(a <= Point(left.back().x, left.back().y)) {
            left_by_y.push_back(a);
        } else {
            right_by_y.push_back(a);
        }
    }
    ll d1 = smallest_distance(left, left_by_y);
    ll d2 = smallest_distance(right, right_by_y);
    ll d = min(d1, d2);
    ll middle_x = left.back().x;
    vector<Point> stripe;
    for(Point a : points_by_y) {
        if(SQ(a.x - middle_x) < d) stripe.push_back(a);
    }
    for (int i = 0; i < stripe.size(); i++) { // O(1)
        for (int j = i + 1; j < stripe.size() && SQ(stripe[j].y - stripe[i].y) < d; j++) {
            d = min(d, dist2(stripe[i], stripe[j]));
        }
    }
    return d;
}

int32_t main() {
    int n; cin >> n;
    vector<Point> points(n);
    cin >> points;
    sort(all(points));
    vector<Point> points_by_y(points);
    sort(all(points_by_y), [&](const Point& a, const Point& b) {
        return a.y < b.y;
    });
    ll ans = smallest_distance(points, points_by_y);
    cout << ans << nl;

    return 0;
}

// Problem Link: https://cses.fi/problemset/task/2194/