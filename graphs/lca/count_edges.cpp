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

const int inf = 1e9, mod = 1e9+7, N = 1e5+5, LG = 21;
const ll INF = 1e18;
const ld eps = 1e-9;

ll n;
vector<vector<pll>> g;
vll2 up;
vll h;

void dfs(ll v, ll p=-1) {
    if (p != -1) {
        h[v] = h[p]+1;
        up[v][0] = p;
        for (int i = 1; i < LG; i++)
            up[v][i] = up[up[v][i-1]][i-1];
    }
    for (auto [to, num] : g[v])
        if (to != p)
            dfs(to, v);
}

ll lca(ll a, ll b) {
    if (h[a] < h[b])
        swap(a, b);

    ll d = h[a]-h[b];
    for (int i = 0; i < LG; i++)
        if ((d >> i)&1)
            a = up[a][i];
    if (a == b)
        return a;

    for (int i = LG-1; i >= 0; i--)
        if (up[a][i] != up[b][i]) {
            a = up[a][i];
            b = up[b][i];
        }
    return up[a][0];
}

vll sum, ans;

void dfs_count(ll v, ll p=-1) {
    for (auto to : g[v]) {
        if (to.F != p) {
            dfs_count(to.F, v);
            ans[to.S] = sum[to.F];
            sum[v] += sum[to.F];
        }
    }
}

int solve(ll tc) {
    cin >> n;

    g.resize(n);
    for (int i = 0; i < n-1; i++) {
        ll x, y; cin >> x >> y;
        x--; y--;
        g[x].pb({y, i});
        g[y].pb({x, i});
    }

    up.resize(n, vll(LG));
    h.resize(n);
    dfs(0);

    sum.resize(n);
    ans.resize(n-1);

    // считает количество проходов по пути
    //       o
    //       |
    //       | +1+1-2
    //       |
    //       o -2
    //      / \
    //     /   \
    //    /     \
    //   o +1    o +1
    // на выходе из рекурсии пересчитываем дп через сыновей

    ll m; cin >> m;
    while (m--) {
        ll x, y; cin >> x >> y; x--; y--;
        ll d = lca(x, y);
        sum[d] -= 2;
        sum[x]++;
        sum[y]++;
    }

    dfs_count(0);
    for (int i = 0; i < n-1; i++)
        cout << ans[i] << " ";

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
