#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> vll;
typedef vector< vll > vll2;
typedef pair<ll, ll> pll;
typedef string str;

//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
//#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
#define vin(a) {for (auto& _ : (a)) {cin >> _;}}
#define vout(a) {for (auto _ : (a)) {cout << _ << " ";} cout << "\n";}
#define forn(i, n) for (int (i) = 0; (i) < int(n); (i)++)
#define all(x) (x).begin(), (x).end()
#define sz(a) ((int) ((a).size()))

#define F first
#define S second
#define pb push_back

const int inf = 1e9, mod = 1e9+7, N = 1e5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

struct Vec {
    ld x = 0;
    ld y = 0;
    void read() {
        cin >> x >> y;
    }
    void print() const {
        cout << x << " " << y << "\n";
    }
};

Vec operator-(Vec a, Vec b) {
    return {a.x-b.x, a.y-b.y};
}
ld operator%(Vec a, Vec b) {
    return a.x*b.x + a.y*b.y;
}
ld operator*(Vec a, Vec b) {
    return a.x*b.y - a.y*b.x;
}
Vec operator*(Vec a, ld x) {
    return {a.x*x, a.y*x};
}
Vec operator+(Vec a, Vec b) {
    return {a.x+b.x, a.y+b.y};
}
ld dist(Vec a, Vec b) {
    return hypot(a.x-b.x, a.y-b.y);
}

struct Seg {
    Vec x, y;
    void read() {
        x.read();
        y.read();
    }
    void print() const {
        x.print();
        y.print();
    }
};

bool checkIntersect(Seg a, Seg b) {
    return ((a.x-a.y)*(b.x-a.y)) * ((a.x-a.y)*(b.y-a.y)) < 0
        && ((b.x-b.y)*(a.x-b.y)) * ((b.x-b.y)*(a.y-b.y)) < 0;
}
bool isOnSegment(Seg a, Vec p) {
    return (a.x-a.y)*(p-a.y) == 0 && (a.x-p)%(a.y-p) <= 0;
}
bool isIntersect(Seg a, Seg b) {
    return checkIntersect(a, b) || isOnSegment(a, b.x) || isOnSegment(a, b.y)
        || isOnSegment(b, a.x) || isOnSegment(b, a.y);
}

int solve(ll tc) {
    Seg a, b;
    a.read(); b.read();

    // пересечение отрезков
    if (isIntersect(a, b))
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}

int main() {
    IOS;

    ll tc = 1;
//    cin >> tc;
    forn(i, tc) {
        solve(i);
    }

    return 0;
}