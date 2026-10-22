#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    // 0 - 1 - 2 - ... - (n-1) の一直線の木
    vector<vector<int>> g(n);
    for (int i = 0; i + 1 < n; i++) {
        g[i].push_back(i + 1);
        g[i + 1].push_back(i);
    }
    vector<int> dep(n);
    // --8<-- [start:core]
    auto dfs = [&](auto&& self, int v, int p) -> void {
        for (int u : g[v]) {
            if (u == p) continue;
            dep[u] = dep[v] + 1;
            self(self, u, v);  // 頂点 0 から呼ぶと、深さは n 段になる
        }
    };
    dfs(dfs, 0, -1);
    // --8<-- [end:core]
    cout << dep[n - 1] << '\n';
}
