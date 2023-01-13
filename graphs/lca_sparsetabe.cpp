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

vector<vector<int>> t;
void build() {
    t.resize(LG, vector<int>(sz(path)));
    t[0] = path;
    for (int i = 1; i < LG; i++)
        for (int j = 0; j+(1ll<<i)-1 < sz(path); j++)
            t[i][j] = f(t[i-1][j], t[i-1][j+(1ll<<(i-1))]);
}

int get(int l, int r) {
    int d = __lg(r-l+1);
    return f(t[d][l], t[d][r-(1<<d)+1]);
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