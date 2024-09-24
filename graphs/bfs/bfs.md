**BFS**

[Алгоритмика](https://ru.algorithmica.org/cs/shortest-paths/bfs/)\
[Википедия](https://ru.wikipedia.org/wiki/%D0%9F%D0%BE%D0%B8%D1%81%D0%BA_%D0%B2_%D1%88%D0%B8%D1%80%D0%B8%D0%BD%D1%83)

Хотим в невзвешенном графе находить кратчайшие пути от заданной вершины до всех. Граф может быть как ориентированным, так и неориентированным.

Основную идею алгоритма можно понимать как процесс «поджигания» графа: на нулевом шаге мы поджигаем вершину ss, а на каждом следующем шаге огонь с каждой уже горящей вершины перекидывается на всех её соседей, в конечном счете поджигая весь граф.

***Обычный bfs*** - одна очередь\
Асимптотика: `O(n + m)`

```cpp
void bfs(ll s) {
    queue<ll> q; q.push(s);
    vll d(n, -1); d[s] = 0;
    vll p(n, -1);

    while (!q.empty()) {
        ll v = q.front(); q.pop();

        for (auto to : g[v]) {
            if (d[to] == -1) {
                d[to] = d[v] + 1;
                p[to] = v;
                q.push(to);
            }
        }
    }
}
```

***0-1 bfs*** - дек\
Асимптотика: `O(n + m)`

```cpp
void bfs(ll s) {
    deque<ll> q; q.push(s);
    vll d(n, -1); d[s] = 0;
    vll p(n, -1);

    while (!q.empty()) {
        ll v = q.front(); q.pop();

        for (auto [to, len] : g[v]) {
            if (d[to] == -1) {
                d[to] = d[v] + len;
                p[to] = v;
                if (len == 0) {
                    q.push_front(to);
                } else {
                    q.push_back(to);
                }
            }
        }
    }
}
```

***0-k bfs*** - Ребра от 0 до k, будем хранить k+1 очередь и указатель на текущую. Смещение будем делать циклически\
Асимптотика: `O(n*k + m)`

```cpp
struct Edge {
    ll to;
    ll len;
};

struct Bfs0k {
    ll n;
    ll k;
    const vector<vector<Edge>>& g;

    Bfs0k(ll _n, ll _k, const vector<vector<Edge>>& _g) 
    : n(_n), k(_k), g(_g) {}

    pair<vll, vll> calcDistAncestor(ll s) {
        vector<bool> used(n, 0);
        vll dist(n, INF); dist[s] = 0;
        vll p(n, -1);

        vector<queue<ll>> q(k+1);
        ll cur = 0; // current level

        q[cur].push(s);
        ll total = 1;

        while (total > 0) {
            if (sz(q[cur]) == 0) {
                ++cur;
                cur %= sz(q);
                continue;
            }

            ll v = q[cur].front(); q[cur].pop();
            --total;
            if (used[v]) {
                continue;
            }
            used[v] = 1;

            for (auto [to, len] : g[v]) {
                if (used[to]) {
                    continue;
                }
                if (dist[v]+len < dist[to]) {
                    dist[to] = dist[v]+len;
                    p[to] = v;
                    q[(cur+len) % sz(q)].push(to);
                    ++total;
                }
            }
        }
        return {dist, p};
    }

    vll calcDist(ll s) {
        return calcDistAncestor(s).first;
    }
};
```
[Задача G-Доставка кефирчика](http://ejudge.algocode.ru/cgi-bin/new-client?contest_id=34009)\
[Решение](tink_bfs_g.cpp)
