#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long w;
        cin >> a >> b >> w;
        g[a].push_back({b, w});
    }
    const long long INF = 1LL << 60;
    vector<long long> dist(n, INF);
    using P = pair<long long, int>;
    priority_queue<P, vector<P>, greater<P>> pq;
    dist[0] = 0;
    pq.push({0, 0});
    // --8<-- [start:core]
    while (!pq.empty()) {
        auto [d, v] = pq.top();  // 値で受ける（コピー）。& を付けない
        pq.pop();
        if (d > dist[v]) continue;
        for (auto [to, w] : g[v]) {
            if (dist[to] > d + w) {
                dist[to] = d + w;
                pq.push({dist[to], to});  // push しても d・v は変わらない
            }
        }
    }
    // --8<-- [end:core]
    for (int i = 0; i < n; i++) cout << (dist[i] == INF ? -1 : dist[i]) << " \n"[i == n - 1];
}
