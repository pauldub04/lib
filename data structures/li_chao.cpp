// https://codeforces.com/problemset/problem/319/C
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> vll;
typedef vector< vll > vll2;
typedef pair<ll, ll> pll;
typedef string str;

// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// #define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
#define vin(x_points) {for (auto& _ : (x_points)) {cin >> _;}}
#define vout(x_points) {for (auto _ : (x_points)) {cout << _ << " ";} cout << "\n";}
#define all(x) (x).begin(), (x).end()
#define sz(x_points) int((x_points).size())

#define F first
#define S second
#define pb push_back

const int inf = 1e9, mod = 1e9+7, N = 1e5+10, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;


struct Line {
    ll k;
    ll b;
    ll get(ll x) const {
        return k*x + b;
    }
};
 
// li chao
vector<Line> tree;
vll x_points;
 
void add_line(Line cur, ll x=0, ll lx=0, ll rx=sz(x_points)) {
    ll m = (lx+rx)/2;
    bool left = cur.get(x_points[lx]) < tree[x].get(x_points[lx]);
    bool mid = cur.get(x_points[m]) < tree[x].get(x_points[m]);
    if (mid) {
        swap(tree[x], cur);
    }

    if (rx-lx == 1) {
        return;
    }
    if (left == mid) {
        add_line(cur, 2*x+2, m, rx);
    } else {
        add_line(cur, 2*x+1, lx, m);
    }
}
 
ll get_ans(ll i, ll x=0, ll lx=0, ll rx=sz(x_points)) {
    if (rx-lx == 1) {
        return tree[x].get(x_points[i]);
    }
 
    ll m = (lx+rx)/2;
    if (i < m) {
        return min(tree[x].get(x_points[i]), get_ans(i, 2*x+1, lx, m));
    } else {
        return min(tree[x].get(x_points[i]), get_ans(i, 2*x+2, m, rx));
    }
}


int solve() {
    ll n; cin >> n;
    x_points.resize(n); vin(x_points);
    vll b(n); vin(b);
 
    tree.resize(4*n, {0, INF});

    vll dp(n);
    dp[0] = 0;
    add_line({b[0], dp[0]});
 
    for (int i = 1; i < n; i++) {
        dp[i] = get_ans(i);
        add_line({b[i], dp[i]});
    }
    
    cout << dp.back();

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
