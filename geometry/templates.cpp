#include "bits/stdc++.h"
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> vll;
typedef vector< vll > vll2;
typedef pair<ll, ll> pll;
typedef string str;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
#define vin(a) {for (auto& _ : (a)) {cin >> _;}}
#define vout(a) {for (auto _ : (a)) {cout << _ << " ";} cout << "\n";}
#define all(x) (x).begin(), (x).end()
#define sz(a) int((a).size())

#define F first
#define S second
#define pb push_back

const int inf = 1e9, mod = 1e9+7, N = 1e5, LG = 30;
const ll INF = 1e18;

const ld eps = 1e-9;
const ld PI = 3.141592653589793238462643383279502884L;


template<typename T>
bool equal(T a, T b) {
    if constexpr (std::is_floating_point_v<T>) {
        return fabsl(a - b) < eps;
    } else {
        return a == b;
    }
}

template<typename T>
int sign(T x) {
    if (equal(x, T{})) {
        return 0;
    } else if (x > T{}) {
        return 1;
    } else {
        return -1;
    }
}


template<typename T>
struct Vec2 {
    T x;
    T y;
    Vec2(T _x, T _y) : x(_x), y(_y) {}
    Vec2() : x(T{}), y(T{}) {}

    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2& operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2& operator*=(const T& scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vec2& operator/=(const T& scalar) {
        assert(!equal(scalar, T{}));
        x /= scalar;
        y /= scalar;
        return *this;
    }

    ld length() const {
        return hypotl(x, y);
    }
    
    bool empty() const {
        return equal(length(), T{});
    }

    Vec2 normalized() const {
        if (empty()) {
            return Vec2{};
        }
        T len = length();
        return Vec2(x / len, y / len);
    }

    Vec2 operator-() const {
        return Vec2(-x, -y);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Vec2<T>& vec) {
    return stream << vec.x << " " << vec.y;
}

template<typename T>
std::istream& operator>>(std::istream& stream, Vec2<T>& vec) {
    return stream >> vec.x >> vec.y;
}

template<typename T>
Vec2<T> operator+(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template<typename T>
Vec2<T> operator-(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return Vec2<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template<typename T>
Vec2<T> operator*(const Vec2<T>& vec, const T& scalar) {
    return Vec2<T>(vec.x * scalar, vec.y * scalar);
}

template<typename T>
Vec2<T> operator/(const Vec2<T>& vec, const T& scalar) {
    return Vec2<T>(vec.x / scalar, vec.y / scalar);
}

template<typename T>
T dot(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

template<typename T>
T cross(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

template<typename T>
ld angle(const Vec2<T>& lhs, const Vec2<T>& rhs) { // (-PI, PI]
    return atan2l(cross(lhs, rhs), dot(lhs, rhs));
}

template<typename T>
ld dist(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return (rhs - lhs).length();
}

template<typename T>
T area(const vector<Vec2<T>>& points) { // doubled and signed
    assert(sz(points) >= 3);
    T ans{};
    for (int i = 0; i < sz(points)-1; i++) {
        ans += cross(points[i], points[i+1]);
    }
    ans += cross(points.back(), points.front());
    return ans;
}

template<typename T>
struct Segment {
    Vec2<T> a;
    Vec2<T> b;
    Segment(Vec2<T> _a, Vec2<T> _b) : a(_a), b(_b) {}
    Segment() : a(Vec2<T>()), b(Vec2<T>()) {}

    bool through(Vec2<T> p) {
        return equal(cross(a-b, p-b), T{}) && dot(p-a, p-b) <= T{};
    }
};

template<typename T>
bool intersect(Segment<T> s1, Segment<T> s2) {
    if (sign(cross(s1.a-s1.b, s2.b-s1.b)) * sign(cross(s1.a-s1.b, s2.a-s1.b)) < 0
        && sign(cross(s2.a-s2.b, s1.a-s2.b)) * sign(cross(s2.a-s2.b, s1.b-s2.b)) < 0) {
        return 1;
    }
    return s1.through(s2.a) || s1.through(s2.b) || s2.through(s1.a) || s2.through(s1.b);
}

template<typename T>
int inside(Vec2<T> point, const vector<Vec2<T>>& points) {
    // > 0  outside, == 0 on polygon, < 0  inside
    static_assert(std::is_floating_point_v<T>);
    Segment<T> away = Segment<T>(point, Vec2<T>(T(point.x+1e-5), T(1e10)));
   
    ll ints = 0;
    for (int j = 0; j < sz(points)-1; j++) {
        Segment<T> cur(points[j], points[j+1]);
        if (cur.through(point)) {
            return 0;
        }
        ints += intersect(away, cur);
    }

    Segment<T> cur(points.back(), points.front());
    if (cur.through(point)) {
        return 0;
    }
    ints += intersect(away, cur);

    if (ints&1) {
        return -1;
    } else {
        return 1;
    }
}


struct Line {
    ld a = 0;
    ld b = 0;
    ld c = 0;
    Line() = default;
    Line(ld _a, ld _b, ld _c) : a(_a), b(_b), c(_c) {}

    static const Vec2<ld> INFVEC;

    template<typename T>
    Line(Vec2<T> p1, Vec2<T> p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = cross(p1, p2);
    }

    template<typename T>
    Line(Segment<T> s) : Line(s.a, s.b) {}

    Vec2<ld> intersect(const Line& other) const {
        if (equal(a*other.b, other.a*b)) {
            return INFVEC;
        }
        return Vec2<ld>(
            ld(b*other.c-other.b*c)/(a*other.b-other.a*b),
            ld(c*other.a-other.c*a)/(a*other.b-other.a*b)
        );
    }

    template<typename T>
    Vec2<ld> proec(const Vec2<T>& p) {
        Line l(Vec2<ld>(p.x, p.y), Vec2<ld>(p.x+a, p.y+b));
        return intersect(l);
    }

    Vec2<ld> direction() {
        return {b, -a};
    }

    Vec2<ld> norm() {
        return {a, b};
    }

    template<typename U>
    ld dist(const Vec2<U>& p) {
        return (Vec2<ld>(p.x, p.y) - proec(p)).length();
    }
};

const Vec2<ld> Line::INFVEC = Vec2<ld>(INF, INF);

std::ostream& operator<<(std::ostream& stream, const Line& line) {
    return stream << line.a << " " << line.b << " " << line.c;
}

std::istream& operator>>(std::istream& stream, Line& line) {
    return stream >> line.a >> line.b >> line.c;
}

bool parallel(Line l1, Line l2) {
    return equal(l1.a*l2.b, l2.a*l1.b);
}
