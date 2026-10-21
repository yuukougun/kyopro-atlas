// 確率 P% で表が出るコインを、表が出るまで投げる回数の期待値を mod 998244353 で出力する（1 ≤ P ≤ 100）。
// 1 回投げて裏なら同じ状況に戻るので E = 1 + (1 − p)E。移項して E = 1 / p。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int P;
    cin >> P;
    // --8<-- [start:core]
    mint p = mint(P) / 100;  // P% は P × 100^(−1) として入れる
    mint q = 1 - p;          // 裏の確率
    // E = 1 + qE を移項して (1 − q)E = 1。1 − q ≡ 0 になる入力（P = 0）では割れない
    assert((1 - q).val() != 0);
    mint e = 1 / (1 - q);
    // --8<-- [end:core]
    cout << e.val() << '\n';
    if (P == 100) assert(e == 1);
}
