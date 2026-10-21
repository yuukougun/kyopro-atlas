// 辺の列を順に 1 本ずつ緩和する（配列を 1 本だけ持つ）
// 入力：N M K、続く M 行に辺「a b c」（a から b へ長さ c の有向辺。頂点は 1-indexed）、
//       続く 1 行に辺の番号の列 E_1 … E_K（1-indexed）
// 出力：E の部分列の順に辺をたどって頂点 1 から頂点 N へ行く長さの最小（行けなければ -1）
#include <bits/stdc++.h>
using namespace std;

const long long INF = 1LL << 60;

// 2 次元の表 dp[k][v] をそのまま作る素朴な方法（確かめ用。O(NK)）
long long naive(int n, const vector<int>& a, const vector<int>& b, const vector<long long>& c, const vector<int>& e) {
    int k = e.size();
    vector<vector<long long>> dp(k + 1, vector<long long>(n, INF));
    dp[0][0] = 0;
    for (int i = 0; i < k; i++) {
        dp[i + 1] = dp[i];  // 辺 E_i を使わない：前の行をそのまま写す
        int j = e[i];
        if (dp[i][a[j]] < INF) dp[i + 1][b[j]] = min(dp[i + 1][b[j]], dp[i][a[j]] + c[j]);
    }
    return dp[k][n - 1];
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(m), b(m);
    vector<long long> c(m);
    for (int j = 0; j < m; j++) {
        cin >> a[j] >> b[j] >> c[j];
        a[j]--, b[j]--;
    }
    vector<int> e(k);
    for (int i = 0; i < k; i++) {
        cin >> e[i];
        e[i]--;
    }
    // --8<-- [start:core]
    vector<long long> dist(n, INF);  // dist[v] = 今までの辺だけを使って v へ行く長さの最小
    dist[0] = 0;
    for (int i = 0; i < k; i++) {
        int j = e[i];  // この行で変わりうるのは dist[b[j]] の 1 か所だけ
        if (dist[a[j]] < INF) dist[b[j]] = min(dist[b[j]], dist[a[j]] + c[j]);
    }
    // --8<-- [end:core]
    assert(dist[n - 1] == naive(n, a, b, c, e));
    cout << (dist[n - 1] == INF ? -1 : dist[n - 1]) << '\n';
}
