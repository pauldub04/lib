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
vll a, b;

void add(Line cur, ll x=0, ll lx=0, ll rx=n) {
    ll m = (lx+rx)/2;
    bool left = cur.get(a[lx]) < t[x].get(a[lx]);
    bool mid = cur.get(a[m]) < t[x].get(a[m]);
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
        return t[x].get(a[i]);

    ll m = (lx+rx)/2;
    if (i < m)
        return min(t[x].get(a[i]), get(i, 2*x+1, lx, m));
    else
        return min(t[x].get(a[i]), get(i, 2*x+2, m, rx));
}


int solve(ll tc) {
    cin >> n;

    t.resize(4*n, {0, INF});
    a.resize(n); vin(a);
    b.resize(n); vin(b);

    vll dp(n);
    add({b[0], 0});

    for (int i = 1; i < n; i++) {
        dp[i] = get(i);
        add({b[i], dp[i]});
    }

    cout << dp.back();

    return 0;
}

int main() {
//    IOS;

    ll tc = 1;
//    cin >> tc;
    forn(i, tc) {
        solve(i);
    }

    return 0;
}