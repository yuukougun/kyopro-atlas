// 原点から (i, j) への右・上の最短路の数 C(i + j, i) を、長方形 r1 ≤ i ≤ r2、c1 ≤ j ≤ c2 のすべての点について足す（法 998244353）。
// 行 i ごとに縦の和（hockey stick）で閉じた式にし、O(r2 + c2) の前計算の後 O(r2 - r1) で求める。
// 小さい入力では二重ループの素朴な和と比べる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

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

// --8<-- [start:core]
// 行 i の和：sum_{j=0}^{c} C(i + j, i) = C(i + c + 1, i + 1)（縦の和）を使い、
// sum_{j=c1}^{c2} = [j ≤ c2 の和] − [j ≤ c1 − 1 の和] とする
mint rect_sum(int r1, int r2, int c1, int c2) {
    mint total = 0;
    for (int i = r1; i <= r2; i++) {
        total += binom(i + c2 + 1, i + 1) - binom(i + c1, i + 1);
    }
    return total;
}
// --8<-- [end:core]

int main() {
    int r1, r2, c1, c2;
    cin >> r1 >> r2 >> c1 >> c2;
    assert(0 <= r1 && r1 <= r2 && r2 <= 1000000 && 0 <= c1 && c1 <= c2 && c2 <= 1000000);
    init_binom(r2 + c2 + 1);  // 使う上の数の最大は r2 + c2 + 1
    mint ans = rect_sum(r1, r2, c1, c2);
    if ((long long)(r2 - r1 + 1) * (c2 - c1 + 1) <= 1000000) {  // 小さければ素朴な和で検算する
        mint naive = 0;
        for (int i = r1; i <= r2; i++)
            for (int j = c1; j <= c2; j++) naive += binom(i + j, i);
        assert(ans == naive);
    }
    cout << ans.val() << '\n';
}
