using T = long long;  // integer type
using Tf = double;    // floating type

const Tf Inf = 1e100;
const Tf eps = 1e-7;  
const Tf PI = acos((Tf)-1.0);
int sign(Tf x) { return (x > eps) - (x < -eps); }
int sign(T x) { return x == 0 ? 0 : x > 0 ? 1 : -1; }

struct Point {
    T x, y;
    Point() : x(0), y(0) {}
    Point(T _x, T _y) : x(_x), y(_y) {}
    Point(const Point &p) : x(p.x), y(p.y) {}

    Point operator+(const Point &other) const { return Point(x + other.x, y + other.y); }
    Point operator-(const Point &other) const { return Point(x - other.x, y - other.y); }
    Point &operator+=(const Point &other) { x += other.x, y += other.y; return *this; }
    Point &operator-=(const Point &other) { x -= other.x, y -= other.y; return *this; }
    Point operator*(const T &other) const { return Point(x * other, y * other); }
    Point operator/(const T &other) const { return Point(x / other, y / other); }
    bool operator==(const Point &other) const { return sign(x - other.x) == 0 && (y - other.y) == 0; }
    bool operator<(const Point &other) const { return sign(x - other.x) == 0 ? y < other.y : x < other.x; }
    bool operator>(const Point &other) const { return sign(x - other.x) == 0 ? y > other.y : x > other.x; } 

    // Length of a vector, from (0, 0) to (x, y)
    Tf norm() const { return sqrt(x * x + y * y); }
    // Squared length of a vector, from (0, 0) to (x, y)
    T norm2() const { return (x * x + y * y); }
};
istream &operator>>(istream &in, Point &p) { return in >> p.x >> p.y; }
ostream &operator<<(ostream &out, Point p) { return out << "(" << p.x << "," << p.y << ")"; }

// Middle point of a segment with two points A and B.
inline Point mid_point(Point a, Point b) { return (a + b) / 2; }

// Returns the magnitude of point A
Point abs(Point a) { a.x = a.x < 0 ? -a.x : a.x; a.y = a.y < 0 ? -a.y : a.y; return a; }

// Dot product of two points A and B.
inline T dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }

// Euclidean distance between the two points A and B.
inline Tf dist(Point a, Point b) { return sqrt(dot(a - b, a - b)); }
// Squared Euclidean distance between the two points A and B.
inline Tf dist2(Point a, Point b) { return dot(a - b, a - b); }

// Cross product of two points A and B. Also, twice signed area with (0,0) point
inline T cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
// Returns twice the signed area of triangle ABC, or vector →AB and →AC
inline T cross2(Point a, Point b, Point c) { return cross(b - a, c - a); }

// Positive area formed by triangle (a, b, c)
Tf area_of_triangle(Point a, Point b, Point c) { return fabs((Tf)cross(b - a, c - a)) * 0.5; }

// Point c's position w.r.t the directed line →AB
//  1 means Counter Clock Wise - to left; 
// -1 means Clock Wise - to right;
//  0 means Collinear - all three points on the same line
inline int orientation(Point a, Point b, Point c) { return sign(cross(b - a, c - a)); }

Point perp(Point a) { return Point(-a.y, a.x); }
Point rotateccw90(Point a) { return Point(-a.y, a.x); }
Point rotatecw90(Point a) { return Point(a.y, -a.x); }
Point rotateccw(Point a, double t) { return Point(a.x * cos(t) - a.y * sin(t), a.x * sin(t) + a.y * cos(t)); }
Point rotatecw(Point a, double t) { return Point(a.x * cos(t) + a.y * sin(t), -a.x * sin(t) + a.y * cos(t)); }

Tf SQ(Tf x) { return x * x; }
Tf rad_to_deg(Tf r) { return (r * 180.0 / PI); }
Tf deg_to_rad(Tf d) { return (d * PI / 180.0); }

// Angle created by two points A and B.
Tf get_angle(Point a, Point b) {
    Tf costheta = dot(a, b) / a.norm() / b.norm();
    return acos(max((Tf)-1.0, min((Tf)1.0, costheta)));
}

// Return true if point P lie in angle <bac, assumes a valid triangle
bool is_point_in_angle(Point b, Point a, Point c, Point p) {
    assert(orientation(a, b, c) != 0);
    if (orientation(a, c, b) < 0) swap(b, c);
    return orientation(a, c, p) >= 0 && orientation(a, b, p) <= 0;
}

bool half(Point p) { return p.y > 0.0 || (p.y == 0.0 && p.x < 0.0); }

// sort points in counterclockwise
void polar_sort(vector<Point> &v) {
    sort(v.begin(), v.end(), [](Point a,Point b) {
        return make_tuple(half(a), 0.0, a.norm2()) < make_tuple(half(b), cross(a, b), b.norm2());
    });
}

// sort points in counterclockwise with respect to point o
void polar_sort(vector<Point> &v, Point o) {
    sort(v.begin(), v.end(), [&](Point a,Point b) {
        return make_tuple(half(a - o), 0.0, (a - o).norm2()) < make_tuple(half(b - o), cross(a - o, b - o), (b - o).norm2());
    });
}

// Check if point P lies on the segment AB
bool is_point_on_seg(Point a, Point b, Point p) {
    return fabs(cross2(a, b, p)) <= eps &&
           min(a.x, b.x) - eps <= p.x && p.x <= max(a.x, b.x) + eps &&
           min(a.y, b.y) - eps <= p.y && p.y <= max(a.y, b.y) + eps;
}

// Intersection point between segment AB and segment CD assuming unique intersection exists
bool seg_seg_intersection(Point a, Point b, Point c, Point d, Point &ans) {
    Tf oa = cross2(c, d, a), ob = cross2(c, d, b);
    Tf oc = cross2(a, b, c), od = cross2(a, b, d);
    if (oa * ob < 0 && oc * od < 0) { // crosses each other (on only 1 point)
        ans = (a * ob - b * oa) / (ob - oa);
        return 1;
    }
    else return 0;
}

// point between segment AB and segment CD assuming unique intersection may not exists
// returns points of intersection
// size()==0 means no intersection
// se.size()==1 means one intersection
// se.size()==2 means range intersection
set<Point> seg_seg_intersection_points(Point a,  Point b,  Point c,  Point d) {
    Point ans;
    if (seg_seg_intersection(a, b, c, d, ans)) return {ans};
    set<Point> se;
    if (is_point_on_seg(c, d, a)) se.insert(a);
    if (is_point_on_seg(c, d, b)) se.insert(b);
    if (is_point_on_seg(a, b, c)) se.insert(c);
    if (is_point_on_seg(a, b, d)) se.insert(d);
    return se;
}

// -1 if strictly inside, 0 if on the triangle, 1 if strictly outside
int is_point_in_triangle(Point a, Point b, Point c, Point p) {
    if (sign(cross(b - a, c - a)) < 0) swap(b, c);
    int c1 = sign(cross(b - a, p - a));
    int c2 = sign(cross(c - b, p - b));
    int c3 = sign(cross(a - c, p - c));
    if (c1 < 0 || c2 < 0 || c3 < 0) return 1;
    if (c1 + c2 + c3 != 3) return 0;
    return -1;
}

// build a convex hull with some points P
vector<Point> convex_hull(vector<Point> &p) {
    if (p.size() <= 1) return p;
    vector<Point> v = p;
    sort(v.begin(), v.end());
    vector<Point> up, dn; // upper and lower hull
    for (auto& p : v) {
        // = sign removes points that are on convex (Collinear with some other)
        while (up.size() > 1 && orientation(up[up.size() - 2], up.back(), p) >= 0) {
            up.pop_back();
        }
        while (dn.size() > 1 && orientation(dn[dn.size() - 2], dn.back(), p) <= 0) {
            dn.pop_back();
        }
        up.push_back(p);
        dn.push_back(p);
    }
    v = dn;
    if (v.size() > 1) v.pop_back();
    reverse(up.begin(), up.end());
    up.pop_back();
    for (auto& p : up) {
        v.push_back(p);
    }
    if (v.size() == 2 && v[0] == v[1]) v.pop_back();
    return v;
}

// checks if polygon is convex or not
bool is_convex(vector<Point> &p) {
    bool s[3]; s[0] = s[1] = s[2] = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        int k = (j + 1) % n;
        s[sign(cross(p[j] - p[i], p[k] - p[i])) + 1] = 1;
        if (s[0] && s[2]) return 0;
    }
    return 1;
}

// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
// it must be strictly convex, otherwise make it strictly convex first
int is_point_in_convex(vector<Point> &p, const Point& x) { // O(log n)
    int n = p.size(); assert(n >= 3);
    int a = orientation(p[0], p[1], x), b = orientation(p[0], p[n - 1], x);
    if (a < 0 || b > 0) return 1;
    int l = 1, r = n - 1;
    while (l + 1 < r) {
        int mid = l + r >> 1;
        if (orientation(p[0], p[mid], x) >= 0) l = mid;
        else r = mid;
    }
    int k = orientation(p[l], p[r], x);
    if (k <= 0) return -k;
    if (l == 1 && a == 0) return 0;
    if (r == n - 1 && b == 0) return 0;
    return -1;
}

Tf perimeter_of_polygon(vector<Point> &p) {
    Tf ans = 0; int n = p.size();
    for (int i = 0; i < n; i++) ans += dist(p[i], p[(i + 1) % n]);
    return ans;
}

Tf area_of_polygon(vector<Point>& p) {
    Tf area = 0; int n = p.size();
    for (int i = 0; i < n; i++) area += cross(p[i], p[(i + 1) % n]);
    return fabs(area) * 0.5;
}

// true is P is at least as high is A
bool above(const Point& a, const Point& p) { return p.y >= a.y - eps; }

// check of →PQ crosses ray from A
bool crosses_ray(const Point& a, const Point& p, const Point& q) {
    return (above(a, q) - above(a, p)) * orientation(a, p, q) > 0;
}

// -1 if strictly inside, 0 if on the polygon, 1 if strictly outside
int is_point_in_polygon(vector<Point>& p, const Point& a) { // O(n)
    int n = p.size(), num_of_crossing = 0;
    for (int i = 0; i < n; i++) {
        if(is_point_on_seg(p[i], p[(i + 1) % n], a)) return 0;
        num_of_crossing += crosses_ray(a, p[i], p[(i + 1) % n]);
    }
    return num_of_crossing % 2 == 0 ? 1 : -1; // inside if odd number of crossing
}

// Returns number of integer points inside or on the polygon
int polygon_lattice_points(vector<Point>& p) {
    int boundary = 0, interior = 0, n = p.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        Point diff = abs(p[j] - p[i]);
        // on boundary there are int points equals to the intervals. i.e. gcd of points
        int g = __gcd(diff.x, diff.y);
        boundary += g;
    }
    T area2 = 0;
    for (int i = 0; i < n; i++) area2 += cross(p[i], p[(i + 1) % n]);
    area2 = abs(area2);
    // Pick's theorem: area = interior + (boundary / 2) - 1
    // interior = (2.area - boundary + 2) / 2
    interior = (area2 - boundary + 2) / 2;
    return boundary + interior;
}