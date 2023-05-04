struct Dsu {
    explicit Dsu(ll n) {
        p.assign(n, 0);
        s.assign(n, 0);
        iota(all(p), 0ll);
    }

    ll get_root(ll x) {
        if (x == p[x])
            return x;
        return p[x] = get_root(p[x]);
    }

    bool is_connected(ll a, ll b) {
        return get_root(a) == get_root(b);
    }

    void connect(ll a, ll b) {
        a = get_root(a);
        b = get_root(b);

        if (s[a] > s[b])
            swap(a, b);
        p[a] = b;
        s[b] += s[a];
    }

    vll p, s;
};
