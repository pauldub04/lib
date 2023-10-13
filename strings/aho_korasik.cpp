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

const int alphabetSize = 26;
const int neutral = -1;

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
            to.assign(alphabetSize, neutral);
            go.assign(alphabetSize, neutral);
            terminal = terminalPrefixCount = terminalSuffixCount = 0;
            depth = 0;
            link = linkTerminal = neutral;
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
            if (trie[v].getTo(c) == neutral) {
                trie[v].getTo(c) = createNode();
            }
            ++trie[v].terminalPrefixCount;
            v = trie[v].getTo(c);
        }
        ++trie[v].terminal;
        ++trie[v].terminalPrefixCount;
    }

    void buildAhoKorasik() {
        trie[root].link = 0;            // это не совсем правда
        trie[root].linkTerminal = 0;    // это не совсем правда
        trie[root].depth = 0;
        for (int c = 0; c < alphabetSize; ++c) {
            if (trie[root].to[c] == neutral) {
                trie[root].go[c] = root;
            } else {
                trie[root].go[c] = trie[root].to[c];
            }
        }

        queue<int> q; q.push(0);
        while (!q.empty()) {
            int v = q.front(); q.pop();

            for (int c = 0; c < alphabetSize; ++c) {
                int u = trie[v].to[c];
                if (u == neutral) {
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

                for (int d = 0; d < alphabetSize; ++d) {
                    if (trie[u].to[d] == neutral) {
                        trie[u].go[d] = trie[trie[u].link].go[d];
                    } else {
                        trie[u].go[d] = trie[u].to[d];
                    }
                }
                q.push(u);
            }
        }
    }

    vector<Node> trie;
    int root;
};

int solve(ll tc) {
    Trie t;
    t.addString("kek");
    t.addString("lol");
    t.addString("abc");
    t.buildAhoKorasik();

    string s = "sodiabcjipflolguabhsdkekfgjkekekdgf";
    int totalCount = 0;

    int cur = t.root;
    for (int i = 0; i < sz(s); ++i) {
        cur = t.trie[cur].getGo(s[i]);

        int pos = cur;
        while (pos != t.root) {
            if (t.trie[pos].terminal) {
                int startPos = i - t.trie[pos].depth + 1;
                cout << "startPos = " << startPos << "; found: " << s.substr(startPos, t.trie[pos].depth) << "\n";
            }
            pos = t.trie[pos].linkTerminal;
        }

        totalCount += t.trie[cur].terminalSuffixCount;
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
