// マス 0〜N−1 のすごろく。マス i（i < N−1）では 0〜A_i の目が等確率のサイコロを振り、出た目だけ進む。
// マス 0 から始めてマス N−1 に着くまでに振る回数の期待値を求める（A_i ≥ 1、i + A_i ≤ N−1）。
// 入力：N、A_0..A_{N−2}。出力：期待値（小数点以下 10 桁）
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// e[i] ＝ マス i から N−1 に着くまでに振る回数の期待値
// 0 の目（自己ループ）を移項すると e[i] = ((A_i + 1) + Σ_{k=1}^{A_i} e[i+k]) / A_i
double expected_rolls(const vector<int>& a) {
    int n = (int)a.size() + 1;
    vector<double> e(n), suf(n + 1);  // suf[i] = e[i] + e[i+1] + … + e[n−1]
    e[n - 1] = 0;                     // 終状態
    suf[n] = 0;
    suf[n - 1] = e[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        double sum = suf[i + 1] - suf[i + a[i] + 1];  // e[i+1] + … + e[i+A_i]
        e[i] = (a[i] + 1 + sum) / a[i];
        suf[i] = suf[i + 1] + e[i];
    }
    return e[0];
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<int> a(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i];
        assert(1 <= a[i] && i + a[i] <= n - 1);
    }
    cout << fixed << setprecision(10) << expected_rolls(a) << '\n';
}
