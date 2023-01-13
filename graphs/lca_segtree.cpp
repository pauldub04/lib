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

vector<int> g[N];
int h[N];
int pos[N];
vector<int> path;

void dfs(int v, int p=-1) {
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

inline int f(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    if (h[a] < h[b]) return a;
    else return b;
}

vector<int> t;
void build(int x=0, int lx=0, int rx=sz(path)) {
    if (rx-lx == 1) {
        t[x] = path[lx];
        return;
    }
    int m = (lx+rx)/2;
    build(2*x+1, lx, m);
    build(2*x+2, m, rx);
    t[x] = f(t[2*x+1], t[2*x+2]);
}

int get(int l, int r, int x=0, int lx=0, int rx=sz(path)) {
    if (l <= lx && rx <= r)
        return t[x];
    if (l >= rx || lx >= r)
        return -1;
    int m = (lx+rx)/2;
    return f(get(l, r, 2*x+1, lx, m), get(l, r, 2*x+2, m, rx));
}

int lca(int a, int b) {
    a = pos[a];
    b = pos[b];
    if (a > b)
        swap(a, b);
    return get(a, b+1);
}

int solve(ll tc) {
    int n, m; cin >> n >> m;

    for (int i = 1; i <= n-1; i++) {
        int x; cin >> x;
        g[x].pb(i);
    }
    dfs(0);

    t.resize(4*(sz(path)+5), -1);
    build();

    ll a1, a2; cin >> a1 >> a2;
    ll x, y, z; cin >> x >> y >> z;
    x %= n;
    y %= n;
    z %= n;

    ll ans = 0;
    for (int i = 0; i < m; i++) {
        ans += lca(a1, a2);
        a1 = (x*a1 + y*a2 + z)%n;
        a2 = (x*a2 + y*a1 + z)%n;
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