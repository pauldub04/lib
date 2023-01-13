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

ll Q = 195;
ll q[N];

void precalc_pow() {
    q[0] = 1;
    for (int i = 1; i < N; i++)
        q[i] = (q[i-1]*Q)%mod;
}

vll build_hash(const str &s) {
    vll h(sz(s)+1);
    for (int i = 1; i < sz(h); i++)
        h[i] = (h[i-1] + (s[i-1]-'a'+1)*q[i-1])%mod;
    return h;
}

ll get(const vll &h, ll l, ll r) {
    return (((h[r]-h[l]+mod)%mod)*q[N-l-2])%mod;
}

int solve(ll tc) {
    str s; cin >> s;
    vll h = build_hash(s);

    ll k; cin >> k;
    while (k--) {
        ll l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        l1--; l2--;

        if (get(h, l1, r1) == get(h, l2, r2)) {
            cout << "=\n";
            continue;
        }

        ll l = 0, r = min(r1-l1, r2-l2)+1;
        while (r-l > 1) {
            ll m = (l+r)/2;
            if (get(h, l1, l1+m) == get(h, l2, l2+m))
                l = m;
            else
                r = m;
        }

        if (l == r1-l1) {
            cout << "<\n";
            continue;
        } else if (l == r2-l2) {
            cout << ">\n";
            continue;
        }

        if (s[l1+l] < s[l2+l])
            cout << "<\n";
        else
            cout << ">\n";
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