// n 個の区別できる玉を k 色で塗り、どの色も 1 回以上使う塗り方（全射）の数を 998244353 で割った余り。
// 「色 j を使わない」を破る条件とみて、使わない色の個数 j ごとにまとめて包除する。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n, k;
    cin >> n >> k;
    assert(0 <= n && 0 <= k);
    vector<mint> fact(k + 1), ifact(k + 1);
    fact[0] = 1;
    for (int i = 1; i <= k; i++) fact[i] = fact[i - 1] * i;
    ifact[k] = fact[k].inv();
    for (int i = k; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
    auto binom = [&](int a, int b) -> mint {
        if (b < 0 || b > a) return 0;
        return fact[a] * ifact[b] * ifact[a - b];
    };

    // --8<-- [start:core]
    // 使わない色を j 個指定すると、各玉は残りの k - j 色から選ぶので (k - j)^n 通り
    mint ans = 0;
    for (int j = 0; j <= k; j++) {
        mint term = binom(k, j) * mint(k - j).pow(n);  // 0^0 = 1 として扱われる
        if (j % 2 == 0) ans += term;
        else ans -= term;
    }
    // --8<-- [end:core]

    cout << ans.val() << '\n';
}
