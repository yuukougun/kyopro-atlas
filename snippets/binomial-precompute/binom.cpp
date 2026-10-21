// 素数 p = 998244353 を法として、0..n_max の階乗 fact と逆階乗 ifact を前計算し、
// クエリ (n, k) ごとに C(n, k) を O(1) で答える。範囲外（k < 0・k > n・n < 0）は 0。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
vector<mint> fact, ifact;

// 0..n_max の表を作る（n_max < p が条件）。O(n_max + log p)
void init_binom(int n_max) {
    fact.assign(n_max + 1, 1);
    ifact.assign(n_max + 1, 1);
    for (int i = 1; i <= n_max; i++) fact[i] = fact[i - 1] * i;  // 前から
    ifact[n_max] = fact[n_max].inv();                            // 逆元は 1 回だけ
    for (int i = n_max; i >= 1; i--) ifact[i - 1] = ifact[i] * i;  // 後ろから
}

mint binom(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;  // 範囲外は 0
    assert(n < (int)fact.size());           // 表が足りなければ止める
    return fact[n] * ifact[k] * ifact[n - k];
}
// --8<-- [end:core]

int main() {
    int n_max, q;
    cin >> n_max >> q;
    init_binom(n_max);
    for (int i = 0; i < q; i++) {
        int n, k;
        cin >> n >> k;
        cout << binom(n, k).val() << '\n';
    }
}
