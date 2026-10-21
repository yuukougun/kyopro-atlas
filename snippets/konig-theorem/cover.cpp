#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

// 二部グラフ（左 nl 頂点・右 nr 頂点、辺は (左の番号, 右の番号)）の
// 最大マッチングの大きさと、最小頂点被覆・最大独立集合を求める
struct KonigResult {
    int matching;
    vector<bool> cover_l, cover_r;  // true なら最小頂点被覆に入る
};

// --8<-- [start:core]
KonigResult konig(int nl, int nr, const vector<pair<int, int>>& edges) {
    int s = nl + nr, t = s + 1;
    atcoder::mf_graph<int> g(nl + nr + 2);
    for (int u = 0; u < nl; u++) g.add_edge(s, u, 1);
    for (int v = 0; v < nr; v++) g.add_edge(nl + v, t, 1);
    for (auto [u, v] : edges) g.add_edge(u, nl + v, 1);
    int nu = g.flow(s, t);                  // 最大マッチングの大きさ
    vector<bool> reach = g.min_cut(s);      // 残余グラフで s から届くか
    vector<bool> cover_l(nl), cover_r(nr);
    for (int u = 0; u < nl; u++) cover_l[u] = !reach[u];      // 左は届かない頂点
    for (int v = 0; v < nr; v++) cover_r[v] = reach[nl + v];  // 右は届く頂点
    return {nu, cover_l, cover_r};
}
// --8<-- [end:core]

// 小さいグラフで、最小頂点被覆を全探索して比べる
int brute_cover(int nl, int nr, const vector<pair<int, int>>& edges) {
    int n = nl + nr, best = n;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (auto [u, v] : edges) {
            if (!(mask >> u & 1) && !(mask >> (nl + v) & 1)) ok = false;
        }
        if (ok) best = min(best, __builtin_popcount(mask));
    }
    return best;
}

int main() {
    int nl, nr, m;
    cin >> nl >> nr >> m;
    vector<pair<int, int>> edges(m);
    for (auto& [u, v] : edges) cin >> u >> v;

    KonigResult r = konig(nl, nr, edges);
    int size = 0;
    for (int u = 0; u < nl; u++) size += r.cover_l[u];
    for (int v = 0; v < nr; v++) size += r.cover_r[v];
    assert(size == r.matching);  // 被覆の大きさ ＝ 最大マッチング
    for (auto [u, v] : edges) assert(r.cover_l[u] || r.cover_r[v]);  // すべての辺を覆う
    if (nl + nr <= 16) assert(brute_cover(nl, nr, edges) == r.matching);

    cout << r.matching << '\n';
    cout << "cover:";
    for (int u = 0; u < nl; u++) if (r.cover_l[u]) cout << " L" << u;
    for (int v = 0; v < nr; v++) if (r.cover_r[v]) cout << " R" << v;
    cout << '\n';
    // 被覆の補集合が最大独立集合
    cout << "independent:";
    for (int u = 0; u < nl; u++) if (!r.cover_l[u]) cout << " L" << u;
    for (int v = 0; v < nr; v++) if (!r.cover_r[v]) cout << " R" << v;
    cout << '\n';
}
