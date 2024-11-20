#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> vll;
typedef vector< vll > vll2;
typedef pair<ll, ll> pll;
typedef string str;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
#define vin(a) {for (auto& _ : (a)) {cin >> _;}}
#define vout(a) {for (auto _ : (a)) {cout << _ << " ";} cout << "\n";}
#define forn(i, n) for (int (i) = 0; (i) < int(n); (i)++)
#define all(x) (x).begin(), (x).end()
#define sz(a) ((int) ((a).size()))

#define F first
#define S second
#define pb push_back

const int inf = 1e9, mod = 1e9+7, N = 2e4+5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

const int c = 1024;
struct Q {
    ll l;
    ll r;
    ll i;
};

ll n, m;
vector<Q> b;
vll ans_query;


vll t;
ll sum(ll x) {
    ll ans = 0;
    for (ll i = x; i >= 0; i = (i&(i+1))-1)
        ans += t[i];
    return ans;
}
ll sum(ll l, ll r) {
    return sum(r)-sum(l-1);
}
void update(ll x, ll add) {
    for (ll i = x; i < n; i = (i|(i+1)))
        t[i] += add;
}


void insert(ll x) {
    update(x, 1);
}
void erase(ll x) {
    update(x, -1);
}

int solve(ll tc) {
    cin >> n;
    vll a(n); vin(a);
    b.resize(n/c+1);
    t.resize(n);

    cin >> m;
    ans_query.resize(m);

    for (int i = 0; i < m; i++) {
        ll l, r; cin >> l >> r;
        b.pb({l-1, r-1, i});
    }

    sort(all(b), [] (Q x, Q y) {
        if (x.l/c == y.l/c)
            return x.r < y.r;
        return x.l/c < y.l/c;
    });

    vll coord = a;
    sort(all(coord));
    coord.erase(unique(all(coord)), coord.end());
    for (int i = 0; i < n; i++)
        a[i] = lower_bound(all(coord), a[i])-coord.begin();

    ll l = 0, r = 0;
    insert(a[l]);
    ll ans = 0;

    for (auto q : b) {
        while (r < q.r) {
            r++;
            ans += sum(a[r]+1, sz(t)-1);
            insert(a[r]);
        }
        while (r > q.r) {
            ans -= sum(a[r]+1, sz(t)-1);
            erase(a[r]);
            r--;
        }
        while (l < q.l) {
            ans -= sum(a[l]-1);
            erase(a[l]);
            l++;
        }
        while (l > q.l) {
            l--;
            ans += sum(a[l]-1);
            insert(a[l]);
        }

        ans_query[q.i] = ans;
    }

    for (auto x : ans_query)
        cout << x << "\n";

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