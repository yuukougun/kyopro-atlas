// (0, 0) から (a, b) への右・上の最短路のうち、どの時点でも「上の回数 ≤ 右の回数 + K」を守るものの数（法 998244353）。
// 全体から、線 y = x + K + 1 に触れる経路（鏡像法で終点 (b − K − 1, a + K + 1) への経路と 1 対 1）を引く。
// カタラン数は a = b = n、K = 0 の場合。小さい入力では格子の DP と比べる。
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

mint binom(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;  // 範囲外は 0
    assert(n < (int)fact.size());
    return fact[n] * ifact[k] * ifact[n - k];
}

// --8<-- [start:core]
// 右 a 回・上 b 回の並べ方のうち、どの接頭辞でも (上の回数) ≤ (右の回数) + k を守るものの数
mint count_below(int a, int b, int k) {
    if (k < 0) return 0;          // 出発点 (0, 0) がすでに条件を破っている
    if (b > a + k) return 0;      // 終点が線の上にあり、守る経路は 1 本もない
    // 全体 − 線 y = x + k + 1 に触れる経路（終点を折り返した (b − k − 1, a + k + 1) への経路の数）
    return binom(a + b, a) - binom(a + b, a + k + 1);
}

// 長さ 2n の正しい括弧列の数（カタラン数）
mint catalan(int n) {
    return binom(2 * n, n) - binom(2 * n, n + 1);
}
// --8<-- [end:core]

// 格子の DP で数える（確かめ用）
long long brute(int a, int b, int k) {
    vector<vector<long long>> dp(a + 1, vector<long long>(b + 1, 0));
    for (int x = 0; x <= a; x++) {
        for (int y = 0; y <= b; y++) {
            if (y > x + k) continue;  // 線より上の点は通れない
            if (x == 0 && y == 0) {
                dp[x][y] = 1;
                continue;
            }
            if (x > 0) dp[x][y] += dp[x - 1][y];
            if (y > 0) dp[x][y] += dp[x][y - 1];
        }
    }
    return dp[a][b];
}

int main() {
    init_binom(4000000);
    // 小さい範囲をすべて DP と比べる
    for (int a = 0; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            for (int k = -1; k <= 4; k++) {
                long long expected = (k < 0) ? 0 : brute(a, b, k);
                assert(count_below(a, b, k).val() == expected % 998244353);
            }
        }
    }
    // カタラン数 1, 1, 2, 5, 14, 42, 132 と、C(2n, n) / (n + 1) との一致
    const int cat[] = {1, 1, 2, 5, 14, 42, 132};
    for (int n = 0; n <= 6; n++) assert(catalan(n).val() == cat[n]);
    for (int n = 0; n <= 1000; n++) assert(catalan(n) == binom(2 * n, n) / mint(n + 1));

    int a, b, k;
    cin >> a >> b >> k;
    cout << count_below(a, b, k).val() << '\n';
}
