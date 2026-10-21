// 自作の最小費用流（逐次最短路＋ポテンシャル）。ACL の mcf_graph と結果が一致することを assert で確かめる。
// 入力：N M S T、続いて M 行の u v cap cost（0-indexed。cost ≥ 0）。
// 出力：S から T へ流せるだけ流したときの流量と最小コスト。
#include <bits/stdc++.h>
#include <atcoder/mincostflow>
using namespace std;

// --8<-- [start:core]
struct MinCostFlow {
    struct Edge {
        int to, rev;  // rev は逆辺が g[to] の何番目か
        long long cap, cost;
    };
    int n;
    vector<vector<Edge>> g;
    MinCostFlow(int n) : n(n), g(n) {}

    void add_edge(int u, int v, long long cap, long long cost) {  // cost ≥ 0
        g[u].push_back({v, (int)g[v].size(), cap, cost});
        g[v].push_back({u, (int)g[u].size() - 1, 0, -cost});  // 逆辺：容量 0、コストは符号を反転
    }

    // 流量 limit まで流し、(流量, 最小コスト) を返す
    pair<long long, long long> flow(int s, int t, long long limit) {
        const long long INF = LLONG_MAX / 4;
        vector<long long> h(n, 0), dist(n);  // h はポテンシャル。最初は 0（コストが 0 以上なので）
        vector<int> pv(n), pe(n);            // 最短路の木での親と、親からの辺の番号
        long long f = 0, cost = 0;
        while (f < limit) {
            // 付け替えたコスト cost + h[u] - h[v]（0 以上）でダイクストラ法
            fill(dist.begin(), dist.end(), INF);
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
            dist[s] = 0;
            pq.push({0, s});
            while (!pq.empty()) {
                auto [d, v] = pq.top();
                pq.pop();
                if (d > dist[v]) continue;
                for (int i = 0; i < (int)g[v].size(); i++) {
                    const Edge& e = g[v][i];
                    if (e.cap == 0) continue;  // 残余グラフにない辺
                    long long nd = d + e.cost + h[v] - h[e.to];
                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = v;
                        pe[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }
            if (dist[t] == INF) break;  // もう流せない
            // ポテンシャルの更新。dist[t] で頭打ちにすると、届かない頂点も含めて付け替えたコストが 0 以上に保たれる
            for (int v = 0; v < n; v++) h[v] += min(dist[v], dist[t]);
            long long add = limit - f;
            for (int v = t; v != s; v = pv[v]) add = min(add, g[pv[v]][pe[v]].cap);
            for (int v = t; v != s; v = pv[v]) {
                Edge& e = g[pv[v]][pe[v]];
                e.cap -= add;
                g[v][e.rev].cap += add;
            }
            f += add;
            cost += add * (h[t] - h[s]);  // h[t] - h[s] が元のコストでの最短路の長さ
        }
        return {f, cost};
    }
};
// --8<-- [end:core]

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    MinCostFlow mine(n);
    atcoder::mcf_graph<long long, long long> acl(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long cap, cost;
        cin >> u >> v >> cap >> cost;
        mine.add_edge(u, v, cap, cost);
        acl.add_edge(u, v, cap, cost);
    }
    auto [f, c] = mine.flow(s, t, LLONG_MAX / 4);
    auto [f2, c2] = acl.flow(s, t);
    assert(f == f2 && c == c2);
    cout << f << ' ' << c << '\n';
}
