// 無向グラフで、頂点 s から t への最短距離（辺の本数）と最短経路を 1 つ求める。
// 入力は 1-indexed（N M s t と M 本の辺）。届かなければ -1 を出力する。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--, t--;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
        g[b].push_back(a);  // 無向なので両向きに張る
    }

    // --8<-- [start:core]
    vector<int> dist(n, -1);  // -1 ＝ まだ見つけていない（訪問済みの印を兼ねる）
    vector<int> par(n, -1);   // par[v] ＝ v を見つけたときに取り出していた頂点
    queue<int> que;
    dist[s] = 0;
    que.push(s);
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int v : g[u]) {
            if (dist[v] != -1) continue;  // 印は push のときに付けてあるので、2 回入らない
            dist[v] = dist[u] + 1;
            par[v] = u;
            que.push(v);
        }
    }

    // 経路復元：t から親をたどって s まで戻り、最後に反転する
    vector<int> path;
    if (dist[t] != -1) {
        for (int v = t; v != -1; v = par[v]) path.push_back(v);
        reverse(path.begin(), path.end());
    }
    // --8<-- [end:core]

    cout << dist[t] << '\n';
    if (dist[t] != -1) {
        assert((int)path.size() == dist[t] + 1 && path[0] == s && path.back() == t);
        for (int i = 0; i < (int)path.size(); i++) cout << path[i] + 1 << (i + 1 < (int)path.size() ? ' ' : '\n');
    }
}
