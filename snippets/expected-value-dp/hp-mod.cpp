// HP が n の相手に、確率 p で 2、確率 1 − p で 1 のダメージを与える攻撃を繰り返す。
// HP が 0 以下になるまでの攻撃回数の期待値を mod 998244353 で求める（p は百分率 P で入力）。
// 入力：N P。出力：期待値 mod 998244353
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// e[h] ＝ HP が h のときから倒すまでの攻撃回数の期待値
mint expected_attacks(int n, mint p) {
    vector<mint> e(n + 1);
    e[0] = 0;  // 終状態：もう攻撃しない
    for (int h = 1; h <= n; h++) {
        // 1 回攻撃してから、移った先の期待値を確率で重み付けて足す
        e[h] = 1 + p * e[max(h - 2, 0)] + (1 - p) * e[h - 1];
    }
    return e[n];
}
// --8<-- [end:core]

int main() {
    int n, pp;
    cin >> n >> pp;
    mint p = mint(pp) / 100;  // P% を mod の値にする
    assert(1 <= n);
    cout << expected_attacks(n, p).val() << '\n';
}
