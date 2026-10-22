#include <bits/stdc++.h>
using namespace std;

int main() {
    // --8<-- [start:core]
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);           // 頂点は 0-indexed で 0, 1, ..., n - 1
    for (int i = 0; i < m; i++) {       // ループは半開区間 [0, m)
        int u, v;
        cin >> u >> v;
        u--, v--;                       // 問題文の 1-indexed を読み込んだ直後に直す
        g[u].push_back(v);
        g[v].push_back(u);
    }
    long long total = 0;                // 和は long long で持つ
    for (int v = 0; v < n; v++) {
        cout << g[v].size() << (v + 1 < n ? ' ' : '\n');
        total += (long long)g[v].size();
    }
    assert(total == 2LL * m);           // 次数の和は辺の数の 2 倍
    cout << total << '\n';
    // --8<-- [end:core]
}
