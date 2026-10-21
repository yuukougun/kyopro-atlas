#include <bits/stdc++.h>
using namespace std;

// 木と指定頂点 v（0-indexed、1 個以上）から、指定頂点をすべて含む最小の部分木の頂点数を返す
int steiner_size(int n, const vector<vector<int>>& g, const vector<int>& v) {
    // --8<-- [start:core]
    vector<bool> is_term(n, false);
    for (int x : v) is_term[x] = true;
    vector<bool> keep(n, false);  // keep[u]：u の部分木に指定頂点があるか
    // 帰りがけに、自分か子のどれかが keep なら自分も keep にする
    auto dfs = [&](auto&& self, int u, int p) -> void {
        keep[u] = is_term[u];
        for (int w : g[u]) {
            if (w == p) continue;
            self(self, w, u);
            if (keep[w]) keep[u] = true;
        }
    };
    dfs(dfs, v[0], -1);  // 根は指定頂点にする
    int cnt = 0;
    for (int u = 0; u < n; u++) if (keep[u]) cnt++;
    return cnt;  // 辺の数は cnt - 1
    // --8<-- [end:core]
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> v(k);
    for (int& x : v) {
        cin >> x;
        x--;
    }
    int ans = steiner_size(n, g, v);
    assert(1 <= ans && ans <= n);
    cout << ans << '\n';
}
