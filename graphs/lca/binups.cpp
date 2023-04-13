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
#define sz(a) ((int) ((a).size()))

#define F first
#define S second
#define pb push_back

const int inf = 1e9, mod = 1e9+7, N = 1e5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

ll n;

vll h;
vll2 up;
vll2 g;

void dfs(ll v, ll p = -1) {
    if (p != -1) {
        h[v] = h[p] + 1;
        up[v][0] = p;
        for (int i = 1; i < LG; i++)
            up[v][i] = up[up[v][i-1]][i-1];
    }

    for (auto to : g[v])
        if (to != p)
            dfs(to, v);
}

ll lca(ll a, ll b) {
    if (h[a] > h[b])
        swap(a, b);

    ll d = h[b]-h[a];
    for (int i = 0; i < LG; i++)
        if ((d>>i)&1)
            b = up[b][i];

    if (a == b)
        return a;

    for (int i = LG-1; i >= 0; i--)
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    return up[a][0];
}

int solve(ll tc) {
    cin >> n;

    g.resize(n);
    for (int i = 0; i < n-1; i++) {
        ll u, v; cin >> u >> v;
        --u; --v;
        g[u].pb(v);
        g[v].pb(u);
    }

    ll start = 0;
    h.resize(n);
    up.resize(n, vll(LG, start));

    dfs(start);

    ll q; cin >> q;
    while (q--) {
        ll a, b; cin >> a >> b;
        --a; --b;
        cout << lca(a, b) + 1 << "\n";
    }

    return 0;
}

int main() {
    IOS;

    ll tc = 1;
//    cin >> tc;
    while (tc--) {
        solve(tc);
    }

    return 0;
}
