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

const int LG = 30;

vector<vector<pll>> g;
vll2 up, e;
vll h;

void dfs(ll v, ll p = -1) {
    if (p != -1) {
        h[v] = h[p] + 1;
        up[v][0] = p;
        for (int i = 1; i < LG; i++) {
            up[v][i] = up[up[v][i-1]][i-1];
            e[v][i] = min(e[v][i-1], e[up[v][i-1]][i-1]);
        }
    }

    for (auto to : g[v]) {
        e[to.F][0] = to.S;
        dfs(to.F, v);
    }
}

ll ans(ll a, ll b) {
    ll ans = inf;
    if (h[a] < h[b])
        swap(a, b);
    ll d = h[a]-h[b];
    for (int i = 0; i < LG; i++)
        if ((d>>i)&1) {
            ans = min(ans, e[a][i]);
            a = up[a][i];
        }
    if (a == b) return ans;
    for (int i = LG-1; i >= 0; i--)
        if (up[a][i] != up[b][i]) {
            ans = min({ans, e[a][i], e[b][i]});
            a = up[a][i];
            b = up[b][i];
        }
    return min({ans, e[a][0], e[b][0]});
}

int solve(ll tc) {

    ll n; cin >> n;
    g.resize(n);
    h.resize(n);
    up.resize(n, vll(LG));
    e.resize(n, vll(LG));

    for (int i = 0; i < n-1; i++) {
        ll x, y; cin >> x >> y;
        g[x-1].pb({i+1, y});
    }

    dfs(0);

    ll m; cin >> m;
    while (m--) {
        ll x, y; cin >> x >> y;
        x--; y--;
        cout << ans(x, y) << "\n";
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