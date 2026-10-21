#include <bits/stdc++.h>
using namespace std;

// 指定されていない葉を削り続け、残った頂点の数を返す（v は 0-indexed、1 個以上）
int steiner_size_prune(int n, const vector<vector<int>>& g, const vector<int>& v) {
    // --8<-- [start:core]
    vector<bool> is_term(n, false);
    for (int x : v) is_term[x] = true;
    vector<int> deg(n);
    queue<int> q;
    for (int u = 0; u < n; u++) {
        deg[u] = g[u].size();
        if (deg[u] == 1 && !is_term[u]) q.push(u);  // 指定されていない葉
    }
    vector<bool> removed(n, false);
    int cnt = n;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        removed[u] = true;
        cnt--;
        for (int w : g[u]) {
            if (removed[w]) continue;
            deg[w]--;
            if (deg[w] == 1 && !is_term[w]) q.push(w);  // 新しく葉になった
        }
    }
    return cnt;
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
    int ans = steiner_size_prune(n, g, v);
    assert(1 <= ans && ans <= n);
    cout << ans << '\n';
}
