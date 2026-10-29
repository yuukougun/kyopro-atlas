// 無向グラフ（辺の重みは 0 以上）で、頂点 0 からの最短路木の辺の番号（1-indexed）を昇順に出力する。
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1LL << 60;  // INF + INF でもあふれない大きさ

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<tuple<int, long long, int>>> g(n);  // (行き先, 重み, 辺の番号)
    for (int i = 0; i < m; i++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        a--, b--;
        assert(w >= 0);
        g[a].push_back({b, w, i});
        g[b].push_back({a, w, i});
    }
    vector<long long> dist(n, INF);
    vector<int> par_edge(n, -1);  // v に入る最短路木の辺
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        // --8<-- [start:core]
        for (auto [v, w, id] : g[u]) {
            if (dist[u] + w < dist[v]) {  // 真に短くなったときだけ親の辺を付け替える
                dist[v] = dist[u] + w;
                par_edge[v] = id;
                pq.push({dist[v], v});
            }
        }
        // --8<-- [end:core]
    }
    vector<int> tree;
    for (int v = 1; v < n; v++) {
        if (par_edge[v] >= 0) tree.push_back(par_edge[v]);
    }
    sort(tree.begin(), tree.end());
    for (int i = 0; i < (int)tree.size(); i++) cout << tree[i] + 1 << (i + 1 < (int)tree.size() ? " " : "");
    cout << '\n';
}
