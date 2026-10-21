#include <bits/stdc++.h>
using namespace std;

// 入力：N M と M 本の有向辺 u v w（0-indexed、w は負でもよい）
// 出力：負閉路があれば NEGATIVE CYCLE、なければ距離の表（届かない組は INF）
int main() {
    int n, m;
    cin >> n >> m;
    // --8<-- [start:core]
    const long long INF = 1LL << 60;
    vector<vector<long long>> d(n, vector<long long>(n, INF));
    for (int i = 0; i < n; i++) d[i][i] = 0;
    for (int e = 0; e < m; e++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        d[u][v] = min(d[u][v], w);  // 多重辺は最小値。負の自己ループは d[u][u] < 0 になる
    }
    for (int k = 0; k < n; k++) {          // k（経由してよい頂点）を一番外に置く
        for (int i = 0; i < n; i++) {
            if (d[i][k] == INF) continue;  // 届かない組は飛ばす（INF + 負の値を防ぐ）
            for (int j = 0; j < n; j++) {
                if (d[k][j] == INF) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    bool negative_cycle = false;
    for (int i = 0; i < n; i++) {
        if (d[i][i] < 0) negative_cycle = true;
    }
    // --8<-- [end:core]
    if (negative_cycle) {
        cout << "NEGATIVE CYCLE" << '\n';
        return 0;
    }
    for (int i = 0; i < n; i++) {
        assert(d[i][i] == 0);
        for (int j = 0; j < n; j++) {
            if (j > 0) cout << ' ';
            if (d[i][j] == INF) cout << "INF";
            else cout << d[i][j];
        }
        cout << '\n';
    }
}
