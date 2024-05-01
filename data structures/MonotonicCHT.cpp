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
