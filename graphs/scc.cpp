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

const int inf = 1e9, mod = 1e9+7, N = 1e5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

ll n;
vll2 a;
vll2 g;
vll2 gr;
vector<bool> used;

vll t;
vll comp;

void dfs_init(ll v) {
    used[v] = 1;
    for (auto to : g[v])
        if (!used[to])
            dfs_init(to);
    t.pb(v);
}

void scc(ll v, ll c) {
    comp[v] = c;
    for (auto to : gr[v])
        if (comp[to] == -1)
            scc(to, c);
}

bool check(ll len) {
    g.assign(n, vll());
    gr.assign(n, vll());

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] > len || i == j)
                continue;
            g[i].pb(j);
            gr[j].pb(i);
        }
    }

    used.assign(n, 0);
    t.assign(0, 0);
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs_init(i);


    comp.assign(n, -1);
    ll c = 0;
    reverse(all(t));
    for (auto x : t)
        if (comp[x] == -1)
            scc(x, c++);

    return c == 1;
}

int solve(ll tc) {
    cin >> n;
    a.resize(n, vll(n));

    for (auto &x : a)
        vin(x);

    ll l = -1, r = inf+10;
    while (r-l > 1) {
        ll m = (l+r)/2;
        if (check(m))
            r = m;
        else
            l = m;
    }

    cout << r;

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