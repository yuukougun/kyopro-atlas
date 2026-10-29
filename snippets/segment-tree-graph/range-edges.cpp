#include <bits/stdc++.h>
using namespace std;

// 頂点 0..n-1 の上に、区間 [l1, r1) の全頂点から区間 [l2, r2) の全頂点へのコスト w の辺を張る
// 頂点の番号：下向きの木のノード i は i（1 <= i < 2n。葉 n + v が元の頂点 v）、
//             上向きの木の内部ノード i（1 <= i < n）は 2n + i（葉は下向きの木と共有する）
// --8<-- [start:core]
struct RangeEdgeGraph {
    int n;
    vector<vector<pair<int, long long>>> g;
    explicit RangeEdgeGraph(int n_) : n(n_), g(3 * n_) {
        for (int i = 1; i < n; i++) {
            for (int c : {2 * i, 2 * i + 1}) {
                g[i].push_back({c, 0});          // 下向きの木：親 → 子（コスト 0）
                g[up(c)].push_back({up(i), 0});  // 上向きの木：子 → 親（コスト 0）
            }
        }
    }
    int up(int i) const { return i >= n ? i : 2 * n + i; }
    int vertex(int v) const { return n + v; }  // 元の頂点 v の番号（葉）
    // [l, r) を覆うノード（O(log n) 個）を f に渡す
    template <class F>
    void cover(int l, int r, F f) const {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) f(l++);
            if (r & 1) f(--r);
        }
    }
    // [l1, r1) の全頂点 → [l2, r2) の全頂点（コスト w）。中継の頂点 x を 1 つ足す
    void add_edge(int l1, int r1, int l2, int r2, long long w) {
        int x = g.size();
        g.emplace_back();
        cover(l1, r1, [&](int i) { g[up(i)].push_back({x, w}); });
        cover(l2, r2, [&](int i) { g[x].push_back({i, 0}); });
    }
};
// --8<-- [end:core]

const long long INF = 1LL << 60;  // INF + INF でもあふれない大きさ

vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& g, int s) {
    vector<long long> dist(g.size(), INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, v] = pq.top();
        pq.pop();
        if (d != dist[v]) continue;
        for (auto [to, w] : g[v]) {
            if (dist[v] + w < dist[to]) {
                dist[to] = dist[v] + w;
                pq.push({dist[to], to});
            }
        }
    }
    return dist;
}

struct Query {
    int l1, r1, l2, r2;
    long long w;
};

// セグメント木の形の補助頂点を使って、頂点 0 からの距離を求める
vector<long long> solve(int n, const vector<Query>& qs) {
    RangeEdgeGraph G(n);
    for (const auto& q : qs) G.add_edge(q.l1, q.r1, q.l2, q.r2, q.w);
    vector<long long> d = dijkstra(G.g, G.vertex(0));
    vector<long long> res(n);
    for (int v = 0; v < n; v++) res[v] = d[G.vertex(v)];
    return res;
}

// 愚直：区間の全組に辺を張る
vector<long long> naive(int n, const vector<Query>& qs) {
    vector<vector<pair<int, long long>>> g(n);
    for (const auto& q : qs)
        for (int u = q.l1; u < q.r1; u++)
            for (int v = q.l2; v < q.r2; v++) g[u].push_back({v, q.w});
    return dijkstra(g, 0);
}

int main() {
    // 小さい乱数の入力で愚直と照らし合わせる
    mt19937 rng(1);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 9 + 1, m = rng() % 8;
        vector<Query> qs;
        for (int j = 0; j < m; j++) {
            int a = rng() % n, b = rng() % n, c = rng() % n, d = rng() % n;
            qs.push_back({min(a, b), max(a, b) + 1, min(c, d), max(c, d) + 1, (long long)(rng() % 10)});
        }
        assert(solve(n, qs) == naive(n, qs));
    }
    // 入力：n m、続いて m 行の l1 r1 l2 r2 w（0-indexed、半開区間）。頂点 0 からの距離を出す（届かなければ -1）
    int n, m;
    cin >> n >> m;
    vector<Query> qs(m);
    for (auto& q : qs) cin >> q.l1 >> q.r1 >> q.l2 >> q.r2 >> q.w;
    vector<long long> d = solve(n, qs);
    assert(d == naive(n, qs));
    for (int v = 0; v < n; v++) cout << (d[v] == INF ? -1 : d[v]) << (v + 1 < n ? ' ' : '\n');
}
