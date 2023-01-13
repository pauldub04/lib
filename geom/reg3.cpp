#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,sse,sse2,lzcnt,popcnt")

#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef string str;
typedef vector<ll> vll;
typedef vector<vll> vll2;
typedef pair<ll, ll> pll;

//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define all(a) (a).begin(), (a).end()
#define sz(a) int((a).size())
#define vin(a) { for (auto &x : (a)) { cin >> x; } }
#define vout(a) { for (auto x : (a)) { cout << x << " "; } cout << "\n"; }

#define F first
#define S second
#define pb push_back

const int inf = 1e9, mod = 1e9+7, N = 1e5+5, LG = 60;
const ll INF = 1e18;
const ld eps = 1e-15;

struct Vec {
    ld x;
    ld y;
    Vec(ld _x = 0, ld _y = 0) {
        x = _x;
        y = _y;
    }
    void read() {
        cin >> x >> y;
    }
    void print() const {
        cout << x << " " << y << "\n";
    }
    ld len() const {
        return hypotl(x, y);
    }
};

Vec operator+(const Vec &a, const Vec &b) {
    return {a.x+b.x, a.y+b.y};
}
Vec operator-(const Vec &a, const Vec &b) {
    return {a.x-b.x, a.y-b.y};
}
ld operator%(const Vec &a, const Vec &b) {
    return a.x*b.x + a.y*b.y;
}
ld operator*(const Vec &a, const Vec &b) {
    return a.x*b.y - a.y*b.x;
}

ld angle(const Vec &a, const Vec &b) {
    return fabsl(atan2l(a*b, a%b));
}

ld dist(const Vec &a, const Vec &b) {
    return (b-a).len();
}

bool eq(ld a, ld b) {
    return fabsl(a-b) < eps;
}

struct Triangle {
    Vec a, b, c;
    vector<ld> angles;
    vector<ld> lens;

    Triangle() = default;
    void read() {
        a.read();
        b.read();
        c.read();
    }
    void print() const {
        a.print();
        b.print();
        c.print();
        cout << "angles: "; vout(angles);

        cout << angles[0]+angles[1]+angles[2] << "\n";

        cout << "lens: "; vout(lens);
        cout << "------\n";
    }

    void fill() {
        lens.clear(); lens.reserve(3);
        lens.pb((b-a).len());
        lens.pb((c-b).len());
        lens.pb((a-c).len());

        angles.clear(); angles.reserve(3);
        angles.pb(angle((b-a), (c-a)));
        angles.pb(angle((c-b), (a-b)));
        angles.pb(angle((a-c), (b-c)));
    }

    void rotate() {
//        angles.insert(angles.begin(), angles.back());
//        angles.pop_back();
        ld t = angles[2];
        angles[2] = angles[1];
        angles[1] = angles[0];
        angles[0] = t;

//        lens.insert(lens.begin(), lens.back());
//        lens.pop_back();
        t = lens[2];
        lens[2] = lens[1];
        lens[1] = lens[0];
        lens[0] = t;
    }
};

ll tc, n;
vector<Triangle> v;

struct Q {
    ll a;
    ll b;
    ll c;
    ll d;
};
bool operator==(const Q &a, const Q &b) {
    return a.a == b.a && a.b == b.b && a.c == b.c && a.d == b.d;
}
bool operator<(const Q &a, const Q &b) {
    return a.a < b.a;
}

vector<Q> ans;

bool check(vll g) {
    while (next_permutation(all(g))) {
        ll down = g[0], left = g[1], right = g[2], mid = g[3];

        for (int ra = 0; ra < 3; ra++) {
            for (int rb = 0; rb < 3; rb++) {
                for (int rc = 0; rc < 3; rc++) {
                    for (int rd = 0; rd < 3; rd++) {
                        if (eq(v[mid].angles[0]+v[right].angles[0]+v[down].angles[0], M_PI)
                            && eq(v[mid].angles[1]+v[right].angles[2]+v[left].angles[2], M_PI)
                            && eq(v[mid].angles[2]+v[down].angles[1]+v[left].angles[1], M_PI)
                            && eq(v[mid].lens[0], v[right].lens[2])
                            && eq(v[mid].lens[1], v[left].lens[1])
                            && eq(v[mid].lens[2], v[down].lens[0])
                                )
                                return 1;

                        v[down].rotate();
                    }
                    v[left].rotate();
                }
                v[right].rotate();
            }
            v[mid].rotate();
        }
    }

    return 0;
}

int solve() {
    cin >> tc >> n;

    v.resize(n);
    for (auto &x : v) {
        x.read();
        x.fill();
    }

    for (int a = 0; a < n; a++) {
        for (int b = a+1; b < n; b++) {
            for (int c = b+1; c < n; c++) {
                for (int d = c+1; d < n; d++) {
                    vll t = {a, b, c, d};
                    Q q = {a, b, c, d};

                    if (check(t))
                        ans.pb(q);
                }
            }
        }
    }

    cout << sz(ans) << "\n";
    for (auto x : ans)
        cout << x.a+1 << " " << x.b+1 << " " << x.c+1 << " " << x.d+1 << "\n";

    return 0;
}

/*
1
4
0 0 6 2 1 2
0 0 5 0 6 3
0 0 3 1 1 3
0 0 6 3 3 6
*/

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    ll t = 1;
//    cin >> t;
    while(t--)
        solve();

    return 0;
}
