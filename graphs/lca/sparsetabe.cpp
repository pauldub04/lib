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

const int inf = 1e9, mod = 1e9+7, N = 1e5, LG = 18;
const ll INF = 1e18;
const ld eps = 1e-9;

vll path, pos, h;
vll2 g;

void dfs(ll v, ll p=-1) {
    if (p != -1)
        h[v] = h[p] + 1;

    pos[v] = sz(path);
    path.pb(v);
    for (auto to : g[v])
        if (to != p) {
            dfs(to, v);
            path.pb(v);
        }
}

inline ll f(ll a, ll b) {
    return (h[a] < h[b]) ? a : b;
}

vll2 t;
void build() {
    t.resize(LG, vll(sz(path)));
    t[0] = path;
    for (int i = 1; i < LG; i++)
        for (int j = 0; j+(1ll<<i)-1 < sz(t[i]); j++)
            t[i][j] = f(t[i-1][j], t[i-1][j+(1ll<<(i-1))]);
}

ll get(ll l, ll r) {
    ll d = __lg(r-l+1);
    return f(t[d][l], t[d][r-(1<<d)+1]);
}

ll lca(ll a, ll b) {
    a = pos[a];
    b = pos[b];
    if (a > b)
        swap(a, b);
    return get(a, b);
    // без -1 (как в до) потому что спарстейбл на отрезках
}

int solve(ll tc) {
    ll n, m; cin >> n >> m;

    g.resize(n);
    for (int i = 1; i <= n-1; i++) {
        int x; cin >> x;
        g[x].pb(i);
    }

    h.resize(n);
    pos.resize(n);
    path.reserve(2*n);

    dfs(0);
    build();

    ll a1, a2, x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    x %= n; y %= n; z %= n;

    ll ans = 0, v = 0;
    for (int i = 0; i < m; i++) {
        v = lca((a1+v)%n, a2);
        ans += v;
        a1 = (x*a1 + y*a2 + z) % n;
        a2 = (x*a2 + y*a1 + z) % n;
    }
    cout << ans;

    return 0;
}

int main() {
    IOS;
    freopen("lca_rmq.in", "r", stdin);
    freopen("lca_rmq.out", "w", stdout);

    ll tc = 1;
//    cin >> tc;
    while (tc--) {
        solve(tc);
    }

    return 0;
}
