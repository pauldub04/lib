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
#define vin(a) for (auto& _ : (a)) {cin >> _;}
#define vout(a) {for (auto _ : (a)) {cout << _ << " ";} cout << "\n";}
#define forn(i, n) for (int (i) = 0; (i) < int(n); (i)++)
#define all(x) (x).begin(), (x).end()
#define sz(a) ((int) ((a).size()))

#define F first
#define S second
#define pb push_back

const int inf = 1e9;
const int mod = 1e9 + 7;
const ld eps = 1e-9;
const ll INF = 1e18 + 10;

vll t, a;
ll n;

inline ll f(ll x, ll y) {
    return x + y;
}
ll neutral = 0;

void build(ll x = 0, ll lx = 0, ll rx = n) {
    if (rx-lx == 1) {
        t[x] = a[lx];
        return;
    }
    ll m = (lx+rx) / 2;
    build(2*x+1, lx, m);
    build(2*x+2, m, rx);
    t[x] = f(t[2*x+1], t[2*x+2]);
}

ll get(ll l, ll r, ll x = 0, ll lx = 0, ll rx = n) {
    if (l <= lx && rx <= r)
        return t[x];
    if (l >= rx || lx >= r)
        return neutral;
    ll m = (lx+rx)/2;
    return f(get(l, r, 2*x+1, lx, m), get(l, r, 2*x+2, m, rx));
}

int solve(ll tc) {

    cin >> n;
    a.resize(n); vin(a);

    t.resize(4*n, neutral);
    build();

    ll q; cin >> q;
    while (q--) {
        ll l, r; cin >> l >> r;
        cout << get(l, r) << "\n";
    }

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
