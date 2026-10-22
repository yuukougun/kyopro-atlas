#include <bits/stdc++.h>
#include <atcoder/convolution>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

vector<mint> stirling_row(int n) {
    auto prod = [&](auto&& self, int l, int r) -> vector<mint> {
        if (r - l == 1) return {mint(l), mint(1)};
        int m = (l + r) / 2;
        return atcoder::convolution(self(self, l, m), self(self, m, r));
    };
    if (n == 0) return {mint(1)};
    return prod(prod, 0, n);
}

// --8<-- [start:core]
// 左から見える数 - 右から見える数 = k となる 1..n の順列の数
// = sum_j c(n-1, j) * [y^k](y + 1/y)^j、(y + 1/y)^j の y^k の係数は binom(j, (j+k)/2)
mint count_diff(int n, int k) {
    k = abs(k);  // 左右を反転すると差の符号が変わるだけ
    vector<mint> fact(n + 1, 1), ifact(n + 1, 1);
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i;
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
    auto c = stirling_row(n - 1);  // 最大の値を除いた n - 1 個の上昇階乗の係数
    mint ans = 0;
    for (int j = k; j <= n - 1; j += 2) {
        int a = (j + k) / 2;  // y を選ぶ個数
        ans += c[j] * fact[j] * ifact[a] * ifact[j - a];
    }
    return ans;
}
// --8<-- [end:core]

int main() {
    // 全列挙と比べる
    for (int n = 1; n <= 7; n++) {
        map<int, long long> cnt;
        vector<int> p(n);
        iota(p.begin(), p.end(), 0);
        do {
            int l = 0, r = 0, mx = -1;
            for (int i = 0; i < n; i++) if (p[i] > mx) { l++; mx = p[i]; }
            mx = -1;
            for (int i = n - 1; i >= 0; i--) if (p[i] > mx) { r++; mx = p[i]; }
            cnt[l - r]++;
        } while (next_permutation(p.begin(), p.end()));
        for (int k = -(n - 1); k <= n - 1; k++) assert(count_diff(n, k).val() == cnt[k]);
    }
    int n, k;
    cin >> n >> k;
    cout << count_diff(n, k).val() << '\n';
}
