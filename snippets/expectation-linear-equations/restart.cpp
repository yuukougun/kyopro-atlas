// 表が出る確率 P/Q のコインを投げ、表が K 回続いたら終わる。裏が出たら連続の回数は 0 に戻る。
// 終わるまでに投げる回数の期待値を mod 998244353 で求める（終わらないなら -1）。
// 入力：K P Q（K ≥ 1、0 ≤ P ≤ Q、1 ≤ Q < 998244353）。表の確率は P/Q。出力：期待値の mod 998244353
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// X ＝ E[0]（振り出しの期待値）を未知数とし、各状態の期待値を a + bX の形で持つ
struct Lin {
    mint a, b;
};

// E[i] ＝ 表が i 回続いた状態から終わるまでに投げる回数の期待値
// E[K] = 0、E[i] = 1 + h E[i+1] + (1 − h) E[0]（0 ≤ i < K、h は表の確率）
// 終わらない（期待値が無限大の）ときは nullopt を返す。表の確率は p/q
optional<mint> expected_tosses(int k, long long p, long long q) {
    // 終状態に着けるかは、b の値ではなくグラフで判定する。
    // 表の遷移（確率 p/q）がなければ連続 K に着けない
    if (p == 0) return nullopt;
    const mint h = mint(p) / q;             // 表の確率
    vector<Lin> e(k + 1);
    e[k] = {0, 0};                          // 終状態：定数 0
    for (int i = k - 1; i >= 0; i--) {
        // 1 + h (a' + b'X) + (1 − h) X
        e[i].a = 1 + h * e[i + 1].a;
        e[i].b = h * e[i + 1].b + (1 - h);
    }
    // X = a + bX を解く：(1 − b) X = a。着けるなら本当の b は 1 未満
    return e[0].a / (1 - e[0].b);
}
// --8<-- [end:core]

int main() {
    int k;
    long long p, q;
    cin >> k >> p >> q;
    assert(k >= 1 && 0 <= p && p <= q && 1 <= q && q < 998244353);
    auto ans = expected_tosses(k, p, q);
    if (ans) {
        cout << ans->val() << '\n';
    } else {
        cout << -1 << '\n';
    }
}
