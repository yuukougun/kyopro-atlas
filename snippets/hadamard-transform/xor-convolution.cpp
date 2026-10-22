// アダマール変換による XOR 畳み込みと、同じ列の K 回の XOR 畳み込み（mod 998244353）。
// 入力：n と、長さ 2^n の列 a・b と、K。
// 出力：1 行目に c_k = Σ_{i XOR j = k} a_i b_j、2 行目に a を K 回 XOR 畳み込みした列（K = 0 なら単位元）。
// main の中で、愚直な O(4^n) の計算と一致することを assert で確かめる。
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// --8<-- [start:core]
// アダマール変換：bit ごとに、bit が 0 の側 x と 1 の側 y を (x + y, x - y) に置き換える
void hadamard(vector<mint>& v) {
    int m = v.size();  // 2 のべき
    for (int len = 1; len < m; len <<= 1)
        for (int i = 0; i < m; i += len << 1)
            for (int j = i; j < i + len; j++) {
                mint x = v[j], y = v[j + len];
                v[j] = x + y;
                v[j + len] = x - y;
            }
}
// XOR 畳み込み：変換 → 各点の積 → もう一度変換して 2^n で割る
vector<mint> xor_convolution(vector<mint> a, vector<mint> b) {
    hadamard(a);
    hadamard(b);
    for (size_t s = 0; s < a.size(); s++) a[s] *= b[s];
    hadamard(a);
    mint inv = mint(a.size()).inv();
    for (auto& x : a) x *= inv;
    return a;
}
// --8<-- [end:core]

// --8<-- [start:power]
// a を K 回 XOR 畳み込みした列：変換した各点を K 乗してから戻す
vector<mint> xor_power(vector<mint> a, long long k) {
    hadamard(a);
    for (auto& x : a) x = x.pow(k);
    hadamard(a);
    mint inv = mint(a.size()).inv();
    for (auto& x : a) x *= inv;
    return a;
}
// --8<-- [end:power]

void print_vec(const vector<mint>& v) {
    for (size_t i = 0; i < v.size(); i++) cout << v[i].val() << (i + 1 == v.size() ? '\n' : ' ');
}

int main() {
    int n;
    long long k;
    cin >> n;
    int m = 1 << n;
    vector<mint> a(m), b(m);
    for (auto& x : a) { int t; cin >> t; x = t; }
    for (auto& x : b) { int t; cin >> t; x = t; }
    cin >> k;

    // 愚直な計算
    vector<mint> naive(m, 0);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++) naive[i ^ j] += a[i] * b[j];
    vector<mint> pw(m, 0);
    pw[0] = 1;  // 0 回の畳み込みは単位元 (1, 0, …, 0)
    for (long long t = 0; t < k; t++) {
        vector<mint> nx(m, 0);
        for (int i = 0; i < m; i++)
            for (int j = 0; j < m; j++) nx[i ^ j] += pw[i] * a[j];
        pw = nx;
    }

    vector<mint> c = xor_convolution(a, b);
    vector<mint> p = xor_power(a, k);
    assert(c == naive);
    assert(p == pw);
    // 2 回変換すると 2^n 倍に戻る
    vector<mint> h = a;
    hadamard(h);
    hadamard(h);
    for (int i = 0; i < m; i++) assert(h[i] == a[i] * m);
    print_vec(c);
    print_vec(p);
}
