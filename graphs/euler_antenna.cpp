#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

ll n;

struct Frag {
    ll m, s;
    ll l, r;
};
vector<Frag> v;

unordered_map<ll, ll> code;
unordered_map<ll, ll> decode;
ll t = 1;
vector<vector<pll>> g;
vll in, out;
vll nfree;
vector<bool> used;
vector<bool> vis;
vll ans;

void euler(ll u) {
    vis[u] = 1;
    while (nfree[u] < sz(g[u])) {
        auto to = g[u][nfree[u]++];
        if (!used[to.S]) {
            used[to.S] = 1;
            euler(to.F);
            ans.pb(to.S+1);
        }
    }
}

bool build(ll d) {
    ans.clear();
    code.clear();
    decode.clear();
    t = 1;

    vector<pair<pll, ll>> e;
    e.reserve(n);
    for (int i = 0; i < n; i++) {
        ll a = v[i].l, b = d-v[i].r;

        if (code[a] == 0)
            code[a] = t++;
        if (code[b] == 0)
            code[b] = t++;

        decode[code[a]] = a;
        decode[code[b]] = b;

        e.pb({{code[a], code[b]}, i});
    }

    g.assign(t, vector<pll>(0));
    nfree.assign(t, 0);
    in.assign(t, 0);
    out.assign(t, 0);
    for (auto x : e) {
        g[x.F.F].pb({x.F.S, x.S});
        in[x.F.S]++;
        out[x.F.F]++;
    }

    ll s = -1, f = -1;
    ll bad = 0;
    for (int i = 1; i < t; i++)
        if (in[i] != out[i]) {
            if (out[i]-1 == in[i]) {
                if (s != -1)
                    return 0;
                s = i;
            }
            if (out[i]+1 == in[i]) {
                if (f != -1)
                    return 0;
                f = i;
            }
            bad++;
        }

    if (bad != 0 && (s == -1 || f == -1))
        return 0;
    if (bad == 0)
        s = 1;

    used.assign(n, 0);
    vis.assign(t, 0);
    euler(s);

    for (int i = 1; i < t; i++)
        if (!vis[i] && sz(g[i]) > 0)
            return 0;

    if (count(all(used), 0) != 0)
        return 0;

    reverse(all(ans));
    return 1;
}


int solve(ll tc) {
    cin >> n;
    v.resize(n);

    unordered_set<ll> gst;
    set<ll> lp, rp;
    ll max_s = 0;
    for (int i = 0; i < n; i++) {
        cin >> v[i].m >> v[i].s;
        vll a(v[i].m); vin(a);

        unordered_set<ll> st;
        for (int j = 1; j < sz(a); j++)
            st.insert(a[j]-a[j-1]);

        if (sz(st) > 1) {
            cout << "No\n";
            return 0;
        } else if (sz(st) == 1)
            gst.insert(*st.begin());

        v[i].l = a[0];
        v[i].r = v[i].s-a.back();
        lp.insert(v[i].l);
        rp.insert(v[i].r);

        max_s = max(max_s, v[i].s);
    }

    if (n == 1) {
        cout << "Yes\n1";
        return 0;
    }
    if (sz(gst) == 1) {
        if (build(*gst.begin())) {
            cout << "Yes\n";
            vout(ans);
        } else
            cout << "No\n";
        return 0;
    }


    if (max_s <= 100) {
        for (ll d = 0; d <= max_s; d++) {
            if (build(d)) {
                cout << "Yes\n";
                vout(ans);
                return 0;
            }
        }
        cout << "No\n";
        return 0;
    }

    if (n <= 1000) {
        for (int j = 1; j < n; j++) {
            if (build(v[0].l+v[j].r)) {
                cout << "Yes\n";
                vout(ans);
                return 0;
            }
            if (build(v[0].r+v[j].l)) {
                cout << "Yes\n";
                vout(ans);
                return 0;
            }
        }
        cout << "No\n";
        return 0;
    }


    vll l(all(lp)), r(all(rp));
    reverse(all(r));

    for (int i = 0; i < min(2, sz(r)); i++) {
        for (int j = 0; j < min(2, sz(l)); j++) {
            if (build(r[i]+l[j])) {
                cout << "Yes\n";
                vout(ans);
                return 0;
            }
        }
    }

    cout << "No\n";

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