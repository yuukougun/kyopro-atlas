#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// 位置 i（0-indexed）から i + A_i, i + 2A_i, … へ dp[i] を配る DP。dp[0] = 1。
// 歩幅 A_i が B 以上なら愚直に配り、B 未満なら（歩幅, 余り）の表に予約する。
// --8<-- [start:core]
vector<mint> step_dp(const vector<int>& A) {
    int n = A.size();
    int B = max(1, (int)sqrt((double)n));
    vector<mint> dp(n, 0);
    dp[0] = 1;
    // pend[k][r]：歩幅 k・余り r の位置へ配る予約の合計（k < B）
    vector<vector<mint>> pend(B);
    for (int k = 1; k < B; k++) pend[k].assign(k, 0);
    for (int i = 0; i < n; i++) {
        for (int k = 1; k < B; k++) dp[i] += pend[k][i % k];   // 貰う：O(B)
        if (A[i] >= B) {
            for (int j = i + A[i]; j < n; j += A[i]) dp[j] += dp[i];   // 配る：n / B 回以下
        } else {
            pend[A[i]][i % A[i]] += dp[i];   // 予約：O(1)
        }
    }
    return dp;
}
// --8<-- [end:core]

vector<mint> naive(const vector<int>& A) {
    int n = A.size();
    vector<mint> dp(n, 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++)
        for (int j = i + A[i]; j < n; j += A[i]) dp[j] += dp[i];
    return dp;
}

void self_test() {
    mt19937 rng(335);
    for (int iter = 0; iter < 300; iter++) {
        int n = rng() % 40 + 1;
        vector<int> A(n);
        for (auto& v : A) v = rng() % (iter % 2 ? 3 : n) + 1;
        auto x = step_dp(A), y = naive(A);
        for (int i = 0; i < n; i++) assert(x[i] == y[i]);
    }
}

int main() {
    self_test();
    int n;
    cin >> n;
    vector<int> A(n);
    for (auto& v : A) cin >> v;
    auto dp = step_dp(A);
    for (int i = 0; i < n; i++) cout << dp[i].val() << (i + 1 < n ? ' ' : '\n');
}
