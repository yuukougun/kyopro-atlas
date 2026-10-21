// DFS の帰りがけ順の逆でトポロジカル順を作る。N 頂点 M 辺の有向グラフ（入力は 1-indexed）。
// 閉路があれば -1 を出力する（探索中の頂点へ向かう辺を見つけたら閉路）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    assert(n >= 1 && m >= 0);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        assert(0 <= a && a < n && 0 <= b && b < n);
        g[a].push_back(b);
    }

    // --8<-- [start:core]
    // state[v]：0 = 未訪問、1 = 探索中（まだ出ていない）、2 = 出た
    vector<int> state(n, 0), post;
    bool has_cycle = false;
    auto dfs = [&](auto&& self, int v) -> void {
        state[v] = 1;
        for (int w : g[v]) {
            if (state[w] == 1) has_cycle = true;  // 祖先へ戻る辺＝閉路
            else if (state[w] == 0) self(self, w);
        }
        state[v] = 2;
        post.push_back(v);  // v から行ける頂点はすべて post に入った後
    };
    for (int v = 0; v < n; v++) if (state[v] == 0) dfs(dfs, v);
    if (has_cycle) {
        cout << -1 << '\n';
        return 0;
    }
    vector<int> order(post.rbegin(), post.rend());  // 帰りがけ順の逆
    // --8<-- [end:core]

    // 検証：すべての辺が前から後ろへ向いている
    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[order[i]] = i;
    for (int u = 0; u < n; u++) for (int v : g[u]) assert(pos[u] < pos[v]);
    for (int i = 0; i < n; i++) cout << order[i] + 1 << (i + 1 < n ? ' ' : '\n');
}
