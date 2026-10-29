// 辺のコストを K 回まで 0 にできるときの、頂点 0 から頂点 N-1 への最短路。
// 状態 (頂点 v, 使った回数 k) を整数 v * (K + 1) + k に詰めてダイクストラ法を回す。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const long long INF = 1LL << 60;  // INF + INF でもあふれない大きさ

// g[v] = {(行き先, コスト)}。返り値は dist[v * (K + 1) + k]
vector<long long> layered_dijkstra(const vector<vector<pair<int, long long>>>& g, int K, int s) {
    int n = g.size(), L = K + 1;               // 層の数 L = K + 1
    vector<long long> dist(n * L, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[s * L] = 0;                           // 状態 (v, k) は整数 v * L + k
    pq.push({0, s * L});
    while (!pq.empty()) {
        auto [d, x] = pq.top();
        pq.pop();
        if (d > dist[x]) continue;             // 古い候補は捨てる
        int v = x / L, k = x % L;              // 整数から状態を戻す
        for (auto [to, c] : g[v]) {
            // ふつうに通る：同じ層の中を進む
            int y = to * L + k;
            if (d + c < dist[y]) {
                dist[y] = d + c;
                pq.push({d + c, y});
            }
            // 無料で通る：1 つ下の層へ降りる（層は戻らない）
            if (k < K && d < dist[y + 1]) {    // y + 1 は (to, k + 1)
                dist[y + 1] = d;
                pq.push({d, y + 1});
            }
        }
    }
    return dist;
}
// --8<-- [end:core]

int main() {
    int n, m, K;
    cin >> n >> m >> K;
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        a--, b--;                              // 入力は 1-indexed
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    vector<long long> dist = layered_dijkstra(g, K, 0);
    long long ans = INF;
    for (int k = 0; k <= K; k++) ans = min(ans, dist[(n - 1) * (K + 1) + k]);  // 答えは全部の層の最小
    assert(dist[0] == 0);                      // 始点の状態 (0, 0) の距離は 0
    cout << (ans == INF ? -1 : ans) << '\n';
}
