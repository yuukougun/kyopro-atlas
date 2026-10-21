// ±1 の歩みを n 歩、高さ s から始めて高さ t で終え、途中ずっと 0 ≤ 高さ ≤ w を守る列の数（法 998244353）。
// 下の線 −1 と上の線 w + 1 での折り返しを繰り返した像を、符号を交互にして足し引きする。
// 項の数は O(n / w + 1)。小さい入力では高さの DP と比べる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

vector<mint> fact, ifact;

void init_binom(int n_max) {
    fact.assign(n_max + 1, 1);
    ifact.assign(n_max + 1, 1);
    for (int i = 1; i <= n_max; i++) fact[i] = fact[i - 1] * i;
    ifact[n_max] = fact[n_max].inv();
    for (int i = n_max; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
}

mint binom(long long n, long long k) {
    if (n < 0 || k < 0 || k > n) return 0;  // 範囲外は 0
    assert(n < (long long)fact.size());
    return fact[n] * ifact[k] * ifact[n - k];
}

// --8<-- [start:core]
// 制約のない ±1 の n 歩で、高さが d だけ変わる列の数（+1 を (n + d) / 2 回）
mint walks(long long n, long long d) {
    if (d < -n || d > n || (n + d) % 2 != 0) return 0;
    return binom(n, (n + d) / 2);
}

// 0 ≤ 高さ ≤ w を守って s から t へ行く n 歩の列の数
mint count_between(long long n, long long s, long long t, long long w) {
    if (s < 0 || s > w || t < 0 || t > w) return 0;
    long long period = 2 * (w + 2);  // 線 −1 と線 w + 1 で 1 回ずつ折り返すと、2(w + 2) の平行移動になる
    long long lim = n / period + 2;
    mint res = 0;
    for (long long j = -lim; j <= lim; j++) {
        res += walks(n, t + j * period - s);       // 偶数回折り返した像
        res -= walks(n, -2 - t + j * period - s);  // 奇数回折り返した像（線 −1 で t を折り返した点 −2 − t から）
    }
    return res;
}
// --8<-- [end:core]

// 高さの DP で数える（確かめ用）
long long brute(int n, int s, int t, int w) {
    if (s < 0 || s > w || t < 0 || t > w) return 0;
    vector<long long> dp(w + 1, 0);
    dp[s] = 1;
    for (int i = 0; i < n; i++) {
        vector<long long> ndp(w + 1, 0);
        for (int h = 0; h <= w; h++) {
            if (h > 0) ndp[h - 1] += dp[h];
            if (h < w) ndp[h + 1] += dp[h];
        }
        dp = ndp;
    }
    return dp[t];
}

int main() {
    init_binom(2000000);
    for (int w = 0; w <= 6; w++) {
        for (int n = 0; n <= 30; n++) {
            for (int s = 0; s <= w; s++) {
                for (int t = 0; t <= w; t++) {
                    assert(count_between(n, s, t, w).val() == brute(n, s, t, w) % 998244353);
                }
            }
        }
    }
    long long n, s, t, w;
    cin >> n >> s >> t >> w;
    cout << count_between(n, s, t, w).val() << '\n';
}
