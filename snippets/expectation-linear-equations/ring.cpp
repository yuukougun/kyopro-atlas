// N 人が列に並ぶ。先頭の人は確率 1/2 で列から抜け、確率 1/2 で末尾に回る。これを残り 1 人になるまで続ける。
// 最初に前から i 番目（1 ≤ i ≤ N）にいた人が最後に残る確率を mod 998244353 で求める。
// 入力：N。出力：N 個の確率（空白区切り）
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// p[n][i] ＝ n 人の列で前から i 番目（0-indexed）の人が最後に残る確率
//   p[n][0] = 1/2 p[n][n−1]                    （抜ければ 0、回れば末尾）
//   p[n][i] = 1/2 p[n][i−1] + 1/2 p[n−1][i−1]  （i ≥ 1：先頭が回るか抜けるかで 1 つ前へ）
// 同じ n の中で 0 → 1 → … → n−1 → 0 と円環状に依存するので、p[n][0] = x とおいて一周させる
vector<mint> last_survivor(int n_max) {
    const mint half = mint(2).inv();
    vector<mint> prev = {1};                 // n = 1
    for (int n = 2; n <= n_max; n++) {
        vector<mint> a(n), b(n);             // p[n][i] = a[i] + b[i] x
        a[0] = 0, b[0] = 1;
        for (int i = 1; i < n; i++) {
            a[i] = half * a[i - 1] + half * prev[i - 1];
            b[i] = half * b[i - 1];
        }
        // x = 1/2 (a[n−1] + b[n−1] x) を解く。b[n−1] = (1/2)^(n−1) なので 1 − b[n−1]/2 ≠ 0
        mint x = half * a[n - 1] / (1 - half * b[n - 1]);
        vector<mint> cur(n);
        for (int i = 0; i < n; i++) cur[i] = a[i] + b[i] * x;
        prev = move(cur);
    }
    return prev;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    assert(n >= 1);
    auto p = last_survivor(n);
    mint total = 0;
    for (auto v : p) total += v;
    assert(total == 1);  // 誰か 1 人は必ず残る
    for (int i = 0; i < n; i++) cout << p[i].val() << (i + 1 < n ? ' ' : '\n');
}
