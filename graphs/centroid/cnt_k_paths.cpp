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

ll n, k;

vll2 g;
vector<bool> deleted;
vll subtree_size;

void calc_subtree_size(ll v, ll p=-1) {
    subtree_size[v] = 1;
    for (auto to : g[v]) {
        if (to == p || deleted[to]) {
            continue;
        }
        calc_subtree_size(to, v);
        subtree_size[v] += subtree_size[to];
    }
}

ll centroid(ll v, ll tree_size, ll p=-1) {
    for (auto to : g[v]) {
        if (to == p || deleted[to]) {
            continue;
        }
        if (subtree_size[to]*2 > tree_size) {
            return centroid(to, tree_size, v);
        }
    }
    return v;
}

void dfs(ll v, ll dist, vll& distances, ll p) {
    if (dist < sz(distances)) {
        ++distances[dist];
    }
    for (auto to : g[v]) {
        if (to == p || deleted[to]) {
            continue;
        }
        dfs(to, dist+1, distances, v);
    }
}

ll ans = 0;
void calc_ans(ll root) {
    calc_subtree_size(root);
    ll v = centroid(root, subtree_size[root]);

    vll current(k+1);
    current[0] = 1;

    for (auto to : g[v]) {
        if (deleted[to]) {
            continue;
        }

        vll from_v(k+1);
        dfs(to, 1, from_v, v);

        for (int dist = 0; dist < sz(from_v); ++dist) {
            if (dist > k) {
                continue;
            }
            ans += current[k-dist] * from_v[dist];
        }

        for (int dist = 0; dist < sz(from_v); ++dist) {
            current[dist] += from_v[dist];
        }
    }

    deleted[v] = 1;
    for (auto to : g[v]) {
        if (deleted[to]) {
            continue;
        }
        calc_ans(to);
    }
}


int solve() {
    cin >> n >> k;

    g.resize(n);
    deleted.resize(n);
    subtree_size.resize(n);
    for (int i = 0; i < n-1; ++i) {
        ll a, b; cin >> a >> b;
        --a; --b;
        g[a].pb(b);
        g[b].pb(a);
    }
 
    calc_ans(0);
    cout << ans;

    return 0;
}

int main() {
    IOS;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    ll tc = 1;
    // cin >> tc;
    while (tc--) {
        solve();
    }

    return 0;
}
