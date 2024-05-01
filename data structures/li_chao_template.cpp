template<typename T = ll>
struct LiChaoTree {
    LiChaoTree(vector<T> _query_points, T neutral, bool _max=0)
        : query_points(_query_points), size(sz(query_points)), max(_max)
    {
        tree.resize(4*size, {0, neutral});
    }

    void add_line(T k, T b) {
        if (max) {
            add_line({-k, -b}, 0, 0, size);
        } else {
            add_line({k, b}, 0, 0, size);
        }
    }

    T get_ans(int i) {
        if (max) {
            return -get_ans(i, 0, 0, size);
        } else {
            return get_ans(i, 0, 0, size);
        }
    }

private:
    struct Line {
        T k;
        T b;
        T get(T x) const {
            return k*x + b;
        }
    };

    void add_line(Line cur, int x, int lx, int rx) {
        int m = (lx+rx)/2;
        bool left = cur.get(query_points[lx]) < tree[x].get(query_points[lx]);
        bool mid = cur.get(query_points[m]) < tree[x].get(query_points[m]);
        if (mid) {
            swap(tree[x], cur);
        }

        if (rx-lx == 1) {
            return;
        }
        if (left == mid) {
            add_line(cur, 2*x+2, m, rx);
        } else {
            add_line(cur, 2*x+1, lx, m);
        }
    }
    
    T get_ans(int i, int x, int lx, int rx) {
        if (rx-lx == 1) {
            return tree[x].get(query_points[i]);
        }
    
        int m = (lx+rx)/2;
        if (i < m) {
            return min(tree[x].get(query_points[i]), get_ans(i, 2*x+1, lx, m));
        } else {
            return min(tree[x].get(query_points[i]), get_ans(i, 2*x+2, m, rx));
        }
    }

    vector<Line> tree;
    vector<T> query_points;
    int size;
    bool max; // на максимум
};
