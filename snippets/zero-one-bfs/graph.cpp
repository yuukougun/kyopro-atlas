// 01-BFS：辺の重みが 0 か 1 の有向グラフで、頂点 s から各頂点への最短距離を求める。
// 入力：N M s、続く M 行に u v w（0-indexed、w は 0 か 1）。届かない頂点は -1 を出力する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    vector<vector<pair<int, int>>> g(n);  // g[u] = {(v, w), …}
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        assert(0 <= u && u < n && 0 <= v && v < n && (w == 0 || w == 1));
        g[u].push_back({v, w});
    }

    // --8<-- [start:core]
    const int INF = INT_MAX;
    vector<int> dist(n, INF);
    deque<pair<int, int>> dq;  // (push したときの距離, 頂点)
    dist[s] = 0;
    dq.push_back({0, s});
    while (!dq.empty()) {
        auto [d, u] = dq.front();
        dq.pop_front();
        if (d > dist[u]) continue;  // 後でもっと短く更新された古い組は読み飛ばす
        // ここで dist[u] が確定する（deque の先頭は常に最小）
        for (auto [v, w] : g[u]) {
            int nd = d + w;
            if (nd >= dist[v]) continue;  // 等しいときに push すると、重み 0 の閉路で止まらない
            dist[v] = nd;
            if (w == 0) dq.push_front({nd, v});  // 距離 d のまま：先頭へ
            else dq.push_back({nd, v});          // 距離 d + 1：末尾へ
        }
    }
    // --8<-- [end:core]

    for (int v = 0; v < n; v++) cout << (dist[v] == INF ? -1 : dist[v]) << '\n';
}
