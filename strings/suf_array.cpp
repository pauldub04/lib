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

vll suf_array(str s) {
    s += '$';
    int n = sz(s);
    vll p, c(n);
    p.reserve(n);
    ll cls = 0;

    map<char, vll> t;
    for (int i = 0; i < n; i++)
        t[s[i]].pb(i);

    for (auto &x : t) {
        for (auto u : x.S) {
            c[u] = cls;
            p.pb(u);
        }
        cls++;
    }

    for (int l = 1; cls < n; l++) {
        vll2 a(cls);
        vll nc(n), np;
        np.reserve(n);
        ll d = (1ll << (l-1));
        ll ncls = 0;

        for (int i = 0; i < n; i++) {
            ll k = (p[i]-d+n) % n;
            a[c[k]].pb(k);
        }

        for (int i = 0; i < cls; i++) {
            for (int j = 0; j < sz(a[i]); j++) {
                if (j == 0 || c[(a[i][j]+d) % n] != c[(a[i][j-1]+d) % n])
                    ncls++;
                nc[a[i][j]] = ncls - 1;
                np.pb(a[i][j]);
            }
        }

        c = move(nc);
        p = move(np);
        cls = ncls;
    }

    return p;
}

int solve(ll tc) {
    str s = "abbaab";

    vll a = suf_array(s);
    vout(a);

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