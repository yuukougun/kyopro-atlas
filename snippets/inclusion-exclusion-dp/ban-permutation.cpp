// 1, …, N の順列 P（0-indexed で値も 0..N-1）のうち、すべての i で |P_i − i| ≥ X となるものの数を
// 998244353 で割った余り（1 ≤ X）。N が小さいときは全探索で検算する。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n, x;
    cin >> n >> x;
    assert(n >= 0 && x >= 1);
    vector<mint> fact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;

    // --8<-- [start:core]
    // 違反のマス：行 i（位置）・列 c（値）で |c − i| < X。行 i で違反になる列は
    // 窓 [i − X + 1, i + X − 1] の 2X − 1 個で、ビット b が列 i − X + 1 + b を表す
    int wid = 2 * x - 1;
    // dp[j][mask] = ここまでの行で、列が重ならない違反のマスを j 個選んだ選び方の数
    //（mask は今の窓のうち使った列）
    vector dp(n + 1, vector<mint>(1 << wid));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        vector ndp(n + 1, vector<mint>(1 << wid));
        for (int j = 0; j <= i; j++) {
            for (int mask = 0; mask < (1 << wid); mask++) {
                if (dp[j][mask] == 0) continue;
                int sh = mask >> 1;  // 窓を 1 つ右へずらす（列 i − X は以後の行で違反にならない）
                ndp[j][sh] += dp[j][mask];  // 行 i には違反のマスを選ばない
                for (int b = 0; b < wid; b++) {
                    int c = i - x + 1 + b;
                    if (c < 0 || c >= n || (sh >> b & 1)) continue;
                    ndp[j + 1][sh | 1 << b] += dp[j][mask];  // 行 i の違反のマスを列 c に選ぶ
                }
            }
        }
        dp = move(ndp);
    }
    // 違反を j 個指定した数は（選び方）×（残りの並べ方 (N − j)!）。符号 (−1)^j を掛けて足す
    mint ans = 0;
    for (int j = 0; j <= n; j++) {
        mint cnt = 0;
        for (int mask = 0; mask < (1 << wid); mask++) cnt += dp[j][mask];
        mint term = cnt * fact[n - j];
        if (j % 2 == 0) ans += term;
        else ans -= term;
    }
    // --8<-- [end:core]

    if (n <= 8) {
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        long long brute = 0;
        do {
            bool ok = true;
            for (int i = 0; i < n; i++) {
                if (abs(p[i] - i) < x) ok = false;
            }
            if (ok) brute++;
        } while (next_permutation(p.begin(), p.end()));
        assert(ans == mint(brute));
    }
    cout << ans.val() << '\n';
}
