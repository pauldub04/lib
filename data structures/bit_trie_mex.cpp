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

const int inf = 1e9, mod = 1e9+7, N = 1e7, LG = 25;
const ll INF = 1e18;
const ld eps = 1e-9;

struct Node {
    int to[2]{};
    int terminal = 0;
    int Xor = 0;
    int sum = 0;
    bool full = 0;
};

Node t[N];
int nf = 1;

bool bit(int x, int i) {
    return (x >> i)&1;
}

bool find(int x) {
    int v = 0;
    for (int i = LG; i >= 0; i--) {
        int c = bit(x, i);
        if (t[v].to[c] == 0)
            return 0;
        v = t[v].to[c];
    }
    return t[v].terminal;
}

void add(int x) {
    int is = !find(x);

    int v = 0;
    for (int i = LG; i >= 0; i--) {
        int c = bit(x, i);
        if (t[v].to[c] == 0)
            t[v].to[c] = nf++;
        t[v].sum += is;
        v = t[v].to[c];
    }
    t[v].terminal++;
    t[v].sum += is;
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

int query(int x) {
    int v = 0;
    t[0].Xor ^= x;

    int ans = 0;
    for (int i = LG; i >= 0; i--) {
//        cerr << i << ": ";

        if (bit(t[v].Xor, i))
            swap(t[v].to[0], t[v].to[1]);
        for (int j : {0, 1})
            if (t[v].to[j] != 0 && i != 0)
                t[t[v].to[j]].Xor ^= t[v].Xor;
        t[v].Xor = 0;

        if (t[v].to[0] == 0)
            return ans;

//        cerr << v << " " << t[t[v].to[0]].sum << " " << (1ll << i) << "\n";
        if (t[t[v].to[0]].sum == (1ll << i)) {
            ans += (1 << i);
            if (t[v].to[1] == 0)
                return ans;
            else
                v = t[v].to[1];
        } else
            v = t[v].to[0];
    }

    return ans;
}

int solve(ll tc) {
    int n, m; cin >> n >> m;

    while (n--) {
        int x; cin >> x;
        add(x);
    }
//    trav(0);

    while (m--) {
        int x; cin >> x;
        cout << query(x) << "\n";
    }

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