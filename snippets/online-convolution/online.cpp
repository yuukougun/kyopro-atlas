#include <bits/stdc++.h>
#include <atcoder/convolution>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// dp[0] = 1、dp[i] = Σ_{j=0}^{i-1} dp[j] g[i-j]（1 ≤ i ≤ n）を求める。g は先にすべて分かっている。
// O(n log^2 n)
vector<mint> online_convolution(int n, const vector<mint>& g) {
    vector<mint> dp(n + 1);  // 確定前は「ここまでに届いた寄与の和」を持つ
    dp[0] = 1;
    // 呼ばれた時点で、[0, l) から [l, r) への寄与はすべて足されている
    auto solve = [&](auto&& self, int l, int r) -> void {
        if (r - l == 1) {
            // ここで dp[l] が確定する。遷移に式があるなら dp[l] をここで変換する
            return;
        }
        int m = (l + r) / 2;
        self(self, l, m);  // 左半分を確定させる
        // 左半分 [l, m) から右半分 [m, r) への寄与：dp[j] * g[k - j]（1 ≤ k − j < r − l）
        vector<mint> left(dp.begin() + l, dp.begin() + m);
        vector<mint> gg(g.begin(), g.begin() + (r - l));
        vector<mint> c = atcoder::convolution(left, gg);
        for (int k = m; k < r; k++) dp[k] += c[k - l];
        self(self, m, r);  // 右半分は、左からの寄与がそろった状態で解く
    };
    solve(solve, 0, n + 1);
    return dp;
}
// --8<-- [end:core]

// 貰う DP をそのまま書く。O(n^2)
vector<mint> naive(int n, const vector<mint>& g) {
    vector<mint> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) dp[i] += dp[j] * g[i - j];
    }
    return dp;
}

int main() {
    mt19937 rng(1);
    for (int n = 0; n <= 300; n++) {
        vector<mint> g(n + 1);
        for (int i = 1; i <= n; i++) g[i] = rng();
        assert(online_convolution(n, g) == naive(n, g));
    }

    int n;
    cin >> n;
    vector<mint> g(n + 1);  // g[0] は使わない
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        g[i] = x;
    }
    auto dp = online_convolution(n, g);
    for (int i = 0; i <= n; i++) cout << dp[i].val() << (i == n ? '\n' : ' ');
}
