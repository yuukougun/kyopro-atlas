// 無向グラフの閉路を DFS で 1 つ見つけ、親をたどって復元する。
// 親へ戻る辺は「頂点」ではなく「辺の番号」で除くので、多重辺（長さ 2 の閉路）も見つかる。
// 入力：n m と m 本の無向辺 u v（0-indexed。自己ループ・多重辺を含んでよい）。
// 出力：閉路があればその長さと頂点を閉路に沿った順に、なければ -1。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);  // (行き先, 辺の番号)
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        assert(0 <= u && u < n && 0 <= v && v < n);
        g[u].push_back({v, i});
        if (u != v) g[v].push_back({u, i});
    }

    // --8<-- [start:core]
    // state：0 = 未訪問、1 = 探索中、2 = 完了。pe[v] は v に入ってきた木の辺の番号
    vector<int> state(n, 0), par(n, -1), pe(n, -1);
    vector<int> cycle;
    auto dfs = [&](auto&& self, int v) -> bool {
        state[v] = 1;
        for (auto [u, id] : g[v]) {
            if (id == pe[v]) continue;  // 来た辺そのものだけを除く（親への別の辺は除かない）
            if (state[u] == 0) {
                par[u] = v;
                pe[u] = id;
                if (self(self, u)) return true;
            } else if (state[u] == 1) {
                // 祖先 u への木以外の辺：木の経路 u → … → v とこの辺で閉路になる
                for (int x = v; x != u; x = par[x]) cycle.push_back(x);
                cycle.push_back(u);
                reverse(cycle.begin(), cycle.end());
                return true;
            }
        }
        state[v] = 2;
        return false;
    };
    for (int s = 0; s < n; s++) {
        if (state[s] == 0 && dfs(dfs, s)) break;
    }
    // --8<-- [end:core]

    if (cycle.empty()) {
        cout << -1 << '\n';
        return 0;
    }
    int k = cycle.size();
    for (int i = 0; i < k; i++) {
        int a = cycle[i], b = cycle[(i + 1) % k];
        bool found = false;
        for (auto [u, id] : g[a]) found |= (u == b);
        assert(found);
    }
    cout << k << '\n';
    for (int i = 0; i < k; i++) cout << cycle[i] << (i + 1 < k ? ' ' : '\n');
}
