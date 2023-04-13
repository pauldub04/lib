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

const int inf = 1e9, mod = 1e9+7, N = 1e5, LG = 17;
const ll INF = 1e18;
const ld eps = 1e-9;

int n, m, q;
vector<int> g[N];
int up[N][LG];
vector<int> t[N][LG];
vector<int> p[N];
int h[N];

vector<int> merge(const vector<int> &a, const vector<int> &b) {
    vector<int> res; res.reserve(sz(a)+sz(b));
    std::merge(all(a), all(b), back_inserter(res));
    res.erase(unique(all(res)), res.end());
    if (sz(res) > 10)
        res.resize(10);
    return std::move(res);
}

void dfs(int v, int pr=-1) {
    if (pr != -1) {
        h[v] = h[pr] + 1;
        up[v][0] = pr;
        t[v][0] = merge(p[pr], p[v]);
        for (int i = 1; i < LG; i++) {
            up[v][i] = up[up[v][i-1]][i-1];
            t[v][i] = merge(t[v][i-1], t[up[v][i-1]][i-1]);
        }
    }
    for (auto to : g[v])
        if (to != pr)
            dfs(to, v);
}

vector<int> ans(int a, int b) {
    auto res = merge(p[a], p[b]);
    if (h[a] < h[b])
        swap(a, b);
    int d = h[a]-h[b];
    for (int i = 0; i < LG; i++)
        if ((d>>i)&1) {
            res = merge(res, t[a][i]);
            a = up[a][i];
        }
    if (a == b)
        return res;
    for (int i = LG-1; i >= 0; i--)
        if (up[a][i] != up[b][i]) {
            res = merge(res, t[a][i]);
            res = merge(res, t[b][i]);
            a = up[a][i];
            b = up[b][i];
        }
    res = merge(res, t[a][0]);
    res = merge(res, t[b][0]);
    return std::move(res);
}

int solve() {
    cin >> n >> m >> q;

    for (int i = 0; i < n-1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        g[a].pb(b);
        g[b].pb(a);
    }

    for (int i = 0; i < m; i++) {
        int c; cin >> c;
        p[c-1].pb(i);
    }
    for (int i = 0; i < n; i++) {
        sort(all(p[i]));
        if (sz(p[i]) > 10)
            p[i].resize(10);
    }

    dfs(0);

    for (int i = 0; i < q; i++) {
        int v, u, a; cin >> v >> u >> a;
        v--; u--;
        auto c = ans(u, v);
        int s = min(sz(c), a);
        cout << s << " ";
        for (int j = 0; j < s; j++)
            cout << c[j]+1 << " ";
        cout << "\n";
    }

    return 0;
}

int main() {
    IOS;

    ll tc = 1;
//    cin >> tc;
    while (tc--) {
        solve();
    }

    return 0;
}
