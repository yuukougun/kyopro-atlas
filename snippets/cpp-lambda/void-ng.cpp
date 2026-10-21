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
    auto dfs = [&](auto&& self, int v, int p) {  // -> void がない
        sz[v] = 1;
        for (int to : g[v]) {
            if (to == p) continue;
            self(self, to, v);  // 受け取った自分自身を呼ぶ。呼ぶときも自分を渡す
            sz[v] += sz[to];
        }
    };
    dfs(dfs, 0, -1);  // 最初の呼び出しで自分を渡す
    // --8<-- [end:core]
    for (int v = 0; v < n; v++) cout << sz[v] << " \n"[v == n - 1];
}
