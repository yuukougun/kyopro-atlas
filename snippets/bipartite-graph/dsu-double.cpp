// 頂点を 2 倍にした Union-Find（ACL の dsu）で、辺を足すたびに二部グラフかを答える
// 入力：N M、続く M 行は辺「u v」（1-indexed）。各辺の後に Yes（二部グラフ）か No を出力
#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    // --8<-- [start:core]
    // 頂点 v は「v が色 0」、頂点 v + n は「v が色 1」を表す
    atcoder::dsu d(2 * n);
    bool bipartite = true;  // 一度塗れなくなったら、辺を足しても戻らない
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;           // 1-indexed → 0-indexed
        d.merge(u, v + n);  // u が色 0 なら v は色 1
        d.merge(u + n, v);  // u が色 1 なら v は色 0
        if (d.same(u, u + n)) bipartite = false;  // 「u が色 0」と「u が色 1」が同時に決まる
        cout << (bipartite ? "Yes" : "No") << '\n';
    }
    // --8<-- [end:core]
    // 矛盾は辺の端点で最初に起きるので、端点だけ調べれば足りることを確かめる
    if (bipartite) {
        for (int v = 0; v < n; v++) assert(!d.same(v, v + n));
    }
}
