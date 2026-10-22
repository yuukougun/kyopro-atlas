#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// y[i] = f(i)（i = 0, 1, ..., d）から f(t) を O(d) で求める。f の次数は d 以下で、d < 法 とする
mint lagrange_eval(const vector<mint>& y, long long t) {
    int d = (int)y.size() - 1;
    if (0 <= t && t <= d) return y[t];
    vector<mint> fact(d + 1), ifact(d + 1);
    fact[0] = 1;
    for (int i = 1; i <= d; i++) fact[i] = fact[i - 1] * i;
    ifact[d] = fact[d].inv();
    for (int i = d; i >= 1; i--) ifact[i - 1] = ifact[i] * i;
    mint tm = t;  // t を法で割った余り
    // pre[i] = (t-0)...(t-(i-1)) = L_i、suf[i] = (t-i)...(t-d)（R_i = suf[i+1]）。(t - i) で割らない
    vector<mint> pre(d + 2, 1), suf(d + 2, 1);
    for (int i = 0; i <= d; i++) pre[i + 1] = pre[i] * (tm - i);
    for (int i = d; i >= 0; i--) suf[i] = suf[i + 1] * (tm - i);
    mint res = 0;
    for (int i = 0; i <= d; i++) {
        // 分母 ∏_{j≠i} (i - j) = i! × (d-i)! × (-1)^(d-i)
        mint term = y[i] * pre[i] * suf[i + 1] * ifact[i] * ifact[d - i];
        res += ((d - i) % 2 == 1) ? -term : term;
    }
    return res;
}

// 1^k + 2^k + ... + n^k は n の k+1 次式なので、n = 0..k+1 の値から補間する
mint power_sum(int k, long long n) {
    vector<mint> y(k + 2);
    y[0] = 0;
    for (int x = 1; x <= k + 1; x++) y[x] = y[x - 1] + mint(x).pow(k);
    return lagrange_eval(y, n);
}
// --8<-- [end:core]

int main() {
    // 小さい k・n で愚直な和と比べる
    for (int k = 0; k <= 6; k++) {
        mint s = 0;
        for (int n = 0; n <= 30; n++) {
            if (n >= 1) s += mint(n).pow(k);
            assert(power_sum(k, n) == s);
        }
    }
    int k;
    long long n;
    cin >> k >> n;
    cout << power_sum(k, n).val() << '\n';
}
