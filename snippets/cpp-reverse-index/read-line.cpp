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
    for (const auto& [i, component] : scc.scc() | views::enumerate) {
        // i は添字（ptrdiff_t）、component は成分への参照（const は付かない）
        static_assert(is_same_v<decltype(i), const ptrdiff_t>);
        static_assert(is_same_v<decltype(component), vector<int>&>);
        cout << i << ":";
        for (int v : component) cout << ' ' << v;
        cout << '\n';
    }
    // --8<-- [end:core]
}
