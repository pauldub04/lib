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

#define vin(a) for (auto& q : (a)) {cin >> q;}
#define vout(a) {for (auto q : (a)) {cout << q << " ";} cout << "\n";}
#define vpout(a) for (auto q : (a)) {cout << q.first << " " << q.second << "\n";}

#define F first
#define S second

const int inf = 1e9;
const int mod = 1e9 + 7;
const ld eps = 1e-9;
const ll INF = 1e18 + 10;

ll bp(ll a, ll n) {
    ll res = 1;
    while(n) {
        if (n&1)
            res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

ll add(ll a, ll b) {
    return ((a%mod+mod)%mod + (b%mod+mod)%mod)%mod;
}

ll mult(ll a, ll b) {
    return ((a%mod+mod)%mod * (b%mod+mod)%mod)%mod;
}

ll divide(ll a, ll b) {
    return mult(a, bp((b%mod+mod)%mod, mod-2));
}

int solve(ll tc) {

    ll n; cin >> n;

    vector<bool> is_prime(n+1, true);
    vll pr;

    for (ll i = 2; i <= n; i++) {
        if (is_prime[i]) {
            pr.pb(i);

            for (ll j = i*i; j <= n; j += i)
                is_prime[j] = false;
        }
    }

    vll lp(n+1);
    vll pr2;

    for (ll i = 2; i <= n; i++) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr2.pb(i);
        }
        for (ll j = 0; j < sz(pr2) && pr2[j] <= lp[i] && i*pr2[j] <= n; j++)
            lp[i*pr2[j]] = pr2[j];
    }

    vout(pr);
    vout(pr2);

    return 0;
}

int main() {
    IOS;

    ll t = 1;
//    cin >> t;
    forn(i, t) {
        solve(t);
    }

    return 0;
}
