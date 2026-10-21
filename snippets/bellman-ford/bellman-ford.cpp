// 負の辺を含む有向グラフで、頂点 1 から各頂点への最短距離を求める。
// 負閉路を経由していくらでも短くできる頂点は -INF、届かない頂点は INF と出力する。
// 入力：N M、続いて M 行の u v w（1-indexed、u から v へ重み w の辺）。
// 出力：各頂点の最短距離（数・INF・-INF）を空白区切りで 1 行。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const long long INF = LLONG_MAX / 4;  // INF + 重み でもあふれない大きさ

struct Edge {
    int from, to;
    long long w;
};

// 始点 s からの最短距離を返す。届かない頂点は INF のまま。
// neg[v] = true は、負閉路を経由して v への距離をいくらでも小さくできること（-∞）を表す
pair<vector<long long>, vector<bool>> bellman_ford(int n, const vector<Edge>& edges, int s) {
    vector<long long> dist(n, INF);
    dist[s] = 0;
    // 1. 全辺の緩和を N-1 回。負閉路の影響がない頂点は、これで確定する
    for (int iter = 0; iter < n - 1; iter++) {
        bool updated = false;
        for (auto [u, v, w] : edges) {
            if (dist[u] == INF) continue;  // 届いていない頂点からは緩和しない
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }
        if (!updated) break;  // 1 回も更新がなければ、もう変わらない
    }
    // 2. さらに N 回。まだ更新される頂点と、そこから辺でたどれる頂点に印を付ける
    vector<bool> neg(n, false);
    for (int iter = 0; iter < n; iter++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] == INF) continue;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                neg[v] = true;
            }
            if (neg[u]) neg[v] = true;  // -∞ は辺の先へ伝わる
        }
    }
    return {dist, neg};
}
// --8<-- [end:core]

// 確かめ用：ワーシャルフロイド法で負閉路の影響を求めた答えと比べる
vector<string> brute(int n, const vector<Edge>& edges, int s) {
    vector<vector<long long>> d(n, vector<long long>(n, INF));
    vector<vector<bool>> reach(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) d[i][i] = 0, reach[i][i] = true;
    for (auto [u, v, w] : edges) d[u][v] = min(d[u][v], w), reach[u][v] = true;
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (reach[i][k] && reach[k][j]) reach[i][j] = true;
                if (d[i][k] < INF && d[k][j] < INF) d[i][j] = max(-INF, min(d[i][j], d[i][k] + d[k][j]));
            }
    vector<string> res(n);
    for (int v = 0; v < n; v++) {
        if (!reach[s][v]) {
            res[v] = "INF";
            continue;
        }
        bool minus_inf = false;
        for (int c = 0; c < n; c++) {
            if (reach[s][c] && d[c][c] < 0 && reach[c][v]) minus_inf = true;
        }
        res[v] = minus_inf ? "-INF" : to_string(d[s][v]);
    }
    return res;
}

vector<string> solve(int n, const vector<Edge>& edges, int s) {
    auto [dist, neg] = bellman_ford(n, edges, s);
    vector<string> res(n);
    for (int v = 0; v < n; v++) {
        if (dist[v] == INF) res[v] = "INF";
        else if (neg[v]) res[v] = "-INF";
        else res[v] = to_string(dist[v]);
    }
    return res;
}

int main() {
    // 小さいランダムなグラフで、全探索の答えと一致することを確かめる
    mt19937 rng(12345);
    for (int t = 0; t < 2000; t++) {
        int n = rng() % 6 + 1, m = rng() % 10;
        vector<Edge> edges;
        for (int i = 0; i < m; i++) {
            edges.push_back({int(rng() % n), int(rng() % n), (long long)(rng() % 11) - 4});
        }
        assert(solve(n, edges, 0) == brute(n, edges, 0));
    }

    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        edges.push_back({u - 1, v - 1, w});
    }
    auto res = solve(n, edges, 0);
    for (int v = 0; v < n; v++) cout << res[v] << (v + 1 < n ? ' ' : '\n');
}
