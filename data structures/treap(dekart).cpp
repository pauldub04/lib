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


struct Node {
    Node *l, *r;
    ll x, y;
    ll sz = 1;
    Node(ll _x, ll _y): l(nullptr), r(nullptr), x(_x), y(_y) {}
};

ll get_sz(Node *t) {
    if (!t)
        return 0;
    else
        return t->sz;
}

void recalc(Node *t) {
    if (!t)
        return;
    t->sz = get_sz(t->l) + 1 + get_sz(t->r);
}

typedef std::pair<Node *, Node *> P;

P split(Node *t, ll x) {
    if (t == nullptr)
        return {nullptr, nullptr};
    if (x > t->x) {
        P p = split(t->r, x);
        t->r = p.F;
        recalc(t);
        return {t, p.S};
    } else {
        P p = split(t->l, x);
        t->l = p.S;
        recalc(t);
        return {p.F, t};
    }
}

Node *merge(Node *l, Node *r) {
    if (l == nullptr)
        return r;
    if (r == nullptr)
        return l;
    if (l->y > r->y) {
        l->r = merge(l->r, r);
        recalc(l);
        return l;
    } else {
        r->l = merge(l, r->l);
        recalc(r);
        return r;
    }
}

void insert(Node *&t, Node *k) {
    P p = split(t, k->x);
    t = merge(merge(p.F, k), p.S);
}

void remove(Node *&t, ll x) {
    if (t == nullptr)
        return;
    if (t->x == x) {
        t = merge(t->l, t->r);
        return;
    }
    if (x >= t->x)
        remove(t->r, x);
    else
        remove(t->l, x);
}

Node *find_rec(Node *t, ll x) {
    if (t == nullptr || t->x == x)
        return t;
    if (x >= t->x)
        return find_rec(t->r, x);
    else
        return find_rec(t->l, x);
}

Node *find(Node *t, ll x) {
    while (t) {
        if (t->x == x)
            return t;
        if (x >= t->x)
            t = t->r;
        else
            t = t->l;
    }
    return nullptr;
}

Node *next(Node *t, ll x) {
    P p = split(t, x);

    Node *r = p.S;
    if (r == nullptr || r->x == x) {
        merge(p.F, p.S);
        return nullptr;
    }

    while (r->l && r->l->x != x)
        r = r->l;

    merge(p.F, p.S);
    return r;
}

Node *prev(Node *t, ll x) {
    P p = split(t, x);

    Node *l = p.F;
    if (l == nullptr) {
        merge(p.F, p.S);
        return nullptr;
    }

    while (l->r)
        l = l->r;

    merge(p.F, p.S);
    return l;
}

Node *kth(Node *t, ll k) {
    if (!t)
        return nullptr;
    if (get_sz(t->l) == k)
        return t;
    if (get_sz(t->l) > k)
        return kth(t->l, k);
    else
        return kth(t->r, k-get_sz(t->l)-1);
}


Node* t = nullptr;

int solve(ll tc) {

    string cmd;
    while (cin >> cmd) {
        ll x; cin >> x;
        if (cmd == "insert") {
            if (!find_rec(t, x)) {
                Node *k = new Node(x, rand(-1e5, 1e5));
                insert(t, k);
            }
        } else
        if (cmd == "exists") {
            cout << (find_rec(t, x) ? "true" : "false") << "\n";
        } else
        if (cmd == "delete") {
            remove(t, x);
        } else
        if (cmd == "next") {
            Node *n = next(t, x);
            if (!n)
                cout << "none\n";
            else
                cout << n->x << "\n";
        } else
        if (cmd == "prev") {
            Node *n = prev(t, x);
            if (!n)
                cout << "none\n";
            else
                cout << n->x << "\n";
        } else
        if (cmd == "kth") {
            Node *n = kth(t, x-1);
            if (!n)
                cout << "none\n";
            else
                cout << n->x << "\n";
        }
    }

    delete t;
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
