// 辺の重みが非負の有向グラフで、頂点 1 から各頂点への最短距離と、頂点 N への経路を求める。
// 入力：N M、続いて M 行の u v w（1-indexed、u から v へ重み w の辺）。
// 出力：1 行目に各頂点の最短距離（届かなければ -1）、2 行目に頂点 1 から N への経路（届かなければ -1）。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const long long INF = 1LL << 60;  // INF + INF でもあふれない大きさ

// g[v] = {(行き先, 重み)}。重みは非負。dist と、最短路の木での親 par を返す
pair<vector<long long>, vector<int>> dijkstra(const vector<vector<pair<int, long long>>>& g, int s) {
    int n = g.size();
    vector<long long> dist(n, INF);
    vector<int> par(n, -1);
    // (距離, 頂点) の最小ヒープ。greater<> を付けないと最大ヒープになる
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d > dist[v]) continue;  // 古い組：v はもっと短い距離で確定済み
        // ここで dist[v] = d が確定する
        for (auto [to, w] : g[v]) {
            if (d + w < dist[to]) {
                dist[to] = d + w;
                par[to] = v;
                pq.push({dist[to], to});
            }
        }
    }
    return {dist, par};
}
// --8<-- [end:core]

// --8<-- [start:path]
// par を終点から始点までたどり、反転して始点からの順にする
vector<int> restore_path(const vector<int>& par, int t) {
    vector<int> path;
    for (int v = t; v != -1; v = par[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}
// --8<-- [end:path]

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        assert(w >= 0);
        g[u - 1].push_back({v - 1, w});
    }
    auto [dist, par] = dijkstra(g, 0);
    for (int v = 0; v < n; v++) {
        cout << (dist[v] == INF ? -1 : dist[v]) << (v + 1 < n ? ' ' : '\n');
    }
    if (dist[n - 1] == INF) {
        cout << -1 << '\n';
    } else {
        vector<int> path = restore_path(par, n - 1);
        assert(path.front() == 0);
        for (int i = 0; i < (int)path.size(); i++) {
            cout << path[i] + 1 << (i + 1 < (int)path.size() ? ' ' : '\n');
        }
    }
}
