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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

#define vin(a) for (auto& _ : (a)) {cin >> _;}
#define vout(a) {for (auto _ : (a)) {cout << _ << " ";} cout << "\n";}
#define vpout(a) for (auto _ : (a)) {cout << _.first << " " << _.second << "\n";}

#define F first
#define S second

const int inf = 1e9;
const int mod = 1e9 + 7;
const ld eps = 1e-9;
const ll INF = 1e18 + 10;

const int MAXN = 260;

ll n, m;
vll2 g;
vll lm, rm;
bitset<MAXN> used(0);

bool kuhn(ll v) {
    if (used[v])
        return false;
    used[v] = true;

    for (auto to : g[v])
        if (rm[to] == -1 || kuhn(rm[to])) {
            rm[to] = v;
            lm[v] = to;
            return true;
        }
    return false;
}

int solve(ll tc) {

    cin >> n >> m;
    g.resize(n);
    rm.resize(m, -1);
    lm.resize(n, -1);

    for (int i = 0; i < n; i++) {
        ll b; cin >> b;
        while (b) {
            g[i].pb(b-1);
            if (lm[i] == -1 && rm[b-1] == -1) {
                lm[i] = b-1;
                rm[b-1] = i;
            }
            cin >> b;
        }
    }

    for (int run = 1; run; ) {
        run = 0, used = 0;
        for (int i = 0; i < n; i++)
            if (lm[i] == -1 && kuhn(i))
                run = 1;
    }

    vector<pll> ans;
    for (int i = 0; i < m; i++)
        if (rm[i] != -1)
            ans.pb({rm[i]+1, i+1});

    cout << sz(ans) << "\n";
    vpout(ans);

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
