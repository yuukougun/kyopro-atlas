// 一度訪れた頂点は二度と訪れない DFS：無向グラフの連結成分の個数と、頂点 0 を含む成分の大きさを求める。
// 入力は N M と辺 (u, v)（1-indexed）。全体で O(N + M)。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;  // 0-indexed に直す
        g[u].push_back(v);
        g[v].push_back(u);
    }

    // --8<-- [start:core]
    vector<bool> seen(n, false);
    int cnt = 0;  // いま探索している成分の頂点数
    auto dfs = [&](auto&& self, int v) -> void {
        seen[v] = true;  // 入った時点で印を付け、二度と外さない
        cnt++;
        for (int to : g[v]) {
            if (!seen[to]) self(self, to);
        }
    };

    int components = 0, size0 = 0;
    for (int s = 0; s < n; s++) {
        if (seen[s]) continue;
        cnt = 0;
        dfs(dfs, s);  // s から届く頂点すべてに印が付く
        components++;
        if (s == 0) size0 = cnt;
    }
    // --8<-- [end:core]
    cout << components << ' ' << size0 << '\n';
}
