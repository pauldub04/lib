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

const int inf = 1e9, mod = 1e9+7, N = 2e4+5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

ll edg;
ll n, m;
vector<pll> g[N];

vll pos;
vector<bool> used;
unordered_map<ll, bool> added;

vll2 ans;

void euler(ll v) {
    while (pos[v] < sz(g[v])) {
        auto to = g[v][pos[v]++];
        if (used[to.S])
            continue;
        used[to.S] = 1;
        euler(to.F);
        ans.back().pb(to.F);
        if (added[to.S])
            ans.pb({});
    }
}

int solve(ll tc) {
    cin >> n >> m;

    edg = 0;
    for (int i = 0; i < m; i++) {
        ll x, y; cin >> x >> y;
        x--; y--;
        g[x].pb({y, edg});
        g[y].pb({x, edg++});
    }

    vll c;
    for (int i = 0; i < n; i++) {
        if (sz(g[i])&1)
            c.pb(i);
    }
    assert(sz(c)%2==0);

    for (int i = 2; i < sz(c); i+=2) {
        added[edg] = 1;
        g[c[i]].pb({c[i+1], edg});
        g[c[i+1]].pb({c[i], edg++});
    }

    ll start = 0;
    if (!c.empty())
        start = c[0];

    used.resize(edg);
    pos.resize(n);

    ans.pb({});
    euler(start);
    ans.back().pb(start);

    ll cnt = count_if(all(ans), [] (auto &x) {
        return sz(x)!=1;
    });

    cout << cnt << "\n";
    for (auto &x : ans)
        if (sz(x) != 1) {
            for (auto y : x)
                cout << y+1 << " ";
            cout << '\n';
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