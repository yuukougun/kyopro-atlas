#include <bits/stdc++.h>
#include <atcoder/convolution>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// 入力：N M、列 a（N 個）、列 b（M 個）。値は 0 以上 998244353 未満。
// 出力：c_k = Σ_{i+j=k} a_i b_j を 998244353 で割った余り（k = 0, ..., N+M-2）。空なら空行。

// --8<-- [start:core]
// 長さ n（2 の冪）の列を、1 の n 乗根 w の冪 w^0, w^1, ..., w^(n-1) での値に変える。
// inverse なら w の代わりに w^(-1) を使い、最後に n で割って係数に戻す
void ntt(vector<mint>& a, bool inverse) {
    int n = a.size();
    // ビット反転の順に並べ替える（再帰で偶奇に分けた後の並びを先に作る）
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    // 長さ len/2 の結果 2 つから長さ len の結果を作る（バタフライ）
    for (int len = 2; len <= n; len <<= 1) {
        mint w = mint(3).pow((998244353 - 1) / len);  // 3 は原始根。w は 1 の len 乗根
        if (inverse) w = w.inv();
        for (int i = 0; i < n; i += len) {
            mint wk = 1;
            for (int k = 0; k < len / 2; k++) {
                mint u = a[i + k], v = a[i + k + len / 2] * wk;
                a[i + k] = u + v;            // 偶の値 + w^k × 奇の値
                a[i + k + len / 2] = u - v;  // w^(k + len/2) = -w^k
                wk *= w;
            }
        }
    }
    if (inverse) {
        mint inv_n = mint(n).inv();
        for (auto& x : a) x *= inv_n;
    }
}

vector<mint> multiply(vector<mint> a, vector<mint> b) {
    if (a.empty() || b.empty()) return {};
    int len = a.size() + b.size() - 1, n = 1;
    while (n < len) n <<= 1;  // 結果の長さ以上の 2 の冪（2^23 まで）
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < n; i++) a[i] *= b[i];  // 点での値どうしの積
    ntt(a, true);
    a.resize(len);
    return a;
}
// --8<-- [end:core]

int main() {
    int n, m;
    cin >> n >> m;
    vector<mint> a(n), b(m);
    for (auto& x : a) { int v; cin >> v; x = v; }
    for (auto& y : b) { int v; cin >> v; y = v; }
    auto c = multiply(a, b);
    // 素朴な O(NM) と ACL の convolution に一致することを確かめる
    vector<mint> d(n == 0 || m == 0 ? 0 : n + m - 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) d[i + j] += a[i] * b[j];
    assert(c == d);
    assert(c == atcoder::convolution(a, b));
    // 乱数の列でも確かめる
    mt19937 rng(1);
    for (int t = 0; t < 20; t++) {
        int p = rng() % 300 + 1, q = rng() % 300 + 1;
        vector<mint> x(p), y(q);
        for (auto& v : x) v = rng();
        for (auto& v : y) v = rng();
        assert(multiply(x, y) == atcoder::convolution(x, y));
    }
    for (int k = 0; k < (int)c.size(); k++) cout << c[k].val() << (k + 1 == (int)c.size() ? "" : " ");
    cout << '\n';
}
