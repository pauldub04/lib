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

ll n;
vll a, t;

inline ll f(ll x, ll y) {
    return max(x, y);
}
ll neutral = -inf;

void build(ll x = 0, ll lx = 0, ll rx = n) {
    if (rx-lx == 1)
        return;

    ll m = (lx + rx) / 2;
    build(2*x+1, lx, m);
    build(2*x+2, m, rx);

    t[x] = f(t[2*x+1], t[2*x+2]);
}

ll ans(ll l, ll r, ll x = 0, ll lx = 0, ll rx = n) {
    if (l <= lx && rx <= r)
        return t[x];
    if (lx >= r || l >= rx)
        return neutral;

    ll m = (lx + rx) / 2;
    return f(ans(l, r, 2*x+1, lx, m), ans(l, r, 2*x+2, m, rx));
}

void upd(ll i, ll v, ll x = 0, ll lx = 0, ll rx = n) {
    if (rx - lx == 1) {
        t[x] = v;
        return;
    }

    ll m = (lx + rx) / 2;
    if (i < m)
        upd(i, v, 2*x+1, lx, m);
    else
        upd(i, v, 2*x+2, m, rx);

    t[x] = f(t[2*x+1], t[2*x+2]);
}

int solve(ll tc) {

    cin >> n;
    a.resize(n); vin(a);

    n = (1 << (int) ceil(log2(n)));
    t.resize(2*n-1);

    for (int i = 0; i < sz(a); i++)
        t[n-1+i] = a[i];
    build();

    ll m; cin >> m;
    while (m--) {
        char c; cin >> c;
        if (c == 's') {
            ll l, r; cin >> l >> r;
            cout << ans(l-1, r) << ' ';
        } else {
            ll i, v; cin >> i >> v;
            upd(i-1, v);
        }
    }

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