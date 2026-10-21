#include <bits/stdc++.h>
#include <atcoder/convolution>
using namespace std;

// 入力：N M、列 A（N 個）、列 B（M 個）。値はどれも 0 以上。
// 出力：1 行目に、A_i + B_j = s となる組 (i, j) の数（s = 0, 1, ..., maxA + maxB）。
//       2 行目に、A_i - B_j = d となる組の数（d = -maxB, ..., maxA）。

// --8<-- [start:core]
// 和が s になる組 (i, j) の数を、すべての s について数える
vector<long long> count_sum_pairs(const vector<int>& a, const vector<int>& b) {
    int va = *max_element(a.begin(), a.end());
    int vb = *max_element(b.begin(), b.end());
    vector<long long> f(va + 1, 0), g(vb + 1, 0);
    for (int x : a) f[x]++;  // f[v] = A の中の v の個数
    for (int y : b) g[y]++;  // g[w] = B の中の w の個数
    // c[s] = Σ_{v + w = s} f[v] g[w]。組の数は N*M まであり 998244353 を超えうるので整数のまま
    return atcoder::convolution_ll(f, g);  // 長さ va + vb + 1
}
// --8<-- [end:core]

// --8<-- [start:diff]
// 差が d になる組 (i, j) の数。戻り値の添字 t が d = t - vb に当たる
vector<long long> count_diff_pairs(const vector<int>& a, const vector<int>& b) {
    int va = *max_element(a.begin(), a.end());
    int vb = *max_element(b.begin(), b.end());
    vector<long long> f(va + 1, 0), h(vb + 1, 0);
    for (int x : a) f[x]++;
    for (int y : b) h[vb - y]++;  // B の側を反転：値 w を添字 vb - w に置く
    // v + (vb - w) = t ⇔ v - w = t - vb
    return atcoder::convolution_ll(f, h);  // 長さ va + vb + 1
}
// --8<-- [end:diff]

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& y : b) cin >> y;
    auto c = count_sum_pairs(a, b);
    auto e = count_diff_pairs(a, b);
    int vb = *max_element(b.begin(), b.end());
    // 全探索と一致することを確かめる
    for (int s = 0; s < (int)c.size(); s++) {
        long long cnt = 0;
        for (int x : a) for (int y : b) cnt += (x + y == s);
        assert(c[s] == cnt);
    }
    for (int t = 0; t < (int)e.size(); t++) {
        long long cnt = 0;
        for (int x : a) for (int y : b) cnt += (x - y == t - vb);
        assert(e[t] == cnt);
    }
    for (int s = 0; s < (int)c.size(); s++) cout << c[s] << (s + 1 == (int)c.size() ? '\n' : ' ');
    for (int t = 0; t < (int)e.size(); t++) cout << e[t] << (t + 1 == (int)e.size() ? '\n' : ' ');
}
