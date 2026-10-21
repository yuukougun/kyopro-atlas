#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> sz(n);  // sz[v]：頂点 0 を根とした v の部分木の頂点数
    // --8<-- [start:core]
    function<void(int, int)> dfs = [&](int v, int p) {
        sz[v] = 1;
        for (int to : g[v]) {
            if (to == p) continue;
            dfs(to, v);  // 自分の名前で呼べる（dfs の型は function と先に決まっている）
            sz[v] += sz[to];
        }
    };
    dfs(0, -1);
    // --8<-- [end:core]
    for (int v = 0; v < n; v++) cout << sz[v] << " \n"[v == n - 1];
}
