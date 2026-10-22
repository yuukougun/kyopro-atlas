#include <bits/stdc++.h>
#include <atcoder/scc>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    atcoder::scc_graph scc(n);
    for (int j = 0; j < m; j++) {
        int u, v;
        cin >> u >> v;
        scc.add_edge(u, v);
    }
    // --8<-- [start:core]
    for (auto& [i, component] : scc.scc() | views::enumerate) {
        cout << i << ":";
        for (int v : component) cout << ' ' << v;
        cout << '\n';
    }
    // --8<-- [end:core]
}
