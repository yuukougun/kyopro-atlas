#include <bits/stdc++.h>
using namespace std;

// 頂点 to へ向かう辺。時刻が k の倍数のときだけ出発でき、t かかる
struct Edge {
    int to;
    long long t, k;
};

const long long INF = LLONG_MAX;

// --8<-- [start:core]
// 時刻 d に辺 e の始点にいるときの、e の終点への到着時刻（次の出発時刻まで待つ）
long long arrive(long long d, const Edge& e) {
    long long depart = (d + e.k - 1) / e.k * e.k;  // d 以上で最小の k の倍数
    return depart + e.t;
}

// dist[v] = 時刻 0 に s を出たとき、v に着ける最も早い時刻
vector<long long> earliest_arrival(const vector<vector<Edge>>& g, int s) {
    int n = g.size();
    vector<long long> dist(n, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) continue;  // 古い組は読み飛ばす
        for (const Edge& e : g[v]) {
            long long a = arrive(d, e);  // 最も早く着いた時刻から出るのが最善（FIFO 性）
            if (a < dist[e.to]) {
                dist[e.to] = a;
                pq.push({a, e.to});
            }
        }
    }
    return dist;
}
// --8<-- [end:core]

// 確かめ用：変化がなくなるまで全辺で緩和を繰り返す
vector<long long> brute(const vector<vector<Edge>>& g, int s) {
    int n = g.size();
    vector<long long> dist(n, INF);
    dist[s] = 0;
    bool changed = true;
    while (changed) {
        changed = false;
        for (int v = 0; v < n; v++) {
            if (dist[v] == INF) continue;
            for (const Edge& e : g[v]) {
                long long a = arrive(dist[v], e);
                if (a < dist[e.to]) {
                    dist[e.to] = a;
                    changed = true;
                }
            }
        }
    }
    return dist;
}

int main() {
    int n, m, x, y;
    cin >> n >> m >> x >> y;
    x--, y--;
    vector<vector<Edge>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        long long t, k;
        cin >> a >> b >> t >> k;
        a--, b--;
        g[a].push_back({b, t, k});
        g[b].push_back({a, t, k});
    }
    vector<long long> dist = earliest_arrival(g, x);
    assert(dist == brute(g, x));
    assert(dist[x] == 0);
    cout << (dist[y] == INF ? -1 : dist[y]) << '\n';
}
