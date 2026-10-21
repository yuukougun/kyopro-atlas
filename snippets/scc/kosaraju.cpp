#include <bits/stdc++.h>
using namespace std;

// Kosaraju 法：成分の数と、各頂点の成分の番号（トポロジカル順）を出力する
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n), rg(n);  // rg は辺の向きを逆にしたグラフ
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    // --8<-- [start:core]
    // 1 回目：元のグラフで DFS し、帰りがけ順に頂点を並べる
    vector<bool> used(n, false);
    vector<int> order;
    auto dfs1 = [&](auto&& self, int v) -> void {
        used[v] = true;
        for (int to : g[v]) {
            if (!used[to]) self(self, to);
        }
        order.push_back(v);
    };
    for (int v = 0; v < n; v++) {
        if (!used[v]) dfs1(dfs1, v);
    }
    // 2 回目：帰りがけ順の逆に、逆辺のグラフで DFS する。1 回の DFS で届く頂点がちょうど 1 つの成分
    vector<int> comp(n, -1);
    auto dfs2 = [&](auto&& self, int v, int c) -> void {
        comp[v] = c;
        for (int to : rg[v]) {
            if (comp[to] == -1) self(self, to, c);
        }
    };
    int k = 0;
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        if (comp[v] == -1) dfs2(dfs2, v, k++);
    }
    // --8<-- [end:core]
    cout << k << '\n';
    for (int v = 0; v < n; v++) cout << comp[v] << (v + 1 < n ? ' ' : '\n');
}
