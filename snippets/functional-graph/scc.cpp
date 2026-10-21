#include <bits/stdc++.h>
#include <atcoder/scc>
using namespace std;

// 頂点 0..n-1、辺 v → a[v]。閉路上の頂点の数を ACL の scc_graph で数える。
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    // --8<-- [start:core]
    atcoder::scc_graph g(n);
    for (int v = 0; v < n; v++) g.add_edge(v, a[v]);
    int cnt = 0;
    for (const auto& comp : g.scc()) {
        // 頂点が 2 個以上の成分は閉路そのもの。1 個なら自己ループのときだけ閉路
        if (comp.size() >= 2 || a[comp[0]] == comp[0]) cnt += comp.size();
    }
    // --8<-- [end:core]

    assert(0 < cnt && cnt <= n);
    cout << cnt << '\n';
}
