// ACL の mf_graph の使い方：容量付きの有向グラフで s から t への最大流を求め、各辺に流れた量を出力する。
// 入力は N M s t と辺 (u, v, c)（0-indexed、有向、容量 c）。
// 最大流の値と最小カットの容量が一致することを assert で確かめる。
#include <bits/stdc++.h>
#include <atcoder/maxflow>
using namespace std;

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<int> eu(m), ev(m);
    vector<long long> ec(m);
    for (int i = 0; i < m; i++) cin >> eu[i] >> ev[i] >> ec[i];

    // --8<-- [start:core]
    atcoder::mf_graph<long long> g(n);  // 容量の合計が int を超えうるなら long long
    for (int i = 0; i < m; i++) {
        g.add_edge(eu[i], ev[i], ec[i]);  // i 番目に足した辺は番号 i になる
    }
    long long f = g.flow(s, t);  // s から t へ流せるだけ流し、流した量を返す
    cout << f << '\n';
    for (int i = 0; i < m; i++) {
        auto e = g.get_edge(i);  // e.from, e.to, e.cap（容量）, e.flow（流れた量）
        cout << e.from << "->" << e.to << ' ' << e.flow << '/' << e.cap << '\n';
    }
    // --8<-- [end:core]

    // 流し終えた残余グラフで s から届く頂点の集合 S が最小カットを与える
    vector<bool> side = g.min_cut(s);
    long long cut = 0;
    for (int i = 0; i < m; i++) {
        if (side[eu[i]] && !side[ev[i]]) cut += ec[i];
    }
    assert(cut == f);
    assert(side[s] && !side[t]);
    return 0;
}
