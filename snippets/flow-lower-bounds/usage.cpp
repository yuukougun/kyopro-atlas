#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

// --8<-- [start:core]
// 辺 (u, v, L, R) は「u から v へ L 以上 R 以下を流す」。下限を満たす s-t 流のうち
// 流量（s から出る量 − s に入る量）が最大のものの値を返し、満たせないなら -1 を返す。
// t から s への辺で流れを戻すので、流量が 0 以上の流れだけを考える。
long long max_flow_with_lower_bounds(int n, const vector<tuple<int, int, long long, long long>>& es, int s, int t) {
    const long long INF = 1LL << 60;
    atcoder::mf_graph<long long> g(n + 2);
    int S = n, T = n + 1;          // 過不足を調整する超頂点
    vector<long long> d(n, 0);     // 下限の分で v に入る量 − 出る量
    for (auto [u, v, l, r] : es) {
        g.add_edge(u, v, r - l);   // 下限を先に流したことにし、残りの幅だけを容量にする
        d[v] += l;
        d[u] -= l;
    }
    long long need = 0;
    for (int v = 0; v < n; v++) {
        if (d[v] > 0) { g.add_edge(S, v, d[v]); need += d[v]; }
        if (d[v] < 0) g.add_edge(v, T, -d[v]);
    }
    g.add_edge(t, s, INF);         // t に着いた流れを s へ戻し、循環として扱う
    if (g.flow(S, T) != need) return -1;   // 過不足を埋めきれなければ下限を満たせない
    // t から s への辺の逆辺（容量はすでに流れた量）も通るので、合計の流量が返る
    return g.flow(s, t);
}
// --8<-- [end:core]

// 小さいグラフで、各辺の流量を全通り試す（確かめ用）
long long brute(int n, const vector<tuple<int, int, long long, long long>>& es, int s, int t) {
    int m = es.size();
    vector<long long> f(m);
    long long best = -1;
    auto rec = [&](auto&& self, int i) -> void {
        if (i == m) {
            vector<long long> bal(n, 0);   // 出る量 − 入る量
            for (int j = 0; j < m; j++) {
                auto [u, v, l, r] = es[j];
                bal[u] += f[j];
                bal[v] -= f[j];
            }
            for (int v = 0; v < n; v++) {
                if (v != s && v != t && bal[v] != 0) return;
            }
            if (bal[s] >= 0) best = max(best, bal[s]);
            return;
        }
        auto [u, v, l, r] = es[i];
        for (long long x = l; x <= r; x++) {
            f[i] = x;
            self(self, i + 1);
        }
    };
    rec(rec, 0);
    return best;
}

int main() {
    mt19937 rng(12345);
    for (int iter = 0; iter < 3000; iter++) {
        int n = 2 + rng() % 3;
        int m = rng() % 5;
        vector<tuple<int, int, long long, long long>> es;
        for (int j = 0; j < m; j++) {
            int u = rng() % n, v = rng() % n;
            long long l = rng() % 3, r = l + rng() % 3;
            es.emplace_back(u, v, l, r);
        }
        assert(max_flow_with_lower_bounds(n, es, 0, n - 1) == brute(n, es, 0, n - 1));
    }

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<tuple<int, int, long long, long long>> es;
    for (int j = 0; j < m; j++) {
        int u, v;
        long long l, r;
        cin >> u >> v >> l >> r;
        es.emplace_back(u, v, l, r);
    }
    cout << max_flow_with_lower_bounds(n, es, s, t) << '\n';
}
