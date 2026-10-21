// 無向グラフで s と t を結ぶ道について、辺を共有しない道の最大本数と、
// s・t 以外の頂点を共有しない道の最大本数を最大流で求める。
// 無向の辺は向きの逆な 2 本の辺にし、頂点の容量は頂点を入口と出口に分けて表す。
// 入力は N M s t と辺 (u, v)（0-indexed、無向）。
#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<pair<int, int>> es(m);
    for (auto& [u, v] : es) cin >> u >> v;

    // --8<-- [start:edge]
    // 辺を共有しない道：無向の辺 {u, v} を u→v と v→u の 2 本（どちらも容量 1）にする
    atcoder::mf_graph<int> ge(n);
    for (auto [u, v] : es) {
        ge.add_edge(u, v, 1);
        ge.add_edge(v, u, 1);
    }
    int edge_disjoint = ge.flow(s, t);
    // --8<-- [end:edge]

    // --8<-- [start:vertex]
    // 頂点を共有しない道：頂点 v を入口 2v と出口 2v+1 に分け、入口→出口に容量 1 を付ける
    auto in = [](int v) { return 2 * v; };
    auto out = [](int v) { return 2 * v + 1; };
    atcoder::mf_graph<int> gv(2 * n);
    for (int v = 0; v < n; v++) gv.add_edge(in(v), out(v), 1);
    for (auto [u, v] : es) {
        gv.add_edge(out(u), in(v), 1);  // 元の辺は出口から入口へ
        gv.add_edge(out(v), in(u), 1);
    }
    int vertex_disjoint = gv.flow(out(s), in(t));  // s は出口から出し、t は入口で受ける
    // --8<-- [end:vertex]

    cout << edge_disjoint << ' ' << vertex_disjoint << '\n';
    assert(vertex_disjoint <= edge_disjoint);
    return 0;
}
