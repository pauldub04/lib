#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector< vll > vll2;
typedef pair<ll, ll> pll;

#define pb push_back
#define pop_it push_back
#define all(x) (x).begin(), (x).end()
#define sz(a) ((int) ((a).size()))
#define forn(i, n) for (int (i) = 0; (i) < int(n); (i)++)
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)

//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
//uniform_int_distribution<ll>(l, r)(rng)

#define vin(a) for (auto& _ : (a)) {cin >> _;}
#define vout(a) {for (auto _ : (a)) {cout << _ << " ";} cout << "\n";}
#define vpout(a) for (auto _ : (a)) {cout << _.first << " " << _.second << "\n";}

#define F first
#define S second

const int inf = 1e9;
const int mod = 1e9 + 7;
const ld eps = 1e-9;
const ll INF = 1e18 + 10;

typedef ld C;
int sign(C x) {
   if (x == 0 || fabs(x*1.0) < eps)
       return 0;
   else if (x > 0)
       return 1;
   else
       return -1;
}

struct Vec {
   C x, y;
   Vec() {
       x = y = 0;
   }
   Vec(C _x, C _y) {
       x = _x;
       y = _y;
   }
   ld len2() const {
       return x*x + y*y;
   }
   ld len() const {
       return hypotl(x, y);
   }
   friend istream& operator>>(istream& is, Vec& v) {
       cin >> v.x >> v.y;
       return is;
   }
   friend ostream& operator<<(ostream& os, const Vec& v) {
       cout << v.x << ' ' << v.y;
       return os;
   }
};
Vec operator+ (Vec v1, Vec v2) {
   return Vec{v1.x+v2.x, v1.y+v2.y};
}
Vec operator- (Vec v1, Vec v2) {
   return Vec{v1.x-v2.x, v1.y-v2.y};
}
Vec operator* (Vec v, C a) {
   return Vec{v.x*a, v.y*a};
}
Vec operator* (C a, Vec v) {
   return Vec{v.x*a, v.y*a};
}
Vec operator/ (Vec v, C a) {
   return Vec{v.x/a, v.y/a};
}
Vec operator/ (C a, Vec v) {
   return Vec{v.x/a, v.y/a};
}
C operator* (Vec v1, Vec v2) {
   return v1.x*v2.x + v1.y*v2.y;
} // dot product
C operator^ (Vec v1, Vec v2) {
   return v1.x*v2.y - v1.y*v2.x;
} // cross product
ld dist(Vec v1, Vec v2) {
   return (v2 - v1).len();
}
Vec norm(Vec v) {
   return v / v.len();
}
bool isParallel(Vec v1, Vec v2) {
   return (v1^v2) == 0 || fabs((v1^v2)*1.0) < eps;
}

struct Seg {
   Vec a, b;

   Seg(Vec _a, Vec _b) {
       a = _a;
       b = _b;
   }
   ld len() const {
       return (a - b).len();
   }

   bool isOnSeg(Vec p) const {
       return ((a-p)^(a-b)) == 0 && (a-p)*(b-p) <= 0;
   }
   Vec vec() const {
       return a-b;
   }

   friend istream& operator>>(istream& is, Seg& s) {
       cin >> s.a >> s.b;
       return is;
   }
   friend ostream& operator<<(ostream& os, const Seg& s) {
       cout << s.a << ' ' << s.b;
       return os;
   }
};
bool isSegIntersect(Seg s1, Seg s2) {
   if (isParallel(s1.vec(), s1.vec()))
       return s1.isOnSeg(s2.a) || s1.isOnSeg(s2.b) || s2.isOnSeg(s1.a) || s2.isOnSeg(s1.b);
   else
       return sign(s1.vec()^(s1.a-s2.a)) * sign(s1.vec()^(s1.a-s2.b)) <= 0 &&
              sign(s2.vec()^(s2.a-s1.a)) * sign(s2.vec()^(s2.a-s1.b)) <= 0;
}

Vec infv(INF, INF);
struct Line {
   C a, b, c;
   Line() {
       a = b = c = 0;
   }
   Line(C _a, C _b, C _c) {
       a = _a;
       b = _b;
       c = _c;
   }
   Line(Vec p1, Vec p2) {
       a = p1.y - p2.y;
       b = p2.x - p1.x;
       c = p1^p2;
   }
   Vec intersect(const Line &other) const {
       if (a*other.b == other.a*b) {
           return infv;
       }
       return Vec{(b*other.c-other.b*c)/(a*other.b-other.a*b),
                  (c*other.a-other.c*a)/(a*other.b-other.a*b)};
   }
   Vec proec(Vec p) const {
       Line l(p, p+Vec(a, b));
       return intersect(l);
   }
   ld dist(Vec p) const {
       return (p - proec(p)).len();
   }

   friend istream& operator>>(istream& is, Line& l) {
       cin >> l.a >> l.b >> l.c;
       return is;
   }
   friend ostream& operator>>(ostream& os, const Line& l) {
       cout << l.a << " " << l.b << " " << l.c;
       return os;
   }
};
bool isParallel(Line l1, Line l2) {
   return l1.a*l2.b == l2.a*l1.b;
}

int solve(ll tc) {
   cout << fixed;
   cout.precision(6);



   return 0;
}

int main() {
   IOS;

   ll t = 1;
//    cin >> t;
   forn(i, t) {
       solve(t);
   }

   return 0;
}
