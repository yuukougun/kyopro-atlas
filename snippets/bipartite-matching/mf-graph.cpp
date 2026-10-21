// 二部マッチングを ACL の mf_graph で求める。
// 入力：左の頂点数 L、右の頂点数 R、辺の本数 M と、M 本の辺 (u, v)（左 u と右 v、どちらも 0-indexed）。
// 出力：最大マッチングの大きさと、組 (u, v) を u の小さい順に。
#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

int main() {
    int l, r, m;
    cin >> l >> r >> m;
    vector<int> eu(m), ev(m);
    for (int i = 0; i < m; i++) cin >> eu[i] >> ev[i];

    // --8<-- [start:core]
    // 頂点の番号：左 0..L-1、右 L..L+R-1、始点 s = L+R、終点 t = L+R+1
    int s = l + r, t = l + r + 1;
    atcoder::mf_graph<int> g(l + r + 2);
    for (int u = 0; u < l; u++) g.add_edge(s, u, 1);      // 左の頂点は 1 回まで
    for (int v = 0; v < r; v++) g.add_edge(l + v, t, 1);  // 右の頂点も 1 回まで
    vector<int> id(m);  // 左→右の辺が何番目に足されたかを覚えておく（復元に使う）
    for (int i = 0; i < m; i++) id[i] = g.add_edge(eu[i], l + ev[i], 1);

    int size = g.flow(s, t);  // 最大流の値 = 最大マッチングの大きさ
    vector<pair<int, int>> pairs;
    for (int i = 0; i < m; i++) {
        if (g.get_edge(id[i]).flow == 1) pairs.push_back({eu[i], ev[i]});  // 流れた辺が組
    }
    // --8<-- [end:core]

    sort(pairs.begin(), pairs.end());
    assert((int)pairs.size() == size);
    cout << size << '\n';
    for (auto [u, v] : pairs) cout << u << ' ' << v << '\n';
}
