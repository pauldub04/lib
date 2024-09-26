**Центроидная декомпозиция**

[Алгоритмика](https://algorithmica.org/ru/centroid)

***Центроид дерева*** - вершина, при удалении которой размеры оставшихся компонент будут не более `n/2`.\
***Центроидная декомпозиция*** - рекурсивный процесс «выделить центроид, удалить, запуститься от компонент».
***Компонента центроида*** - множество вершин, достижимых из центроида непосредственно перед его удалением.

- Каждая вершина входит в `O(log n)` компонент.
- Для любого пути `a --> b` есть единственный центроид `c`, в чьей компоненте были и `a`, и `b`.

Задачи:
- ***Подсчет путей с заданным свойством***. Вмешаемся в процесс центроиднодной декомпозиции: для каждого центроида перед его удалением будем прибавлять к ответу число интересующих нас путей, которые проходят через этот центроид.
- ***Запросы на путях — offline***. Мы находим всё, что нам надо, сразу после того, как получили новую компоненту. Если у нас есть список запросов «посчитать что-то на пути», то мы часто можем обработать их в offline.

Асимптотика: `O(n*logn)`
```cpp
ll n;
vll2 g;
vector<bool> deleted;
vll subtree_size;

void calc_subtree_size(ll v, ll p=-1) {
    subtree_size[v] = 1;
    for (auto to : g[v]) {
        if (to == p || deleted[to]) {
            continue;
        }
        calc_subtree_size(to, v);
        subtree_size[v] += subtree_size[to];
    }
}

ll centroid(ll v, ll tree_size, ll p=-1) {
    for (auto to : g[v]) {
        if (to == p || deleted[to]) {
            continue;
        }
        if (subtree_size[to]*2 > tree_size) {
            return centroid(to, tree_size, v);
        }
    }
    return v;
}

void dfs(ll v, ll dist, vll& distances, ll p) {
    if (dist < sz(distances)) {
        ++distances[dist];
    }
    for (auto to : g[v]) {
        if (to == p || deleted[to]) {
            continue;
        }
        dfs(to, dist+1, distances, v);
    }
}

ll ans = 0;
void calc_ans(ll root) {
    calc_subtree_size(root);
    ll v = centroid(root, subtree_size[root]);

    for (auto to : g[v]) {
        if (deleted[to]) {
            continue;
        }

        // calc smth
    }

    deleted[v] = 1;
    for (auto to : g[v]) {
        if (deleted[to]) {
            continue;
        }
        calc_ans(to);
    }
}

```

Задача. Расстояние в дереве\
[итмо](https://codeforces.com/group/6QVazHPgRF/contest/351702/problem/A)
[мифи](https://codeforces.com/group/lTkkazGqHJ/contest/513285/problem/A)\
Дано дерево из n вершин и положительное число k. Посчитайте количество различных пар вершин дерева, расстояние между которыми равно k.\
[Решение](cnt_k_paths.cpp)
