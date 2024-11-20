#include <vector>
#include <numeric>

namespace dsu {
    using ll = long long;
    struct Dsu {
        explicit Dsu(int n) {
            root.resize(n, 0);
            subtree.resize(n, 1);
            std::iota(root.begin(), root.end(), 0);
        }
        int getRoot(int x) {
            if (x == root[x]) { return x; }
            return root[x] = getRoot(root[x]);
        }
        bool isConnected(int a, int b) {
            return getRoot(a) == getRoot(b);
        }
        void connect(int a, int b) {
            a = getRoot(a); b = getRoot(b);
            if (a == b) { return; }
            if (subtree[a] > subtree[b]) {
                std::swap(a, b);
            }
            root[a] = b;
            subtree[b] += subtree[a];
        }
        std::vector<int> root;
        std::vector<ll> subtree;
    };
}