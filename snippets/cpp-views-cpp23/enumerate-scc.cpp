#include <bits/stdc++.h>
#include <atcoder/scc>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    atcoder::scc_graph g(n);
    for (int j = 0; j < m; j++) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }
    vector<int> id(n);
    // --8<-- [start:core]
    // 強連結成分の番号（トポロジカル順）を各頂点に書き込む
    for (const auto& [i, component] : g.scc() | views::enumerate) {
        for (int v : component) id[v] = i;
    }
    // --8<-- [end:core]
    for (int v = 0; v < n; v++) cout << id[v] << " \n"[v == n - 1];
}
