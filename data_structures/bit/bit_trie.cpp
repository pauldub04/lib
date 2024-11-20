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

const int inf = 1e9, mod = 1e9+7, N = 5e6, LG = 32;
const ll INF = 1e18;
const ld eps = 1e-9;

const int alph = 2;

struct Node {
    ll to[alph] = {};
    ll terminal = 0;
    ll sum = 0;
};
Node t[N];
ll nf = 1;

bool bit(ll x, ll i) {
    return (x >> i)&1;
}

void add(ll x) {
    ll v = 0;
    for (int i = LG; i >= 0; i--) {
        ll c = bit(x, i);
        if (t[v].to[c] == 0)
            t[v].to[c] = nf++;
        t[v].sum++;
        v = t[v].to[c];
    }
    t[v].terminal++;
    t[v].sum++;
}

vll q;
void trav(ll v) {
    ll cnt = 0;
    for (int i = 0; i < 2; i++)
        if (t[v].to[i] != 0 && t[t[v].to[i]].sum != 0) {
            q.pb(i);
            trav(t[v].to[i]);
            q.pop_back();
            cnt++;
        }
    if (cnt == 0) {
        for (auto x : q)
            cerr << x;
        cerr << "\n";
    }
}

void del(ll x) {
    ll v = 0;
    for (int i = LG; i >= 0; i--) {
        ll c = bit(x, i);
        if (t[v].to[c] == 0)
            t[v].to[c] = nf++;
        t[v].sum--;
        v = t[v].to[c];
    }
    t[v].terminal--;
    t[v].sum--;
}


ll get(ll x) {
    ll v = 0;

    ll ans = 0;
    for (int i = LG; i >= 0; i--) {
        bool c = !bit(x, i);
        if (t[v].to[int(c)] == 0 || t[t[v].to[c]].sum == 0)
            c = !c;
        if (c)
            ans += (1ll << i);
        v = t[v].to[int(c)];
    }

    return ans;
}


int solve(ll tc) {
    ll n; cin >> n;
    add(0);

    while (n--) {
        char c; ll x;
        cin >> c >> x;

        if (c == '+')
            add(x);
        else if (c == '-')
            del(x);
        else
            cout << (get(x)^x) << "\n";
    }

    return 0;
}

int main() {
//    IOS;

    ll tc = 1;
//    cin >> tc;
    forn(i, tc) {
        solve(i);
    }

    return 0;
}