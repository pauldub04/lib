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

const int inf = 1e9, mod = 1e9+7, N = 1e5+5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

ll t[N];
ll a[N];
ll n, k;

ll sum(ll x) {
    ll res = 0;
    for (ll i = x; i > 0; i -= i&-i)
        res += t[i];
    return res;
}

ll sum(ll l, ll r) {
    return sum(r)-sum(l-1);
}

void add(ll x, ll v) {
    for (ll i = x; i <= n; i += i&-i)
        t[i] += v;
}

int solve(ll tc) {

    cin >> n >> k;

    while (k--) {
        char type; cin >> type;
        if (type == 'A') {
            ll i, x; cin >> i >> x;
            add(i, x-a[i]);
            a[i] = x;
        } else {
            ll l, r; cin >> l >> r;
            cout << sum(l, r) << "\n";
        }
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