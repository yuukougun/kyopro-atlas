// ACL の scc_graph でトポロジカル順を得る。N 頂点 M 辺の有向グラフ（入力は 1-indexed）。
// 成分の数が N より少ないか自己ループがあれば、閉路があるので -1 を出力する。
#include <bits/stdc++.h>
#include <atcoder/scc>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    assert(n >= 1 && m >= 0);
    atcoder::scc_graph sg(n);
    bool self_loop = false;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        assert(0 <= a && a < n && 0 <= b && b < n);
        if (a == b) self_loop = true;
        g[a].push_back(b);
        sg.add_edge(a, b);
    }

    // --8<-- [start:core]
    // sg は atcoder::scc_graph sg(n); に add_edge(a, b) で辺を足したもの
    vector<vector<int>> groups = sg.scc();  // 成分のリスト。トポロジカル順に並ぶ
    if ((int)groups.size() < n || self_loop) {  // 2 頂点以上の成分か自己ループ＝閉路
        cout << -1 << '\n';
        return 0;
    }
    vector<int> order;
    for (auto& c : groups) order.push_back(c[0]);  // DAG なら各成分は 1 頂点
    // --8<-- [end:core]

    vector<int> pos(n);
    for (int i = 0; i < n; i++) pos[order[i]] = i;
    for (int u = 0; u < n; u++) for (int v : g[u]) assert(pos[u] < pos[v]);
    cout << "ok\n";
}
