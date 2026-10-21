// 長さ N の列 A について、x = 1, …, K のそれぞれで、組 i < j にわたる (A_i + A_j)^x の和を求める（法 998244353）。
// 二項定理で展開してべき乗和 S_k = sum_i A_i^k の積にし、O(NK + K^2) で求める。小さい入力では素朴な和と比べる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main() {
    int n, k_max;
    cin >> n >> k_max;
    vector<long long> a(n);
    for (auto& v : a) cin >> v;
    assert(1 <= n && 1 <= k_max);

    // 二項係数は x ≤ K だけなので、パスカルの三角形で作る
    vector<vector<mint>> c(k_max + 1, vector<mint>(k_max + 1, 0));
    for (int x = 0; x <= k_max; x++) {
        c[x][0] = 1;
        for (int i = 1; i <= x; i++) c[x][i] = c[x - 1][i - 1] + (i <= x - 1 ? c[x - 1][i] : mint(0));
    }

    // --8<-- [start:core]
    // べき乗和 s[k] = sum_i A_i^k（s[0] = N）
    vector<mint> s(k_max + 1, 0);
    for (int i = 0; i < n; i++) {
        mint p = 1;
        for (int k = 0; k <= k_max; k++) {
            s[k] += p;
            p *= a[i];
        }
    }
    vector<mint> ans(k_max + 1);
    for (int x = 1; x <= k_max; x++) {
        // 順序つきの組 (i, j) すべて（i = j も含む）の和：sum_t C(x, t) s[t] s[x - t]
        mint all = 0;
        for (int t = 0; t <= x; t++) all += c[x][t] * s[t] * s[x - t];
        // i = j の項 (2 A_i)^x = 2^x s[x] を引き、残りは i < j と i > j で同じなので 2 で割る
        all -= mint(2).pow(x) * s[x];
        ans[x] = all / 2;
    }
    // --8<-- [end:core]

    if ((long long)n * n * k_max <= 10000000) {  // 小さければ素朴な和で検算する
        for (int x = 1; x <= k_max; x++) {
            mint naive = 0;
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++) naive += mint(a[i] + a[j]).pow(x);
            assert(ans[x] == naive);
        }
    }
    for (int x = 1; x <= k_max; x++) cout << ans[x].val() << '\n';
}
