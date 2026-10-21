#include <bits/stdc++.h>
using namespace std;

// 検算用：要素ごとに K 個のどのグループに入れるかを全列挙する
long long brute(int n, int k, const vector<long long>& w) {
    long long best = LLONG_MAX;
    vector<int> g(n);
    auto dfs = [&](auto&& self, int i) -> void {
        if (i == n) {
            vector<long long> sum(k, 0);
            for (int x = 0; x < n; x++) sum[g[x]] += w[x];
            if (*min_element(sum.begin(), sum.end()) == 0) return;  // 空のグループ（w は正）
            best = min(best, *max_element(sum.begin(), sum.end()));
            return;
        }
        for (int c = 0; c < k; c++) {
            g[i] = c;
            self(self, i + 1);
        }
    };
    dfs(dfs, 0);
    return best;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> w(n);
    for (auto& x : w) cin >> x;
    int full = (1 << n) - 1;
    vector<long long> sum(1 << n, 0);
    for (int s = 1; s <= full; s++) sum[s] = sum[s & (s - 1)] + w[__builtin_ctz(s)];

    // --8<-- [start:core]
    // dp[j][s] ＝ 集合 s をちょうど j 個の空でないグループに分けたときの、グループの重さの和の最大の最小
    const long long INF = LLONG_MAX;  // 分けられない
    vector<vector<long long>> dp(k + 1, vector<long long>(1 << n, INF));
    dp[0][0] = 0;
    for (int j = 1; j <= k; j++) {
        for (int s = 1; s <= full; s++) {
            int low = s & -s, rest = s ^ low;
            for (int t = rest;; t = (t - 1) & rest) {
                int g = t | low;
                if (dp[j - 1][s ^ g] != INF)
                    dp[j][s] = min(dp[j][s], max(sum[g], dp[j - 1][s ^ g]));
                if (t == 0) break;
            }
        }
    }
    // --8<-- [end:core]
    long long ans = dp[k][full];
    if (n <= 8) assert(ans == brute(n, k, w));
    if (ans == INF) cout << -1 << '\n';
    else cout << ans << '\n';
}
