#include <bits/stdc++.h>
using namespace std;

// 無向グラフで、ちょうど K 頂点を通る単純パス（同じ頂点を 2 度通らない）の頂点の重みの和の最大値。なければ -1
// --8<-- [start:core]
mt19937_64 rng(random_device{}());

long long colorful_path(int n, int k, const vector<long long>& w, const vector<vector<int>>& g, int trials) {
    const long long NEG = LLONG_MIN / 4;
    uniform_int_distribution<int> color_of(0, k - 1);
    long long best = -1;
    vector<int> col(n);
    for (int t = 0; t < trials; t++) {
        for (int v = 0; v < n; v++) col[v] = color_of(rng);   // 頂点に K 色をランダムに塗る
        // dp[S][v]：使った色の集合が S で v で終わる、色がすべて異なるパスの重みの最大
        vector<vector<long long>> dp(1 << k, vector<long long>(n, NEG));
        for (int v = 0; v < n; v++) dp[1 << col[v]][v] = w[v];
        for (int S = 1; S < (1 << k); S++)
            for (int v = 0; v < n; v++) {
                if (dp[S][v] == NEG) continue;
                for (int u : g[v]) {
                    if (S >> col[u] & 1) continue;               // 同じ色は使わない → 同じ頂点も使わない
                    int T = S | 1 << col[u];
                    dp[T][u] = max(dp[T][u], dp[S][v] + w[u]);
                }
            }
        for (int v = 0; v < n; v++)
            if (dp[(1 << k) - 1][v] != NEG) best = max(best, dp[(1 << k) - 1][v]);
    }
    return best;
}
// --8<-- [end:core]

// 確かめ用：すべての単純パスを DFS で調べる
long long brute(int n, int k, const vector<long long>& w, const vector<vector<int>>& g) {
    long long best = -1;
    vector<bool> used(n, false);
    auto dfs = [&](auto&& self, int v, int len, long long sum) -> void {
        if (len == k) {
            best = max(best, sum);
            return;
        }
        for (int u : g[v])
            if (!used[u]) {
                used[u] = true;
                self(self, u, len + 1, sum + w[u]);
                used[u] = false;
            }
    };
    for (int v = 0; v < n; v++) {
        used[v] = true;
        dfs(dfs, v, 1, w[v]);
        used[v] = false;
    }
    return best;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<long long> w(n);
    for (auto& x : w) cin >> x;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    // 1 回の成功確率は K!/K^K 以上（K = 4 で 3/32）。失敗確率を 10^-9 以下にする回数
    double p = 1.0;
    for (int i = 1; i <= k; i++) p *= (double)i / k;
    int trials = (int)ceil(log(1e-9) / log(1 - p)) + 1;
    if (k == 1) trials = 1;
    long long ans = colorful_path(n, k, w, g, trials);
    assert(ans == brute(n, k, w, g));
    cout << ans << '\n';
}
