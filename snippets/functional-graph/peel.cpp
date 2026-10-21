#include <bits/stdc++.h>
using namespace std;

// 頂点 0..n-1、辺 v → a[v]（各頂点から 1 本）。
// 入次数 0 の頂点から剥がして閉路上の頂点を求め、各頂点について
// 閉路までの距離 dist[v] と、v から到達できる頂点の数 dist[v] + (閉路の長さ) を求める。
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    // --8<-- [start:core]
    vector<int> indeg(n, 0);
    for (int v = 0; v < n; v++) indeg[a[v]]++;
    vector<int> removed;                    // 剥がした順（v は a[v] より先に来る）
    for (int v = 0; v < n; v++) if (indeg[v] == 0) removed.push_back(v);
    for (size_t i = 0; i < removed.size(); i++) {
        int w = a[removed[i]];
        if (--indeg[w] == 0) removed.push_back(w);
    }
    vector<bool> on_cycle(n, true);         // 剥がされずに残った頂点がちょうど閉路上
    for (int v : removed) on_cycle[v] = false;

    vector<int> len(n, 0), dist(n, 0);      // len[v] = v が最後に入る閉路の長さ
    for (int s = 0; s < n; s++) {
        if (!on_cycle[s] || len[s] > 0) continue;
        vector<int> cyc;                    // s を含む閉路を 1 周たどる
        int v = s;
        do { cyc.push_back(v); v = a[v]; } while (v != s);
        for (int u : cyc) len[u] = cyc.size();
    }
    for (int i = (int)removed.size() - 1; i >= 0; i--) {  // 閉路に近い頂点から
        int v = removed[i];
        dist[v] = dist[a[v]] + 1;
        len[v] = len[a[v]];
    }
    long long total = 0;                    // 到達できる組 (u, v) の数。最大 N^2
    for (int v = 0; v < n; v++) total += dist[v] + len[v];
    // --8<-- [end:core]

    for (int v = 0; v < n; v++) {
        assert(dist[v] + len[v] <= n);
        assert(on_cycle[v] == (dist[v] == 0));
    }
    for (int v = 0; v < n; v++) cout << (on_cycle[v] ? '1' : '0');
    cout << '\n';
    for (int v = 0; v < n; v++) cout << dist[v] << (v + 1 < n ? ' ' : '\n');
    cout << total << '\n';
}
