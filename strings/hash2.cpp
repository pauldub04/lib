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

ll Q = 192;
ll q[N];
void precalc_pow() {
    q[0] = 1;
    for (int i = 1; i < N; i++)
        q[i] = (q[i-1]*Q)%mod;
}

vll build_hash(const str &s) {
    vll h(sz(s)+1);
    for (int i = 1; i <= sz(s); i++)
        h[i] = (h[i-1] + (s[i-1]-'a'+1) * q[i-1]) % mod;
    return h;
}

ll get(const vll &h, ll l, ll r) {
    return ((h[r]-h[l]+mod) * q[N-l-5]) % mod;
}

int solve(ll tc) {
    str s; cin >> s;
    vll h = build_hash(s);

    ll m; cin >> m;
    while (m--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;

        if (get(h, a-1, b) == get(h, c-1, d))
            cout << "Yes\n";
        else
            cout << "No\n";

    }

    return 0;
}

int main() {
    IOS;

    precalc_pow();

    ll tc = 1;
//    cin >> tc;
    forn(i, tc) {
        solve(i);
    }

    return 0;
}