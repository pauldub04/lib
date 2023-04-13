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

const int inf = 1e9, mod = 1e9+7, N = 1e6, LG = 21;
const ll INF = 1e18;
const ld eps = 1e-9;

vll2 g;
vll h, pos;
vll path;

void dfs(ll v, ll p=-1) {
    if (p != -1)
        h[v] = h[p]+1;

    pos[v] = sz(path);
    path.pb(v);
    for (auto to : g[v])
        if (to != p) {
            dfs(to, v);
            path.pb(v);
        }
}

inline ll f(ll a, ll b) {
    if (a == -1) return b;
    if (b == -1) return a;
    if (h[a] < h[b]) return a;
    else return b;
}

vll t;
void build(ll x=0, ll lx=0, ll rx=sz(path)) {
    if (rx-lx == 1) {
        t[x] = path[lx];
        return;
    }
    ll m = (lx+rx)/2;
    build(2*x+1, lx, m);
    build(2*x+2, m, rx);
    t[x] = f(t[2*x+1], t[2*x+2]);
}

ll get(ll l, ll r, ll x=0, ll lx=0, ll rx=sz(path)) {
    if (l <= lx && rx <= r)
        return t[x];
    if (l >= rx || lx >= r)
        return -1;
    ll m = (lx+rx)/2;
    return f(get(l, r, 2*x+1, lx, m), get(l, r, 2*x+2, m, rx));
}

ll lca(ll a, ll b) {
    a = pos[a];
    b = pos[b];
    if (a > b)
        swap(a, b);
    return get(a, b+1);
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

    t.resize(4*sz(path), -1);
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

    ll tc = 1;
//    cin >> tc;
    forn(i, tc) {
        solve(i);
    }

    return 0;
}
