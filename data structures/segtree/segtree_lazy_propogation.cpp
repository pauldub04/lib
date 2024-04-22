vector<int> add, tree;

const int base_tree = 0;
const int neutral_tree = -inf;

const int base_add = 0;
const int neutral_add = 0;

inline int func(int x, int y) {
    return max(x, y);
}

void build(int x=0, int lx=0, int rx=N) {
    if (rx-lx == 1) {
        tree[lx] = base_tree;
        add[lx] = base_add;
        return;
    }
    int m = (lx+rx)/2;
    build(2*x+1, lx, m);
    build(2*x+2, m, rx);
    tree[x] = func(tree[2*x+1], tree[2*x+2]);
}

void push(int x) {
    if (add[x] == neutral_add) {
        return;
    }
    tree[x] += add[x];
    for (int i : {1, 2}) {
        add[2*x+i] += add[x];
    }
    add[x] = base_add;
}

int ans(int l, int r, int x=0, int lx=0, int rx=N) {
    push(x);
    if (l <= lx && rx <= r) {
        return tree[x];
    }
    if (lx >= r || l >= rx) {
        return neutral_tree;
    }
    int m = (lx+rx)/2;
    return func(ans(l, r, 2*x+1, lx, m), ans(l, r, 2*x+2, m, rx));
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
