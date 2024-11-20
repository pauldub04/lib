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
#define all(x) (x).begin(), (x).end()
#define sz(a) int((a).size())

#define F first
#define S second
#define pb push_back

const int inf = 1e9, mod = 1e9, N = 1e5+10, LG = 17;
const ll INF = 1e18;
const ld eps = 1e-9;

struct Node;
Node f(Node a, Node b);

struct Node {
    Node* l;
    Node* r;
    ll sum{};

    Node(Node* l, Node* r, ll sum)
            : l(l), r(r), sum(sum)
    {}

    Node& operator=(const Node& other) = default;

    Node(Node* a, Node* b) {
        *this = f(*a, *b);
        l = a;
        r = b;
    }
};
Node neutral = Node(nullptr, nullptr, 0);

Node f(Node a, Node b) {
    return {nullptr, nullptr, a.sum+b.sum};
}

Node* build(ll lx=0, ll rx=N) {
    if (rx-lx == 1) {
        return new Node(nullptr, nullptr, 0);
    }
    ll mid = (lx+rx)/2;
    return new Node(build(lx, mid), build(mid, rx));
}

Node* update(Node* node, ll pos, ll val, ll lx=0, ll rx=N) {
    if (rx-lx == 1) {
        return new Node(nullptr, nullptr, val);
    }
    ll mid = (lx+rx)/2;
    if (pos < mid) {
        return new Node(update(node->l, pos, val, lx, mid), node->r);
    } else {
        return new Node(node->l, update(node->r, pos, val, mid, rx));
    }
}

Node query(Node* node, ll l, ll r, ll lx=0, ll rx=N) {
    if (lx >= r || l >= rx) {
        return neutral;
    }
    if (l <= lx && rx <= r) {
        return *node;
    }

    ll mid = (lx+rx)/2;
    return f(query(node->l, l, r, lx, mid), query(node->r, l, r, mid, rx));
}


int solve() {



    return 0;
}

int main() {
    IOS;
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    ll tc = 1;
//    cin >> tc;
    while (tc--) {
        solve();
    }

    return 0;
}