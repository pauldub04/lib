// максимум с позицией
struct Segment {
    int max_val;
    int max_pos;
};

vector<Segment> tree;
const int base_tree = 0;
const int neutral_tree = -inf;

vector<int> add;
const int base_add = 0;

inline Segment func(const Segment& x, const Segment& y) {
    if (x.max_val > y.max_val) {
        return x;
    } else {
        return y;
    }
}

void build(int x=0, int lx=0, int rx=N) {
    if (rx-lx == 1) {
        tree[x] = {base_tree, lx};
        add[x] = base_add;
        return;
    }
    int m = (lx+rx)/2;
    build(2*x+1, lx, m);
    build(2*x+2, m, rx);
    tree[x] = func(tree[2*x+1], tree[2*x+2]);
}

void push(int x) {
    if (add[x] == base_add) {
        return;
    }
    tree[x].max_val += add[x];
    for (int i : {1, 2}) {
        if (2*x+i < sz(add)) {
            add[2*x+i] += add[x];
        }
    }
    add[x] = base_add;
}

Segment get(int l, int r, int x=0, int lx=0, int rx=N) {
    push(x);
    if (l <= lx && rx <= r) {
        return tree[x];
    }
    if (lx >= r || l >= rx) {
        return {neutral_tree, -1};
    }
    int m = (lx+rx)/2;
    return func(get(l, r, 2*x+1, lx, m), get(l, r, 2*x+2, m, rx));
}

void upd(int l, int r, int val, int x=0, int lx=0, int rx=N) {
    push(x);
    if (lx >= r || l >= rx) {
        return;
    }
    if (l <= lx && rx <= r) {
        add[x] += val;
        push(x);
        return;
    }
    int m = (lx+rx)/2;
    upd(l, r, val, 2*x+1, lx, m);
    upd(l, r, val, 2*x+2, m, rx);
    tree[x] = func(tree[2*x+1], tree[2*x+2]);
}
