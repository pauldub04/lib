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

const int inf = 1e9, mod = 1e9+7, N = 1e3+5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

ll n;
vector<multiset<pll>> g;
vll ans;

void euler(ll v) {
    while (!empty(g[v])) {
        auto to = *g[v].begin();
        g[v].erase(g[v].begin());
        g[to.F].erase(g[to.F].find({v, to.S}));
        euler(to.F);
        ans.pb(to.F);
    }
}

int solve(ll tc) {
    cin >> n;

    g.resize(n);
    for (int i = 0; i < n; i++) {
        ll m; cin >> m;
        while (m--) {
            ll x, l; cin >> x >> l;
            g[i].insert({x-1, l});
        }
    }

    ll cnt = count_if(all(g), [] (auto &v) {
        return sz(v)&1;
    });


    ll start = 0;
    if (cnt == 2)
        start = find_if(all(g), [] (auto &v) {
            return sz(v)&1;
        })-g.begin();


    euler(start);
    ans.pb(start);

    reverse(all(ans));
    cout << sz(ans)-1 << "\n";
    for (auto x : ans)
        cout << x+1 << " ";

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