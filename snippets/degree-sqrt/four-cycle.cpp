#include <bits/stdc++.h>
using namespace std;

// 単純無向グラフの長さ 4 の閉路を 1 つ見つける（なければ空の配列）。
// 鳩の巣原理：頂点の組は n(n-1)/2 種類なので、組を記録していけば
// その回数 + 1 回以内に同じ組が 2 回出る。表は n×n なので n は数千まで。
// --8<-- [start:detect]
vector<int> find_c4(int n, const vector<vector<int>>& g) {
    vector<int> seen((size_t)n * n, -1);      // seen[a*n+b]：a, b の両方に隣接する頂点
    for (int v = 0; v < n; v++) {
        for (int i = 0; i < (int)g[v].size(); i++) {
            for (int j = i + 1; j < (int)g[v].size(); j++) {
                int a = min(g[v][i], g[v][j]), b = max(g[v][i], g[v][j]);
                int& s = seen[(size_t)a * n + b];
                if (s != -1) return {s, a, v, b};   // s - a - v - b - s
                s = v;
            }
        }
    }
    return {};
}
// --8<-- [end:detect]

// 長さ 4 の閉路の個数を O(M√M) で数える。
// --8<-- [start:count]
long long count_c4(int n, const vector<vector<int>>& g) {
    // (次数, 番号) の辞書順で順位を比べる
    auto less_rank = [&](int a, int b) {
        return g[a].size() != g[b].size() ? g[a].size() < g[b].size() : a < b;
    };
    vector<long long> cnt(n, 0);
    long long res = 0;
    for (int v = 0; v < n; v++) {     // v は閉路の中で順位が最大の頂点
        vector<int> touched;
        for (int u : g[v]) {
            if (!less_rank(u, v)) continue;
            for (int w : g[u]) {
                if (!less_rank(w, v)) continue;   // w ≠ v もここで除かれる
                res += cnt[w];                    // v - u - w の道と、先に見た v - u' - w の道で閉路
                if (cnt[w]++ == 0) touched.push_back(w);
            }
        }
        for (int w : touched) cnt[w] = 0;
    }
    return res;
}
// --8<-- [end:count]

bool is_c4(int n, const vector<vector<int>>& g, const vector<int>& c) {
    if (c.size() != 4) return false;
    set<int> s(c.begin(), c.end());
    if ((int)s.size() != 4) return false;
    for (int i = 0; i < 4; i++) {
        int a = c[i], b = c[(i + 1) % 4];
        if (a < 0 || a >= n) return false;
        if (find(g[a].begin(), g[a].end(), b) == g[a].end()) return false;
    }
    return true;
}

long long naive_count(int n, const vector<vector<int>>& g) {
    vector<vector<char>> adj(n, vector<char>(n, 0));
    for (int v = 0; v < n; v++) for (int u : g[v]) adj[v][u] = 1;
    long long c = 0;
    // 4 頂点の閉路は、4 頂点を選んで並べる 4!/8 = 3 通りのどれか
    for (int a = 0; a < n; a++) for (int b = a + 1; b < n; b++)
        for (int x = b + 1; x < n; x++) for (int y = x + 1; y < n; y++) {
            if (adj[a][b] && adj[b][x] && adj[x][y] && adj[y][a]) c++;
            if (adj[a][b] && adj[b][y] && adj[y][x] && adj[x][a]) c++;
            if (adj[a][x] && adj[x][b] && adj[b][y] && adj[y][a]) c++;
        }
    return c;
}

void self_test() {
    mt19937 rng(4);
    for (int iter = 0; iter < 400; iter++) {
        int n = rng() % 9 + 1;
        vector<vector<int>> g(n);
        int p = rng() % 4 + 1;
        for (int a = 0; a < n; a++)
            for (int b = a + 1; b < n; b++)
                if ((int)(rng() % 5) < p) g[a].push_back(b), g[b].push_back(a);
        long long c = naive_count(n, g);
        assert(count_c4(n, g) == c);
        vector<int> f = find_c4(n, g);
        if (c == 0) assert(f.empty());
        else assert(is_c4(n, g, f));
    }
}

int main() {
    self_test();
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> c = find_c4(n, g);
    if (c.empty()) cout << -1 << '\n';
    else cout << c[0] + 1 << ' ' << c[1] + 1 << ' ' << c[2] + 1 << ' ' << c[3] + 1 << '\n';
    cout << count_c4(n, g) << '\n';
}
