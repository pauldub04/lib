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

vll zfunc(const str &s) {
    vll z(sz(s));
    ll l = 0;

    for (int i = 1; i < sz(z); i++) {
        if (l+z[l] > i)
            z[i] = min(z[i-l], l+z[l]-i);

        while (i+z[i] < sz(s) && s[z[i]] == s[i+z[i]])
            z[i]++;

        if (i+z[i] > l+z[l])
            l = i;
    }
    return z;
}

int solve(ll tc) {
    str s; cin >> s;
    vll z = zfunc(s);

    vll p(sz(s));
    for (int i = 0; i < sz(z); i++)
        if (i+z[i]-1 >= 0)
            p[i+z[i]-1] = max(p[i+z[i]-1], z[i]);

    for (int i = sz(p)-2; i > 0; i--)
        if (p[i+1] >= 1)
            p[i] = max(p[i], p[i+1]-1);
        
    vout(p);

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