#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// 和が n で、ちょうど k 個の正の整数からなり、同じ値を m 個以下しか含まない多重集合の数を
// k = 1, ..., n について求める
int main() {
    int n, m;
    cin >> n >> m;

    // --8<-- [start:core]
    // dp[k][s] = k 個の正の整数で和が s、同じ値は M 個以下（入力の m）の多重集合の数
    vector<vector<mint>> dp(n + 1, vector<mint>(n + 1, 0));
    dp[0][0] = 1;
    for (int k = 1; k <= n; k++) {
        for (int s = k; s <= n; s++) {
            dp[k][s] = dp[k][s - k];          // 1 を含まない：全部から 1 を引く
            dp[k][s] += dp[k - 1][s - 1];     // 1 を含む：1 を 1 つ取り除く
            // 1 を M + 1 個含むものを引く（残りの k - m - 1 個は 2 以上なので、1 を引くと和は s - k）
            if (k - m - 1 >= 0) dp[k][s] -= dp[k - m - 1][s - k];
        }
    }
    // --8<-- [end:core]

    // 小さい n では全部の分割を作って確かめる
    if (n <= 30) {
        vector<long long> cnt(n + 1, 0);
        vector<int> parts;
        auto dfs = [&](auto&& self, int rest, int mx) -> void {
            if (rest == 0) {
                map<int, int> c;
                for (int x : parts) c[x]++;
                bool ok = true;
                for (auto [v, t] : c) ok &= (t <= m);
                if (ok) cnt[parts.size()]++;
                return;
            }
            for (int x = min(rest, mx); x >= 1; x--) {
                parts.push_back(x);
                self(self, rest - x, x);
                parts.pop_back();
            }
        };
        dfs(dfs, n, n);
        for (int k = 1; k <= n; k++) assert(mint(cnt[k]) == dp[k][n]);
    }
    for (int k = 1; k <= n; k++) cout << dp[k][n].val() << (k == n ? '\n' : ' ');
}
