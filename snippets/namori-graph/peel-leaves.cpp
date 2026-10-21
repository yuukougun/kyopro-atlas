#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// N 頂点 N 辺の連結な無向グラフ（多重辺・自己ループも可）で、
// 次数 1 の頂点を削って閉路を求め、閉路の頂点ごとにぶら下がる木に分ける。
// 質問 (x, y) には、2 点間の単純パスが一意なら Yes を答える。
int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> edges(n);
    for (auto& [u, v] : edges) {
        cin >> u >> v;
        u--, v--;  // 1-indexed → 0-indexed
    }
    // --8<-- [start:core]
    vector<vector<int>> g(n);
    vector<int> deg(n, 0);
    for (auto [u, v] : edges) {
        g[u].push_back(v);
        g[v].push_back(u);
        deg[u]++, deg[v]++;  // 自己ループは次数が 2 増える
    }
    // 次数 1 の頂点をキューに入れ、削るたびに隣の次数を減らす
    vector<bool> on_cycle(n, true);
    queue<int> que;
    for (int v = 0; v < n; v++) {
        if (deg[v] == 1) que.push(v);
    }
    while (!que.empty()) {
        int v = que.front();
        que.pop();
        on_cycle[v] = false;
        for (int w : g[v]) {
            if (!on_cycle[w]) continue;  // 削った頂点は見ない
            deg[w]--;
            if (deg[w] == 1) que.push(w);
        }
    }
    // 両端が閉路の上にある辺は閉路の辺。それ以外の辺で結ぶと、
    // 成分が「閉路の頂点 1 つとそこからぶら下がる木」になる
    atcoder::dsu d(n);
    for (auto [u, v] : edges) {
        if (!(on_cycle[u] && on_cycle[v])) d.merge(u, v);
    }
    // --8<-- [end:core]
    int cycle_len = 0;
    for (int v = 0; v < n; v++) cycle_len += on_cycle[v];
    assert(cycle_len >= 1);
    assert(d.groups().size() == (size_t)cycle_len);  // 木は閉路の頂点の数だけある
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        cout << (d.same(x, y) ? "Yes" : "No") << '\n';
    }
}
