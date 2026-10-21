// 根を動かした差分：各頂点からほかの全頂点への距離の総和
// 入力：N、続く N - 1 行に辺 u v（1-indexed）。出力：頂点 1, …, N の値
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
    vector<int> par(n, -1), order = {0}, dep(n, 0);
    for (int i = 0; i < (int)order.size(); i++) {
        int v = order[i];
        for (int c : g[v]) {
            if (c == par[v]) continue;
            par[c] = v;
            dep[c] = dep[v] + 1;
            order.push_back(c);
        }
    }
    // --8<-- [start:core]
    // 1 回目（下から上）：部分木のサイズ。根 0 での値は深さの和
    vector<long long> sz(n, 1), f(n, 0);
    for (int i = n - 1; i >= 1; i--) sz[par[order[i]]] += sz[order[i]];
    for (int v = 0; v < n; v++) f[0] += dep[v];
    // 2 回目（上から下）：根を親 p から子 c へ移すと、
    // c の部分木の sz[c] 頂点は 1 近づき、残りの n - sz[c] 頂点は 1 遠ざかる
    for (int i = 1; i < n; i++) {
        int c = order[i];
        f[c] = f[par[c]] + (n - sz[c]) - sz[c];
    }
    // --8<-- [end:core]
    // 素朴に各頂点から BFS して確かめる
    if (n <= 2000) {
        for (int s = 0; s < n; s++) {
            vector<int> dist(n, -1);
            queue<int> q;
            dist[s] = 0;
            q.push(s);
            long long sum = 0;
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                sum += dist[v];
                for (int c : g[v])
                    if (dist[c] < 0) dist[c] = dist[v] + 1, q.push(c);
            }
            assert(sum == f[s]);
        }
    }
    for (int v = 0; v < n; v++) cout << f[v] << '\n';
}
