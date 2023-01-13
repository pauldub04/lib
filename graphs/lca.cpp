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

const int inf = 1e9, mod = 1e9+7, N = 5e5+5, LG = 20;
const ll INF = 1e18;
const ld eps = 1e-9;

ll up[N][LG];
ll h[N];

void add(ll a, ll b) {
    h[b] = h[a]+1;
    up[b][0] = a;
    for (int i = 1; i < LG; i++)
        up[b][i] = up[up[b][i-1]][i-1];
}

ll lca(ll a, ll b) {
    if (h[a] < h[b])
        swap(a, b);

    ll d = h[a]-h[b];
    for (int i = 0; i < LG; i++)
        if ((d>>i)&1)
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

int solve(ll tc) {
    ll k; cin >> k;

    while (k--) {
        str cmd; ll a, b;
        cin >> cmd >> a >> b; a--; b--;

        if (cmd == "ADD")
            add(a, b);
        else
            cout << lca(a, b)+1 << "\n";
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