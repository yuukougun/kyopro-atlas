#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// 長さ n の列 a の 0 の項を 1〜m の一様な値に独立に置き換え、
// 昇順に並べたときの k 番目（1-indexed）の値の期待値を求める
// --8<-- [start:core]
mint expected_kth(int n, int m, int k, const vector<int>& a) {
    vector<mint> fact(n + 1, 1), ifact(n + 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
    auto binom = [&](int s, int t) { return fact[s] * ifact[t] * ifact[s - t]; };

    int z = 0;                      // 0 の項（値が未定の項）の個数
    vector<int> ge(m + 2, 0);       // ge[x] ＝ 決まった項のうち x 以上の個数
    for (int v : a) {
        if (v == 0) z++;
        else ge[v]++;
    }
    for (int x = m; x >= 1; x--) ge[x] += ge[x + 1];

    mint inv_m = mint(m).inv(), ans = 0;
    vector<mint> pp(z + 1), pq(z + 1);
    for (int x = 1; x <= m; x++) {
        // k 番目 ≥ x ⇔ x 以上の項が n − k + 1 個以上
        int need = (n - k + 1) - ge[x];   // 0 の項から x 以上になる必要がある個数
        if (need <= 0) { ans += 1; continue; }
        if (need > z) continue;
        mint p = mint(m - x + 1) * inv_m, q = 1 - p;  // 1 つの 0 の項が x 以上になる確率
        pp[0] = pq[0] = 1;
        for (int j = 1; j <= z; j++) pp[j] = pp[j - 1] * p, pq[j] = pq[j - 1] * q;
        for (int j = need; j <= z; j++) ans += binom(z, j) * pp[j] * pq[z - j];
    }
    return ans;  // Σ_{x=1}^{m} P(k 番目 ≥ x)
}
// --8<-- [end:core]

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    assert(1 <= k && k <= n);
    cout << expected_kth(n, m, k, a).val() << '\n';
}
