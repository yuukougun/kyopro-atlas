// 1〜6 の目が等確率のサイコロを、出た目の合計が N 以上になるまで振る。
// 振る回数の期待値を mod 998244353 で出力する。
// E[i] ＝ 合計が i のときから、N 以上になるまでに振る回数の期待値（i ≥ N なら 0）。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n;
    cin >> n;
    // --8<-- [start:core]
    vector<mint> e(n + 6, 0);           // e[i] = 0（i ≥ n）が境界
    mint inv6 = mint(6).inv();          // 1/6 は逆元にして掛ける
    for (int i = n - 1; i >= 0; i--) {  // 大きい i から決まる
        mint s = 0;
        for (int d = 1; d <= 6; d++) s += e[i + d];
        e[i] = 1 + s * inv6;            // 実数の式 E[i] = 1 + (Σ E[i+d]) / 6 と同じ形
    }
    cout << e[0].val() << '\n';         // val() で 0 以上 p 未満の整数を取り出す
    // --8<-- [end:core]
    // 7/6 を mod で表した値と一致する（n = 2）
    if (n == 2) assert(e[0] == mint(7) / 6);
}
