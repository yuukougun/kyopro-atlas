// (+1, +2) と (+2, +1) の移動だけで (0, 0) から (x, y) へ行く方法の数を、法 10^9+7 で求める。
// 回数の組 (n, m) を連立方程式で決めると、方法は 2 種類の移動の並べ方 C(n + m, n) 通りになる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint1000000007;

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

int main() {
    int x, y;
    cin >> x >> y;
    assert(0 <= x && x <= 1000000 && 0 <= y && y <= 1000000);
    init_binom((x + y) / 3);  // 移動の回数の合計は (x + y) / 3 以下

    // --8<-- [start:core]
    // n 回の (+1, +2) と m 回の (+2, +1)：x = n + 2m、y = 2n + m
    // 3(n + m) = x + y なので、x + y が 3 の倍数でなければ整数の解がない
    if ((x + y) % 3 != 0) {
        cout << 0 << '\n';
        return 0;
    }
    int n = (2 * y - x) / 3, m = (2 * x - y) / 3;
    if (n < 0 || m < 0) {  // 回数が負なら行けない（binom も 0 を返すが、意味を明示する）
        cout << 0 << '\n';
        return 0;
    }
    cout << binom(n + m, n).val() << '\n';   // n + m 回のうち、どの n 回を (+1, +2) にするか
    // --8<-- [end:core]
}
