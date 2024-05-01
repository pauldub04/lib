struct Line {
    ll k;
    ll b;
    ll get(ll x) const {
        return k*x + b;
    }
};

struct Node {
    Line line;
    Node *l = nullptr;
    Node *r = nullptr;
 
    Node(Line line_) : line(line_) {}
};

vll query_points;
void add_line(Node *node, Line cur, int lx=0, int rx=sz(query_points)) {
    int m = (lx+rx)/2;
    bool left = cur.get(query_points[lx]) < node->line.get(query_points[lx]);
    bool mid = cur.get(query_points[m]) < node->line.get(query_points[m]);
    if (mid) {
        swap(node->line, cur);
    }

    if (lx == rx) {
        return;
    }

    if (left == mid) {
        if (!node->r) {
            node->r = new Node(cur);
        } else {
            add_line(node->r, cur, m, rx);
        }
    } else {
        if (!node->l) {
            node->l = new Node(cur);
        } else {
            add_line(node->l, cur, lx, m);
        }
    }
}
 
ll get_ans(Node *node, int i, int lx=0, int rx=sz(query_points)) {
    if (!node) {
        return INF;
    }
    if (rx-lx == 1) {
        return node->line.get(query_points[i]);
    }

    int m = (lx+rx)/2;
    if (i < m) {
        return min(node->line.get(query_points[i]), get_ans(node->l, i, lx, m));
    } else {
        return min(node->line.get(query_points[i]), get_ans(node->r, i, m, rx));
    }
}
