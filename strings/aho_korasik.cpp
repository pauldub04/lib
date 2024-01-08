#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> vll;
typedef vector< vll > vll2;
typedef pair<ll, ll> pll;
typedef string str;

//mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
//#define rand(l, r) uniform_int_distribution<ll>(l, r)(rng)

#define IOS ios::sync_with_stdio(false); cin.tie(nullptr)
#define vin(a) {for (auto& _ : (a)) {cin >> _;}}
#define vout(a) {for (auto _ : (a)) {cout << _ << " ";} cout << "\n";}
#define all(x) (x).begin(), (x).end()
#define sz(a) ((int) ((a).size()))

#define F first
#define S second
#define pb push_back

const int inf = 1e9, mod = 1e9+7, N = 1e5, LG = 30;
const ll INF = 1e18;
const ld eps = 1e-9;

const int ALPHABET = 26;
const int NEUTRAL = -1;

struct Trie {
    struct Node {
        vector<int> to;     // обычный переход
        vector<int> go;     // переход автомата
        int link;           // обычная суфф ссылка
        int linkTerminal;   // сжатая суфф ссылка в первый терминальный суффикс

        int depth;                  // глубина вершины, не нужна для алгоса
        int terminal;               // сколько здесь заканчивается строк
        int terminalPrefixCount;    // сколько заканчивается строк во всех префиксах
        int terminalSuffixCount;    // сколько заканчивается строк во всех суффиксах

        Node() {
            to.assign(ALPHABET, NEUTRAL);
            go.assign(ALPHABET, NEUTRAL);
            terminal = terminalPrefixCount = terminalSuffixCount = 0;
            depth = 0;
            link = linkTerminal = NEUTRAL;
        }

        inline int& getTo(char c) {
            return to[c-'a'];
        }

        inline int& getGo(char c) {
            return go[c-'a'];
        }
    };

    Trie() {
        trie.reserve(N);
        trie.resize(1);
        root = 0;
    }

    int createNode() {
        trie.emplace_back();
        return sz(trie)-1;
    }

    void addString(const string& s) {
        int v = root;
        for (auto c : s) {
            if (trie[v].getTo(c) == NEUTRAL) {
                trie[v].getTo(c) = createNode();
            }
            ++trie[v].terminalPrefixCount;
            v = trie[v].getTo(c);
        }
        ++trie[v].terminal;
        ++trie[v].terminalPrefixCount;
    }

    void buildAhoKorasik() {
        trie[root].link = root;            // это не совсем правда
        trie[root].linkTerminal = root;    // это не совсем правда
        trie[root].depth = 0;
        for (int c = 0; c < ALPHABET; ++c) {
            if (trie[root].to[c] == NEUTRAL) {
                trie[root].go[c] = root;
            } else {
                trie[root].go[c] = trie[root].to[c];
            }
        }

        queue<int> q; q.push(root);
        while (!q.empty()) {
            int v = q.front(); q.pop();

            for (int c = 0; c < ALPHABET; ++c) {
                int u = trie[v].to[c];
                if (u == NEUTRAL) {
                    continue;
                }
                trie[u].depth = trie[v].depth + 1;

                if (v == root) {
                    trie[u].link = root;
                } else {
                    trie[u].link = trie[trie[v].link].go[c];
                }

                if (trie[trie[u].link].terminal) {
                    trie[u].linkTerminal = trie[u].link;
                } else {
                    trie[u].linkTerminal = trie[trie[u].link].linkTerminal;
                }

                trie[u].terminalSuffixCount = trie[u].terminal + trie[trie[u].link].terminalSuffixCount;

                for (int d = 0; d < ALPHABET; ++d) {
                    if (trie[u].to[d] == NEUTRAL) {
                        trie[u].go[d] = trie[trie[u].link].go[d];
                    } else {
                        trie[u].go[d] = trie[u].to[d];
                    }
                }
                q.push(u);
            }
        }
    }

    Node& operator[](size_t idx) {
        return trie[idx];
    }

    vector<Node> trie;
    int root;
};

int solve(ll tc) {
    Trie trie;
    trie.addString("kek");
    trie.addString("lol");
    trie.addString("abc");
    trie.addString("ab");
    trie.buildAhoKorasik();

    string s = "sodiabcjipflolguabhsdkekfgjkekekdgflol";
//                       |||    |||  ||         ^^^^^   |||     kek
//                       |||    ^^^  ||                 ^^^     lol
//                       ^^^         ||                         abc
//                       ^^          ^^                         ab

    int totalCount = 0;
    int curState = trie.root;

    for (int i = 0; i < sz(s); ++i) {
        curState = trie[curState].getGo(s[i]);

        int pos = curState;
        while (pos != trie.root) {
            if (trie[pos].terminal) {
                int startPos = i - trie[pos].depth + 1;
                cout << "startPos = " << startPos << ";";
                cout << "\tfound: " << s.substr(startPos, trie[pos].depth) << "\n";
            }
            pos = trie[pos].linkTerminal;
        }

        totalCount += trie[curState].terminalSuffixCount;
    }

    cout << "totalCount: " << totalCount << "\n";


    return 0;
}

int main() {
    IOS;
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);

    ll tc = 1;
//    cin >> tc;
    while (tc--) {
        solve(tc);
    }

    return 0;
}
