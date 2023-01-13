#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
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

const int inf = 1e9, mod = 1e9+7, N = 3e5+10, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

const int c = 700;

struct Q {
    ll l;
    ll r;
    ll i;
};

ll n, m;
vector<vector<Q>> v;
vll a;
vll ans, cnt;

ll res = 0;
void insert(ll x) {
    cnt[x]++;
    if (cnt[x] == 1)
        res++;
}
void erase(ll x) {
    cnt[x]--;
    if (cnt[x] == 0)
        res--;
}

int solve(ll tc) {
    cin >> n;
    a.resize(n); vin(a);
    cnt.resize(n+10);
    v.resize(n/c+5);

    ll time=1;
    unordered_map<ll, ll> color;
    for (int i = 0; i < n; i++)
        if (color[a[i]] == 0)
            a[i] = color[a[i]] = time++;
        else {
            a[i] = color[a[i]];
        }


    cin >> m;
    ans.resize(m);
    for (int i = 0; i < m; i++) {
        ll l, r; cin >> l >> r;
        v[l/c].pb({l-1, r-1, i});
    }

    for (int i = 0; i < sz(v); i++)
        sort(all(v[i]), [] (Q x, Q y) {
            return x.r < y.r;
        });

    for (int i = 0; i < sz(v); i++) {
        ll l = i*c, r = i*c;
        res = 0;
        if (!v[i].empty()) {
            cnt.assign(n+10, 0);
            insert(a[l]);
        }

        for (auto q : v[i]) {
            while (l < q.l) {
                erase(a[l]);
                l++;
            }
            while (l > q.l) {
                l--;
                insert(a[l]);
            }
            while (r < q.r) {
                r++;
                insert(a[r]);
            }
//            while (r > q.r) {
//                erase(a[r]);
//                r--;
//            }

            ans[q.i] = res;
        }
    }

    for (auto x : ans)
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