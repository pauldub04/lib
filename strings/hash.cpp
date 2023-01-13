#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector< vll > vll2;
typedef pair<ll, ll> pll;

#define pb push_back
#define pop_it push_back
#define all(x) (x).begin(), (x).end()
#define sz(a) ((int) ((a).size()))
#define forn(i, n) for (int (i) = 0; (i) < int(n); (i)++)
#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)

#define vin(a) for (auto& _ : (a)) {cin >> _;}
#define vout(a) {for (auto _ : (a)) {cout << _ << " ";} cout << "\n";}
#define vpout(a) for (auto _ : (a)) {cout << _.first << " " << _.second << "\n";}

#define F first
#define S second

const int inf = 1e9;
const int mod = 1e9 + 7;
const ld eps = 1e-9;
const ll INF = 1e18 + 10;

vll q(1e5+10);
ll Q = 604;

void calc_pow() {
    q[0] = 1;
    for (int i = 1; i < sz(q); i++)
        q[i] = q[i-1] * Q % mod;
}

ll hash_substring(const vll& h, ll l, ll r) {
    return (h[r] - h[l] + mod) * q[sz(h)-1-l] % mod;
}

bool is_equal(const vll& h1, ll l1, ll r1, const vll& h2, ll l2, ll r2) {
    return hash_substring(h1, l1, r1) == hash_substring(h2, l2, r2);
}

vll build_hash(const string &s) {
    vll h(sz(s)+1);
    for (int i = 1; i < sz(h); i++)
        h[i] = (h[i-1] + (s[i-1]-'a'+1) * q[i-1]) % mod;
    return h;
}


int solve(ll tc) {
    string s; cin >> s;
    calc_pow();

    vll h = build_hash(s);

    ll n; cin >> n;
    while (n--) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a--; b--; c--; d--;

        if (is_equal(h, a, b+1, h, c, d+1))
            cout << "Yes\n";
        else
            cout << "No\n";
    }

    return 0;
}

int main() {
//    IOS;

    ll t = 1;
//    cin >> t;
    forn(i, t) {
        solve(t);
    }

    return 0;
}
