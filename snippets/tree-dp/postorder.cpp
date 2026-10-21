// 再帰を使わない木 DP：BFS 順を作り、逆順にたどって子から親へ集める（部分木のサイズの例）
// 入力：N、続く N - 1 行に辺 u v（1-indexed）。出力：頂点 1 を根にした各頂点の部分木のサイズ
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // --8<-- [start:core]
    // 根 0 から BFS して、親 par と訪れた順 order を作る（親は必ず子より前に並ぶ）
    vector<int> par(n, -1), order;
    order.reserve(n);
    order.push_back(0);
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int c : g[v]) {
            if (c == par[v]) continue;  // 親へ戻らない
            par[c] = v;
            order.push_back(c);
        }
    }
    // 逆順にたどると、子はすべて親より先に確定している（帰りがけ順の代わり）
    vector<int> sz(n, 1);
    for (int i = n - 1; i >= 1; i--) {
        int v = order[i];
        sz[par[v]] += sz[v];
    }
    // --8<-- [end:core]
    assert(sz[0] == n);
    for (int i = 0; i < n; i++) cout << sz[i] << '\n';
}
