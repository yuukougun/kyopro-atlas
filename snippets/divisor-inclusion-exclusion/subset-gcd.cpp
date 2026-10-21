// 約数包除：空でない部分集合を gcd ごとに数え、gcd が 1 の個数と gcd の総和を求める
// 入力：n、続いて n 個の正の整数 a（1 <= a_i <= 10^6）
// 出力：1 行目 gcd が 1 になる空でない部分集合の個数（mod 998244353）
//       2 行目 空でない部分集合すべてについての gcd の総和（mod 998244353）
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// cnt[v]：値 v の出現回数（v = 0..m）。返す f[g]：gcd がちょうど g の空でない部分集合の個数
vector<mint> exact_gcd_subsets(const vector<long long>& cnt) {
    int m = (int)cnt.size() - 1;
    vector<mint> f(m + 1, 0);
    for (int g = m; g >= 1; g--) {
        long long c = 0;  // g の倍数である要素の個数
        for (int k = g; k <= m; k += g) c += cnt[k];
        f[g] = mint(2).pow(c) - 1;  // F(g)：g の倍数だけからなる空でない部分集合（空集合は除く）
        for (int k = 2 * g; k <= m; k += g) f[g] -= f[k];  // gcd が 2g, 3g, … のものを引く
    }
    return f;
}
// --8<-- [end:core]

// 愚直に 2^n 通りを調べる（main の確かめに使う。本文には載せない）
pair<long long, long long> brute(const vector<int>& a) {
    int n = (int)a.size();
    long long coprime = 0, sum = 0;
    for (int s = 1; s < (1 << n); s++) {
        int g = 0;
        for (int i = 0; i < n; i++) {
            if (s >> i & 1) g = gcd(g, a[i]);
        }
        if (g == 1) coprime++;
        sum += g;
    }
    return {coprime, sum};
}

pair<mint, mint> solve(const vector<int>& a) {
    int m = *max_element(a.begin(), a.end());
    vector<long long> cnt(m + 1, 0);
    for (int x : a) cnt[x]++;
    vector<mint> f = exact_gcd_subsets(cnt);
    mint sum = 0;
    for (int g = 1; g <= m; g++) sum += f[g] * g;
    return {f[1], sum};
}

int main() {
    mt19937 rng(12345);
    for (int t = 0; t < 2000; t++) {
        int n = rng() % 10 + 1;
        vector<int> a(n);
        for (int& x : a) x = rng() % 30 + 1;
        auto [c, s] = brute(a);
        auto [c2, s2] = solve(a);
        assert(mint(c) == c2 && mint(s) == s2);
    }

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    auto [c, s] = solve(a);
    cout << c.val() << '\n' << s.val() << '\n';
}
