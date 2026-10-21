// N ≤ 20 の単純無向グラフで、隣り合う頂点が異なる色になる 3 色の塗り方の数を、連結成分ごとの DFS 順の全探索で数える
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
long long count_3_colorings(int n, const vector<vector<int>>& adj) {
    vector<int> color(n, -1);                     // -1 はまだ塗っていない
    vector<bool> seen(n, false);
    long long total = 1;
    for (int s = 0; s < n; s++) {
        if (seen[s]) continue;
        // 1. 成分の頂点を DFS 順に並べる（先頭以外は、自分より前に隣の頂点がある）
        vector<int> order;
        auto dfs = [&](auto&& self, int v) -> void {
            seen[v] = true;
            order.push_back(v);
            for (int to : adj[v]) if (!seen[to]) self(self, to);
        };
        dfs(dfs, s);
        // 2. その順に色を決める。塗り済みの隣と同じ色は選ばない
        auto paint = [&](auto&& self, int idx) -> long long {
            if (idx == (int)order.size()) return 1;
            int v = order[idx];
            long long ways = 0;
            for (int c = 0; c < 3; c++) {
                bool ok = true;
                for (int to : adj[v]) if (color[to] == c) ok = false;
                if (!ok) continue;
                color[v] = c;
                ways += self(self, idx + 1);
                color[v] = -1;                    // 戻す
            }
            return ways;
        };
        total *= paint(paint, 0);                 // 成分どうしは独立なので掛ける
    }
    return total;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    assert(1 <= n && n <= 20);
    vector<vector<int>> adj(n);
    for (int e = 0; e < m; e++) {
        int u, v;
        cin >> u >> v;
        u--, v--;                                 // 入力は 1-indexed
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    cout << count_3_colorings(n, adj) << '\n';
}
