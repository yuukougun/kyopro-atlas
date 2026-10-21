// 重み付きの木で、1 点 s から全頂点への距離を求める（ダイクストラ法を使わない）
// 入力：N s、続く N - 1 行に辺 u v w（1-indexed、w は負でもよい）
// 出力：各頂点の s からの距離
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// g[v] は (隣の頂点, 辺の重み) の列。s からの距離を返す
vector<long long> dist_from(int s, const vector<vector<pair<int, long long>>>& g) {
    int n = g.size();
    vector<long long> dist(n, 0);
    vector<pair<int, int>> st = {{s, -1}};  // (頂点, 親)。取り出す順は DFS でも BFS でもよい
    while (!st.empty()) {
        auto [v, p] = st.back();
        st.pop_back();
        for (auto [c, w] : g[v]) {
            if (c == p) continue;     // 親へ戻らなければ、各頂点を 1 回ずつ訪れる
            dist[c] = dist[v] + w;    // パスが 1 本なので、この値で確定する
            st.push_back({c, v});
        }
    }
    return dist;
}
// --8<-- [end:core]

int main() {
    int n, s;
    cin >> n >> s;
    s--;
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    vector<long long> dist = dist_from(s, g);
    assert(dist[s] == 0);
    for (int v = 0; v < n; v++) cout << dist[v] << (v + 1 < n ? ' ' : '\n');
}
