// 辺で切って数える：N 頂点の木で、すべての頂点の組 {u, v}（u < v）の距離の総和を求める。
// 頂点 1 を根にして部分木サイズ sz を求め、親子の辺ごとに sz[c] × (N − sz[c]) を足す。
// 入力：N、続く N - 1 行に辺 u v（1-indexed）
#include <bits/stdc++.h>
using namespace std;

// 確かめ用：各頂点から BFS して距離を全部足す（O(N^2)）
long long brute(int n, const vector<vector<int>>& g) {
    long long total = 0;
    for (int s = 0; s < n; s++) {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int c : g[v]) {
                if (dist[c] == -1) {
                    dist[c] = dist[v] + 1;
                    q.push(c);
                }
            }
        }
        for (int t = s + 1; t < n; t++) total += dist[t];
    }
    return total;
}

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
    // --8<-- [start:core]
    // 根から BFS した順 order を作り、逆から読んで部分木サイズを求める（再帰を使わない）
    vector<int> par(n, -1), order = {0};
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int c : g[v]) {
            if (c == par[v]) continue;
            par[c] = v;
            order.push_back(c);
        }
    }
    vector<long long> sz(n, 1);
    long long ans = 0;
    for (int i = n - 1; i >= 1; i--) {  // 子は親より先に確定する
        int c = order[i];
        ans += sz[c] * (n - sz[c]);  // 辺 (par[c], c) を通る組の数。long long で掛ける
        sz[par[c]] += sz[c];
    }
    // --8<-- [end:core]
    if (n <= 2000) assert(ans == brute(n, g));
    cout << ans << '\n';
}
