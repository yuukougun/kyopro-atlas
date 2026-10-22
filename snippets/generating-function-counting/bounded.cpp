#include <bits/stdc++.h>
#include <atcoder/convolution>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:power]
// f の k 乗を、x^deg より上を捨てながら繰り返し二乗法で求める
vector<mint> pow_truncated(vector<mint> f, long long k, int deg) {
    vector<mint> res = {1};
    f.resize(min((int)f.size(), deg + 1));
    while (k > 0) {
        if (k & 1) {
            res = atcoder::convolution(res, f);
            res.resize(min((int)res.size(), deg + 1));
        }
        k >>= 1;
        if (k > 0) {
            f = atcoder::convolution(f, f);
            f.resize(min((int)f.size(), deg + 1));
        }
    }
    return res;
}
// --8<-- [end:power]

// --8<-- [start:closed]
// [x^k] (1 + x + ... + x^c)^n = [x^k] (1 - x^(c+1))^n / (1 - x)^n
//   = Σ_j (-1)^j C(n, j) C(k - j(c+1) + n - 1, n - 1)
mint bounded_closed(int n, int c, int k, const vector<mint>& fact, const vector<mint>& ifact) {
    if (n == 0) return k == 0 ? 1 : 0;  // C(-1, -1) に頼らず空の積を分ける
    auto binom = [&](int a, int b) -> mint {
        if (b < 0 || a < b) return 0;
        return fact[a] * ifact[b] * ifact[a - b];
    };
    mint ans = 0;
    for (int j = 0; j <= n && (long long)j * (c + 1) <= k; j++) {
        mint term = binom(n, j) * binom(k - j * (c + 1) + n - 1, n - 1);
        ans += (j % 2 == 0) ? term : -term;
    }
    return ans;
}
// --8<-- [end:closed]

// 確かめ用：各変数を 0..c から選ぶ DP（O(n k c)）
mint bounded_naive(int n, int c, int k) {
    vector<mint> dp(k + 1, 0);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        vector<mint> nx(k + 1, 0);
        for (int s = 0; s <= k; s++) {
            for (int t = 0; t <= c && s + t <= k; t++) nx[s + t] += dp[s];
        }
        dp = nx;
    }
    return dp[k];
}

int main() {
    int n, c, k;
    cin >> n >> c >> k;
    int lim = n + k + 1;
    vector<mint> fact(lim + 1), ifact(lim + 1);
    fact[0] = 1;
    for (int i = 1; i <= lim; i++) fact[i] = fact[i - 1] * i;
    ifact[lim] = fact[lim].inv();
    for (int i = lim; i > 0; i--) ifact[i - 1] = ifact[i] * i;

    vector<mint> f(c + 1, 1);  // 1 + x + ... + x^c
    vector<mint> p = pow_truncated(f, n, k);
    mint by_power = (k < (int)p.size()) ? p[k] : mint(0);
    mint by_closed = bounded_closed(n, c, k, fact, ifact);
    assert(by_power == by_closed);
    if ((long long)n * k * (c + 1) <= 10000000) assert(bounded_naive(n, c, k) == by_closed);
    cout << by_closed.val() << '\n';
}
