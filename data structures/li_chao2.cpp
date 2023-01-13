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

const int inf = 1e9, mod = 1e9+7, N = 2e6+5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

const int diff = 1e6;

struct Line {
    ll k;
    ll b;
    ll get(ll x) const {
        return k*x + b;
    }
};

// li chao
vector<Line> t;

ll n;
struct Rect {
    ll x;
    ll y;
    ll a;
};
vector<Rect> a;

void add(Line cur, ll x=0, ll lx=0, ll rx=n) {
    ll m = (lx+rx)/2;
    bool left = cur.get(a[lx].y) < t[x].get(a[lx].y);
    bool mid = cur.get(a[m].y) < t[x].get(a[m].y);
    if (mid)
        swap(t[x], cur);

    if (rx-lx == 1)
        return;
    if (left == mid)
        add(cur, 2*x+2, m, rx);
    else
        add(cur, 2*x+1, lx, m);
}

ll get(ll i, ll x=0, ll lx=0, ll rx=n) {
    if (rx-lx == 1)
        return t[x].get(a[i].y);

    ll m = (lx+rx)/2;
    if (i < m)
        return min(t[x].get(a[i].y), get(i, 2*x+1, lx, m));
    else
        return min(t[x].get(a[i].y), get(i, 2*x+2, m, rx));
}


int solve(ll tc) {
    cin >> n;

    t.resize(4*n, {0, INF});
    a.resize(n);
    for (auto &x : a)
        cin >> x.x >> x.y >> x.a;

    sort(all(a), [] (auto x, auto y) {
        return x.x < y.x;
    });

    vll dp(n);
    dp[0] = a[0].x*a[0].y - a[0].a;
    add({a[0].x, -dp[0]});

    for (int i = 1; i < n; i++) {
        dp[i] = a[i].x*a[i].y-a[i].a;
        dp[i] = max(dp[i], dp[i]-get(i));
        add({a[i].x, -dp[i]});
    }

    cout << *max_element(all(dp));

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