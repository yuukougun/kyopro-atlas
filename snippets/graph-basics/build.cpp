// 重み付き無向グラフを、隣接リスト・辺リスト・隣接行列の 3 通りで持つ。
// 入力：N M のあと、M 行に u v w（1-indexed の頂点番号と重み）。多重辺・自己ループを含んでよい。
// 出力：1 行目に各頂点の次数、続く N 行に隣接行列（同じ組の辺は重みの最小、辺がなければ -1、対角は 0）。
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // --8<-- [start:core]
    vector<vector<pair<int, long long>>> g(n);  // g[u] = {(行き先, 重み), …}
    vector<tuple<int, int, long long>> edges;   // 辺リスト：(u, v, 重み)
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--, v--;  // 1-indexed → 0-indexed は読んだ直後に 1 回だけ
        g[u].push_back({v, w});
        g[v].push_back({u, w});  // 無向なので逆向きも足す
        edges.push_back({u, v, w});
    }
    // --8<-- [end:core]

    // --8<-- [start:matrix]
    const long long INF = 1LL << 60;  // INF + INF でもあふれない大きさ
    vector<vector<long long>> d(n, vector<long long>(n, INF));
    for (int v = 0; v < n; v++) d[v][v] = 0;
    for (auto [u, v, w] : edges) {
        d[u][v] = min(d[u][v], w);  // 多重辺は代入でなく最小を取る
        d[v][u] = min(d[v][u], w);
    }
    // --8<-- [end:matrix]

    // 握手補題：次数の和は 2M（自己ループは 2 回数える）
    long long degsum = 0;
    for (int v = 0; v < n; v++) degsum += (long long)g[v].size();
    assert(degsum == 2LL * m);

    for (int v = 0; v < n; v++) cout << g[v].size() << (v + 1 < n ? ' ' : '\n');
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (d[i][j] == INF ? -1 : d[i][j]) << (j + 1 < n ? ' ' : '\n');
        }
    }
}
