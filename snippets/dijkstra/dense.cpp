// 密グラフ（隣接行列）での O(N^2) のダイクストラ法。頂点 1 から各頂点への最短距離を求める。
// 入力：N、続いて N 行 N 列の行列 c（c[i][j] は i から j への辺の重み。辺がなければ -1）。
// 出力：各頂点の最短距離（届かなければ -1）。
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1LL << 60;  // INF + INF でもあふれない大きさ

// --8<-- [start:core]
// c[u][v] は u から v への重み（辺がなければ INF）。ヒープを使わず、未確定の最小を毎回探す
vector<long long> dijkstra_dense(const vector<vector<long long>>& c, int s) {
    int n = c.size();
    vector<long long> dist(n, INF);
    vector<bool> done(n, false);
    dist[s] = 0;
    for (int iter = 0; iter < n; iter++) {
        int v = -1;
        for (int u = 0; u < n; u++) {
            if (!done[u] && (v == -1 || dist[u] < dist[v])) v = u;
        }
        if (dist[v] == INF) break;  // 残りはどれも届かない
        done[v] = true;             // dist[v] が確定する
        for (int to = 0; to < n; to++) {
            if (c[v][to] != INF) dist[to] = min(dist[to], dist[v] + c[v][to]);
        }
    }
    return dist;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<vector<long long>> c(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c[i][j];
            assert(c[i][j] >= -1);
            if (c[i][j] == -1) c[i][j] = INF;
        }
    }
    vector<long long> dist = dijkstra_dense(c, 0);
    for (int v = 0; v < n; v++) {
        cout << (dist[v] == INF ? -1 : dist[v]) << (v + 1 < n ? ' ' : '\n');
    }
}
