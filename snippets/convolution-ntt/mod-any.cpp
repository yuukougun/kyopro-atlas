#include <bits/stdc++.h>
#include <atcoder/convolution>
using namespace std;

// 入力：N M、列 a（N 個）、列 b（M 個）。値は 0 以上 10^9+7 未満。
// 出力：c_k = Σ_{i+j=k} a_i b_j を 10^9+7 で割った余り（k = 0, ..., N+M-2）。

// --8<-- [start:core]
const long long MOD = 1000000007;

// 各値を 2^15 進の 2 桁 a = a1 * 2^15 + a0 に分け、4 回の convolution_ll で掛ける。
// 桁どうしの積は 2^30 未満、その和は 2^30 * min(N, M) 未満なので long long に収まる
vector<long long> convolution_mod_any(const vector<long long>& a, const vector<long long>& b) {
    int n = a.size(), m = b.size();
    if (n == 0 || m == 0) return {};
    const long long B = 1 << 15;
    vector<long long> a0(n), a1(n), b0(m), b1(m);
    for (int i = 0; i < n; i++) a0[i] = a[i] % B, a1[i] = a[i] / B;
    for (int j = 0; j < m; j++) b0[j] = b[j] % B, b1[j] = b[j] / B;
    auto c00 = atcoder::convolution_ll(a0, b0);
    auto c01 = atcoder::convolution_ll(a0, b1);
    auto c10 = atcoder::convolution_ll(a1, b0);
    auto c11 = atcoder::convolution_ll(a1, b1);
    vector<long long> c(n + m - 1);
    long long sh1 = B % MOD, sh2 = B * B % MOD;
    for (int k = 0; k < n + m - 1; k++) {
        long long x = c11[k] % MOD * sh2 % MOD;
        x += (c01[k] + c10[k]) % MOD * sh1 % MOD;
        x += c00[k] % MOD;
        c[k] = x % MOD;
    }
    return c;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<long long> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& y : b) cin >> y;
    auto c = convolution_mod_any(a, b);
    // 素朴な O(NM) と一致することを確かめる
    vector<long long> d(n + m - 1, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) d[i + j] = (d[i + j] + a[i] * b[j] % MOD) % MOD;
    assert(c == d);
    for (int k = 0; k < (int)c.size(); k++) cout << c[k] << (k + 1 == (int)c.size() ? '\n' : ' ');
}
