#include <bits/stdc++.h>
using namespace std;

const long long INF = 1LL << 60;  // INF + INF でもあふれない大きさ

void floyd_warshall(vector<vector<long long>>& d) {
    int n = d.size();
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (d[i][k] < INF && d[k][j] < INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

// --8<-- [start:core]
// 距離の表 d（辺の重みは非負）に、無向辺 a - b（長さ c）を足す。O(N^2)
void add_edge(vector<vector<long long>>& d, int a, int b, long long c) {
    int n = d.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // 新しい辺を a → b の向きに使う経路と、b → a の向きに使う経路
            if (d[i][a] < INF && d[b][j] < INF) d[i][j] = min(d[i][j], d[i][a] + c + d[b][j]);
            if (d[i][b] < INF && d[a][j] < INF) d[i][j] = min(d[i][j], d[i][b] + c + d[a][j]);
        }
    }
}
// --8<-- [end:core]

// 入力：N M、M 本の無向辺 u v w、Q、Q 本の追加する無向辺 a b c（0-indexed、重みは非負）
// 出力：辺を足すたびに、届く組 i < j の距離の総和
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> g(n, vector<long long>(n, INF));  // 辺だけの表
    for (int i = 0; i < n; i++) g[i][i] = 0;
    for (int e = 0; e < m; e++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u][v] = g[v][u] = min(g[u][v], w);
    }
    vector<vector<long long>> d = g;
    floyd_warshall(d);
    int q;
    cin >> q;
    for (int t = 0; t < q; t++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        add_edge(d, a, b, c);
        // 確かめ：最初から計算し直した表と一致する
        g[a][b] = g[b][a] = min(g[a][b], c);
        vector<vector<long long>> full = g;
        floyd_warshall(full);
        assert(d == full);
        long long sum = 0;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (d[i][j] < INF) sum += d[i][j];
        cout << sum << '\n';
    }
}
