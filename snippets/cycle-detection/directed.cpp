// 有向グラフの閉路を 3 色の DFS で 1 つ見つけ、親をたどって復元する。
// 入力：n m と m 本の有向辺 u v（0-indexed。自己ループ・多重辺を含んでよい）。
// 出力：閉路があればその長さと頂点を辺の向きの順に、なければ -1。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        assert(0 <= u && u < n && 0 <= v && v < n);
        g[u].push_back(v);
    }

    // --8<-- [start:core]
    // color：0 = 未訪問、1 = 探索中（今の再帰の経路の上にある）、2 = 完了
    vector<int> color(n, 0), par(n, -1);
    vector<int> cycle;
    auto dfs = [&](auto&& self, int v) -> bool {
        color[v] = 1;
        for (int u : g[v]) {
            if (color[u] == 0) {
                par[u] = v;
                if (self(self, u)) return true;
            } else if (color[u] == 1) {
                // 探索中の u への辺：経路 u → … → v とこの辺 v → u で閉路になる
                for (int x = v; x != u; x = par[x]) cycle.push_back(x);
                cycle.push_back(u);
                reverse(cycle.begin(), cycle.end());  // u から辺の向きの順に並べる
                return true;
            }
            // color[u] == 2（完了）への辺は閉路を作らないので無視する
        }
        color[v] = 2;
        return false;
    };
    for (int s = 0; s < n; s++) {
        if (color[s] == 0 && dfs(dfs, s)) break;
    }
    // --8<-- [end:core]

    if (cycle.empty()) {
        cout << -1 << '\n';
        return 0;
    }
    // 見つけた列が本当に閉路かを確かめる
    int k = cycle.size();
    for (int i = 0; i < k; i++) {
        int a = cycle[i], b = cycle[(i + 1) % k];
        assert(find(g[a].begin(), g[a].end(), b) != g[a].end());
    }
    cout << k << '\n';
    for (int i = 0; i < k; i++) cout << cycle[i] << (i + 1 < k ? ' ' : '\n');
}
