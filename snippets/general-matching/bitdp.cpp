#include <bits/stdc++.h>
using namespace std;

// 頂点数 n（20 程度まで）の一般グラフの最大重みマッチング。
// w[i][j] は辺 i-j の重み（辺がなければ -1）。
// --8<-- [start:core]
long long max_weight_matching(int n, const vector<vector<long long>>& w) {
    // dp[S] = 集合 S の頂点の扱い（組むか、組まないか）を決め終えたときの重みの和の最大
    vector<long long> dp(1 << n, LLONG_MIN);  // まだ作れない印。足す前に飛ばすのでこの値でよい
    dp[0] = 0;
    for (int s = 0; s < (1 << n) - 1; s++) {
        if (dp[s] == LLONG_MIN) continue;
        int i = __builtin_ctz(~s);  // まだ決めていない最も小さい頂点
        int t = s | (1 << i);
        dp[t] = max(dp[t], dp[s]);  // i は組まない
        for (int j = i + 1; j < n; j++) {
            if ((s >> j & 1) || w[i][j] < 0) continue;
            int u = t | (1 << j);
            dp[u] = max(dp[u], dp[s] + w[i][j]);  // i と j を組む
        }
    }
    return dp[(1 << n) - 1];
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> w(n, vector<long long>(n, -1));
    for (int k = 0; k < m; k++) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        w[u][v] = w[v][u] = max(w[u][v], c);
    }
    long long ans = max_weight_matching(n, w);
    assert(ans >= 0);
    cout << ans << '\n';
}
