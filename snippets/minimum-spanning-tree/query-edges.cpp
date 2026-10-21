// 各クエリの辺を元のグラフに 1 本だけ足したとき、その辺がある最小全域木に入りうるかを、まとめて重みの順に処理して判定する
// 入力：N M Q、続く M 行は元の辺「u v w」、続く Q 行はクエリの辺「u v w」（0-indexed。元のグラフは連結）
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

struct Edge {
    long long w;
    int u, v;
};

// --8<-- [start:core]
// ans[i]：クエリの辺 i を足したグラフで、辺 i を含む最小全域木があるか
vector<bool> can_be_in_mst(int n, const vector<Edge>& edges, const vector<Edge>& queries) {
    int m = edges.size(), q = queries.size();
    // (重み, 種類, 番号)。同じ重みなら、クエリ（種類 0）を元の辺（種類 1）より先に見る
    vector<tuple<long long, int, int>> order;
    for (int i = 0; i < m; i++) order.emplace_back(edges[i].w, 1, i);
    for (int i = 0; i < q; i++) order.emplace_back(queries[i].w, 0, i);
    sort(order.begin(), order.end());
    atcoder::dsu d(n);
    vector<bool> ans(q);
    for (const auto& [w, kind, i] : order) {
        if (kind == 0) {
            ans[i] = !d.same(queries[i].u, queries[i].v);  // クエリの辺は判定だけで、併合しない
        } else {
            d.merge(edges[i].u, edges[i].v);
        }
    }
    return ans;
}
// --8<-- [end:core]

// 確かめ用：forced の辺を先に採ってから、残りをクラスカル法で採ったときの重みの和
long long mst_weight(int n, vector<Edge> edges, const vector<Edge>& forced) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    atcoder::dsu d(n);
    long long total = 0;
    for (const auto& e : forced) {
        d.merge(e.u, e.v);
        total += e.w;
    }
    for (const auto& e : edges) {
        if (!d.same(e.u, e.v)) {
            d.merge(e.u, e.v);
            total += e.w;
        }
    }
    return total;
}

int main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<Edge> edges(m), queries(q);
    for (auto& [w, u, v] : edges) cin >> u >> v >> w;
    for (auto& [w, u, v] : queries) cin >> u >> v >> w;
    vector<bool> ans = can_be_in_mst(n, edges, queries);
    for (int i = 0; i < q; i++) {
        // 辺 i を必ず採ったときの最小が、足したグラフの最小全域木の重みと等しいか
        vector<Edge> all = edges;
        all.push_back(queries[i]);
        bool expected = queries[i].u != queries[i].v &&
                        mst_weight(n, all, {queries[i]}) == mst_weight(n, all, {});
        assert(ans[i] == expected);
        cout << (ans[i] ? "Yes" : "No") << '\n';
    }
}
