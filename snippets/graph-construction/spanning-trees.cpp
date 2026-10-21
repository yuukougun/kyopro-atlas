// DFS 木と BFS 木：連結な単純無向グラフで、頂点 0 を根にした 3 通りの全域木を作り、木に入らない辺を調べる。
//   1 行目：DFS 木（再帰）で、両端が祖先と子孫の関係にない「木に入らない辺」の本数（必ず 0）
//   2 行目：DFS 木（非再帰。取り出したときに印を付ける）で、同じ本数（必ず 0）
//   3 行目：BFS 木で、両端が祖先と子孫の関係にある「木に入らない辺」の本数（必ず 0）
//   4 行目：スタックに積むときに印を付けた木（DFS 木にならない）で、1 行目と同じ本数
// 入力は N M と辺 (u, v)（1-indexed）。隣接リストは入力の順に並ぶ。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        edges[i] = {u, v};
    }

    // --8<-- [start:dfs-tree]
    vector<int> par_dfs(n, -1);
    vector<bool> seen(n, false);
    auto dfs = [&](auto&& self, int v) -> void {
        seen[v] = true;
        for (int to : g[v]) {
            if (seen[to]) continue;  // 祖先か、もう調べ終えた子孫（後退辺の相手）
            par_dfs[to] = v;         // まだ見ていない頂点は子にする
            self(self, to);
        }
    };
    dfs(dfs, 0);
    // --8<-- [end:dfs-tree]

    // --8<-- [start:dfs-tree-iterative]
    vector<int> par_it(n, -1);
    vector<bool> seen_it(n, false);
    vector<pair<int, int>> st = {{0, -1}};  // （頂点, 積んだときの親）
    while (!st.empty()) {
        auto [v, p] = st.back();
        st.pop_back();
        if (seen_it[v]) continue;  // 取り出したときに印を付ける
        seen_it[v] = true;
        par_it[v] = p;             // 最後に積んだ頂点が親になる
        for (int i = (int)g[v].size() - 1; i >= 0; i--) {
            if (!seen_it[g[v][i]]) st.push_back({g[v][i], v});
        }
    }
    // --8<-- [end:dfs-tree-iterative]

    // --8<-- [start:bfs-tree]
    vector<int> par_bfs(n, -1), dep(n, -1);
    queue<int> q;
    dep[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (dep[to] != -1) continue;
            dep[to] = dep[v] + 1;  // 積むときに印（深さ）を付ける
            par_bfs[to] = v;
            q.push(to);
        }
    }
    // --8<-- [end:bfs-tree]

    // 誤り：スタックに積むときに印を付けると、親が早く決まりすぎて DFS 木にならない
    vector<int> par_ng(n, -1);
    vector<bool> seen_ng(n, false);
    vector<int> st_ng = {0};
    seen_ng[0] = true;
    while (!st_ng.empty()) {
        int v = st_ng.back();
        st_ng.pop_back();
        for (int to : g[v]) {
            if (seen_ng[to]) continue;
            seen_ng[to] = true;
            par_ng[to] = v;
            st_ng.push_back(to);
        }
    }

    // 親の配列から行きがけ番号 tin と出る番号 tout を作り、「木に入らない辺」の両端が祖先と子孫かを数える
    auto count_non_tree = [&](const vector<int>& par, bool want_ancestor) {
        vector<vector<int>> ch(n);
        for (int v = 1; v < n; v++) ch[par[v]].push_back(v);
        vector<int> tin(n), tout(n);
        int timer = 0;
        auto walk = [&](auto&& self, int v) -> void {
            tin[v] = timer++;
            for (int c : ch[v]) self(self, c);
            tout[v] = timer;
        };
        walk(walk, 0);
        auto is_anc = [&](int a, int b) { return tin[a] <= tin[b] && tout[b] <= tout[a]; };
        int cnt = 0;
        for (auto [u, v] : edges) {
            if (par[u] == v || par[v] == u) continue;  // 木の辺（単純グラフなので親子なら木の辺）
            bool anc = is_anc(u, v) || is_anc(v, u);
            if (anc == want_ancestor) cnt++;
        }
        return cnt;
    };
    int a = count_non_tree(par_dfs, false);
    int b = count_non_tree(par_it, false);
    int c = count_non_tree(par_bfs, true);
    int d = count_non_tree(par_ng, false);
    assert(a == 0 && b == 0 && c == 0);
    // BFS 木では、木に入らない辺の両端の深さの差が 1 以下
    for (auto [u, v] : edges) assert(abs(dep[u] - dep[v]) <= 1);
    cout << a << '\n' << b << '\n' << c << '\n' << d << '\n';
}
