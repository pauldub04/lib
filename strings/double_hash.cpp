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

const int inf = 1e9, mod1 = 1e9+7, mod2 = 998244353, N = 1e5+5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

ll Q1 = 192, Q2 = 831;
ll q1[N], q2[N];

void precalc_pow() {
    q1[0] = 1;
    for (int i = 1; i < N; i++)
        q1[i] = (q1[i-1]*Q1)%mod1;

    q2[0] = 1;
    for (int i = 1; i < N; i++)
        q2[i] = (q2[i-1]*Q2)%mod2;
}

vector<pll> build_hash(const str &s) {
    vector<pll> h(sz(s)+1);
    for (int i = 1; i <= sz(s); i++)
        h[i] = {(h[i-1].F+(s[i-1]-'a'+1)*q1[i-1])%mod1, (h[i-1].S+(s[i-1]-'a'+1)*q2[i-1])%mod2};
    return h;
}

pll get(const vector<pll> &h, ll l, ll r) {
    return {((h[r].F-h[l].F+mod1)*q1[N-l-5])%mod1, ((h[r].S-h[l].S+mod2)*q2[N-l-5])%mod2};
}

str a, b;
vector<pll> ha, hb;

bool check(ll x) {
    set<pll> s;
    for (int i = 0; i <= sz(a)-x; i++)
        s.insert(get(ha, i, i+x));

    for (int i = 0; i <= sz(b)-x; i++)
        if (s.find(get(hb, i, i+x)) != s.end())
            return 1;

    return 0;
}

int solve(ll tc) {
    ll n; cin >> n;
    cin >> a >> b;
    ha = build_hash(a), hb = build_hash(b);

    ll l = 0, r = INF;
    while (r-l > 1) {
        ll m = (l+r)/2;
        if (check(m))
            l = m;
        else
            r = m;
    }

    ll x = l;
    set<pll> s;
    for (int i = 0; i <= sz(a)-x; i++)
        s.insert(get(ha, i, i+x));

    for (int i = 0; i <= sz(b)-x; i++)
        if (s.find(get(hb, i, i+x)) != s.end()) {
            cout << b.substr(i, x);
            return 0;
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