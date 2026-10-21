// 撹乱順列の数 D_n（p_i ≠ i がすべての i で成り立つ長さ n の順列の数）を 998244353 で割った余り。
// 包除の式と漸化式 D_n = (n - 1)(D_{n-1} + D_{n-2}) の両方で求め、一致を確かめる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    assert(0 <= n);
    vector<mint> fact(n + 1), ifact(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
    auto binom = [&](int a, int b) -> mint {
        if (b < 0 || b > a) return 0;
        return fact[a] * ifact[b] * ifact[a - b];
    };

    // --8<-- [start:core]
    // 「p_i = i」を破る条件とみる。k 個の位置を固定点に指定すると、残りは (n - k)! 通り
    mint d = 0;
    for (int k = 0; k <= n; k++) {
        mint term = binom(n, k) * fact[n - k];
        if (k % 2 == 0) d += term;
        else d -= term;
    }
    // --8<-- [end:core]

    // 漸化式で検算する（D_0 = 1、D_1 = 0）
    vector<mint> dp(max(n + 1, 2));
    dp[0] = 1;
    dp[1] = 0;
    for (int i = 2; i <= n; i++) dp[i] = mint(i - 1) * (dp[i - 1] + dp[i - 2]);
    assert(d == dp[n]);

    cout << d.val() << '\n';
}
