#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

// --8<-- [start:core]
// 各クエリ (u, v) について、u から v への経路の辺の重みの最大値の最小値を返す
// u == v なら 0、つながらなければ -1
vector<long long> bottlenecks(int n, vector<array<long long, 3>> edges,
                              const vector<pair<int, int>>& qs) {
    int q = qs.size();
    vector<long long> ans(q, -1);
    vector<vector<int>> ids(n);  // ids[r]：端点が r の成分にある未解決のクエリ
    for (int i = 0; i < q; i++) {
        auto [u, v] = qs[i];
        if (u == v) {
            ans[i] = 0;
            continue;
        }
        ids[u].push_back(i);
        ids[v].push_back(i);
    }
    sort(edges.begin(), edges.end(),
         [](const auto& a, const auto& b) { return a[2] < b[2]; });
    atcoder::dsu d(n);
    for (auto [u, v, w] : edges) {
        int a = d.leader(u), b = d.leader(v);
        if (a == b) continue;
        int r = d.merge(a, b);
        int o = (r == a ? b : a);  // 代表元でなくなった方
        if (ids[o].size() > ids[r].size()) swap(ids[o], ids[r]);
        // 小さい方 ids[o] だけを調べる。相手の端点が併合した成分にあれば答えが出る
        for (int i : ids[o]) {
            if (ans[i] != -1) continue;  // すでに答えが出た（もう一方の端点の写し）
            auto [x, y] = qs[i];
            if (d.same(x, y)) ans[i] = w;
            else ids[r].push_back(i);
        }
        ids[o].clear();
        ids[o].shrink_to_fit();
    }
    return ans;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<array<long long, 3>> edges(m);
    for (auto& [u, v, w] : edges) cin >> u >> v >> w;
    int q;
    cin >> q;
    vector<pair<int, int>> qs(q);
    for (auto& [u, v] : qs) cin >> u >> v;
    auto ans = bottlenecks(n, edges, qs);

    // 確かめ：しきい値 x 以下の辺だけで連結かを、辺の重みごとに調べる
    for (int i = 0; i < q; i++) {
        auto [u, v] = qs[i];
        long long best = (u == v ? 0 : -1);
        if (u != v) {
            for (auto [a, b, x] : edges) {
                atcoder::dsu d(n);
                for (auto [c, e, w] : edges)
                    if (w <= x) d.merge(c, e);
                if (d.same(u, v) && (best == -1 || x < best)) best = x;
            }
        }
        assert(ans[i] == best);
    }
    for (long long x : ans) cout << x << '\n';
}
