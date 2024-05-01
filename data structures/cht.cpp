//Slopes are INCREASING -> query for MAXIMUM
//Slopes are DECREASING -> query for MINIMUM
struct Line {
    mutable ll m, b, p;
    bool operator<(const Line &o) const { return m < o.m; }
    bool operator<(const ll x) const { return p < x; }
};
 
struct MonotonicCHT : deque<Line> {
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(Line &x, Line &y) {
        x.p = div(y.b - x.b, x.m - y.m);
        return x.p >= y.p;
    }
    void add(ll m, ll b) {
        Line l = {m, b, INF};
        if(!empty()) isect(at(size() - 1), l);
        while(size() >= 2 && isect(at(size() - 2), at(size() - 1))) {
            pop_back();
            isect(at(size() - 1), l);
        }
        push_back(l);
    }
    ll query(ll x) {
        assert(!empty());
        while(x > front().p) {
            pop_front();
        }
        auto l = front();
        return l.m * x + l.b;
    }
};

//----------------------------------------------------------------

struct Line {
    ll k, b;
    mutable ll p;
 
    bool operator<(const Line &l) const {
        if (k != l.k) return k < l.k;
        return b < l.b;
    }
 
    bool operator<(const ll &x) const { return p < x; }
};
 
struct Convex : multiset<Line, less<>> {
    // for doubles, use inf = 1 / 0.0, div(a, b) = a / b
    const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // floored division
 
    ll calc(iterator y) {
        auto z = next(y);
        if (z == end()) return inf;
        else if (y->k == z->k) return -inf;
        else return div(y->b - z->b, z->k - y->k);
    }
 
    bool bad(iterator y) {
        if (next(y) == end() || y == begin()) return false;
        return calc(prev(y)) >= calc(y);
    }
 
    void add(ll k, ll b) {
        auto y = insert({k, b, 0});
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
        y->p = calc(y);
        if (y != begin()) prev(y)->p = calc(prev(y));
    }
 
    ll query(ll x) {
        auto it = lower_bound(x);
        return it->k * x + it->b;
    }
};
