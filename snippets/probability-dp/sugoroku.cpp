// マス 0〜N のすごろく。1〜M の目が等確率のサイコロを最大 K 回振り、N を超えたら超えた分だけ戻る。
// マス N に着いたら終わる。K 回以内にマス N に着く確率を mod 998244353 で求める（M ≤ N とする）。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// dp[x] = t 回振った後にマス x にいる確率。ゴールに着いたらそこにとどまる（吸収）
mint reach_goal(int n, int m, int k) {
    assert(1 <= m && m <= n);
    mint inv_m = mint(m).inv();
    vector<mint> dp(n + 1, 0);
    dp[0] = 1;
    for (int t = 0; t < k; t++) {
        vector<mint> nxt(n + 1, 0);
        nxt[n] += dp[n];  // ゴールからは確率 1 でゴールへ
        for (int x = 0; x < n; x++) {
            for (int a = 1; a <= m; a++) {
                int y = x + a;
                if (y > n) y = n - (y - n);  // 超えた分だけ戻る
                nxt[y] += dp[x] * inv_m;
            }
        }
        dp = move(nxt);
        mint total = 0;
        for (mint v : dp) total += v;
        assert(total == 1);  // 検算：mod の値でも和は 1 になる
    }
    return dp[n];  // 「K 回以内に着く」＝「K 回後にゴールにいる」
}
// --8<-- [end:core]

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    cout << reach_goal(n, m, k).val() << '\n';
}
