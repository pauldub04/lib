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
#define all(x) (x).begin(), (x).end()
#define sz(a) int((a).size())
 
#define F first
#define S second
#define pb push_back
 
const int inf = 1e9, mod = 1e9+7, N = 1e5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

struct Edge {
    ll to;
    ll len;
};

struct Bfs0k {
    ll n;
    ll k;
    const vector<vector<Edge>>& g;

    Bfs0k(ll _n, ll _k, const vector<vector<Edge>>& _g) 
    : n(_n), k(_k), g(_g) {}

    pair<vll, vll> calcDistAncestor(ll s) {
        vector<bool> used(n, 0);
        vll dist(n, INF); dist[s] = 0;
        vll p(n, -1);

        vector<queue<ll>> q(k+1);
        ll cur = 0; // current level

        q[cur].push(s);
        ll total = 1;

        while (total > 0) {
            if (sz(q[cur]) == 0) {
                ++cur;
                cur %= sz(q);
                continue;
            }

            ll v = q[cur].front(); q[cur].pop();
            --total;
            if (used[v]) {
                continue;
            }
            used[v] = 1;

            for (auto [to, len] : g[v]) {
                if (used[to]) {
                    continue;
                }
                if (dist[v]+len < dist[to]) {
                    dist[to] = dist[v]+len;
                    p[to] = v;
                    q[(cur+len) % sz(q)].push(to);
                    ++total;
                }
            }
        }
        return {dist, p};
    }

    vll calcDist(ll s) {
        return calcDistAncestor(s).first;
    }
};

int solve() {
    ll n, m; cin >> n >> m;

    vector<vector<Edge>> g(n);
    for (int i = 0; i < m; ++i) {
        ll u, v, c; cin >> u >> v >> c;
        --u; --v;
        g[u].push_back({v, c});
        g[v].push_back({u, c});
    }
    ll s = 0, f = n-1;

    Bfs0k bfs(n, 2, g);
    auto dist = bfs.calcDist(s);

    if (dist[f] >= INF) {
        cout << "-1";
    } else {
        cout << dist[f];
    }

    return 0;
}
 
int main() {
    IOS;
    freopen("kefir.in", "r", stdin);
    freopen("kefir.out", "w", stdout);
 
    ll tc = 1;
    // cin >> tc;
    while (tc--) {
        solve();
    }
 
    return 0;
}
