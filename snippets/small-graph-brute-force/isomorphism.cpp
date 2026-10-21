// 頂点数 N ≤ 8 の 2 つの単純無向グラフ G・H が同型か（頂点の番号を付け替えて一致するか）を、頂点の対応の全探索で判定する
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// g・h は隣接行列（g[i][j] が true なら辺 i–j がある）
bool isomorphic(int n, const vector<vector<bool>>& g, const vector<vector<bool>>& h) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);                  // 0, 1, …, n-1 の昇順から始める
    do {
        // G の頂点 i を H の頂点 p[i] に対応させる
        bool ok = true;
        for (int i = 0; i < n && ok; i++) {
            for (int j = i + 1; j < n; j++) {
                if (g[i][j] != h[p[i]][p[j]]) { ok = false; break; }  // 辺の有無が食い違う
            }
        }
        if (ok) return true;
    } while (next_permutation(p.begin(), p.end()));
    return false;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    assert(1 <= n && n <= 8);
    auto read_graph = [&]() {
        int m;
        cin >> m;
        vector<vector<bool>> adj(n, vector<bool>(n, false));
        for (int e = 0; e < m; e++) {
            int u, v;
            cin >> u >> v;
            u--, v--;                              // 入力は 1-indexed
            adj[u][v] = adj[v][u] = true;
        }
        return adj;
    };
    auto g = read_graph();
    auto h = read_graph();
    cout << (isomorphic(n, g, h) ? "Yes" : "No") << '\n';
}
