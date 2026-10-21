#include <bits/stdc++.h>
#include <atcoder/scc>
using namespace std;

// 有向グラフで、ある閉路に含まれる頂点の数を数える
int main() {
    int n, m;
    cin >> n >> m;
    // --8<-- [start:core]
    atcoder::scc_graph g(n);
    vector<bool> self_loop(n, false);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g.add_edge(u, v);
        if (u == v) self_loop[u] = true;  // 自己ループは大きさ 1 の成分でも閉路
    }
    int cnt = 0;
    for (const auto& grp : g.scc()) {
        if (grp.size() >= 2 || self_loop[grp[0]]) cnt += grp.size();
    }
    // --8<-- [end:core]
    assert(0 <= cnt && cnt <= n);
    cout << cnt << '\n';
}
