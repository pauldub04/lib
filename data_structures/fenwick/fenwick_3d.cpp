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

const int inf = 1e9, mod = 1e9+7, N = 130, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

ll t[N][N][N];
ll n;

ll sum(ll _x, ll _y, ll _z) {
    ll res = 0;
    for (ll x = _x; x >= 0; x = (x&(x+1))-1)
        for (ll y = _y; y >= 0; y = (y&(y+1))-1)
            for (ll z = _z; z >= 0; z = (z&(z+1))-1)
                res += t[x][y][z];
    return res;
}

ll sum(ll x1, ll y1, ll z1, ll x2, ll y2, ll z2) {
    x1--; y1--; z1--;
    return
        + sum(x2, y2, z2)
        - sum(x2, y1, z2)
        + sum(x1, y1, z2)
        - sum(x1, y2, z2)
        + sum(x2, y1, z1)
        - sum(x1, y1, z1)
        + sum(x1, y2, z1)
        - sum(x2, y2, z1);
}

void add(ll _x, ll _y, ll _z, ll k) {
    for (ll x = _x; x < n; x = x|(x+1))
        for (ll y = _y; y < n; y = y|(y+1))
            for (ll z = _z; z < n; z = z|(z+1))
                t[x][y][z] += k;
}

int solve(ll tc) {
    cin >> n;

    while (1) {
        ll m; cin >> m;
        if (m == 1) {
            ll x, y, z, k; cin >> x >> y >> z >> k;
            add(x, y, z, k);
        } else if (m == 2) {
            ll x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << sum(x1, y1, z1, x2, y2, z2) << "\n";
        } else break;
    }

    return 0;
}

int main() {
//    IOS;

    ll tc = 1;
//    cin >> tc;
    forn(i, tc) {
        solve(i);
    }

    return 0;
}