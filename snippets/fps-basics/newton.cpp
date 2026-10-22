#include <bits/stdc++.h>
#include <atcoder/convolution>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

// f の先頭 n 項だけを残す（足りなければ 0 で埋める）
vector<mint> prefix(vector<mint> f, int n) {
    f.resize(n);
    return f;
}

// --8<-- [start:inv]
// 1/f の先頭 n 項。f[0] != 0 が必要
// 精度を 1 → 2 → 4 → … と倍にする：g ← g (2 − f g)
vector<mint> fps_inv(const vector<mint>& f, int n) {
    assert(!f.empty() && f[0] != 0);
    vector<mint> g = {f[0].inv()};
    for (int m = 1; m < n; m *= 2) {
        vector<mint> fg = prefix(atcoder::convolution(prefix(f, 2 * m), g), 2 * m);
        for (auto& v : fg) v = -v;
        fg[0] += 2;
        g = prefix(atcoder::convolution(g, fg), 2 * m);
    }
    return prefix(g, n);
}
// --8<-- [end:inv]

// --8<-- [start:log-exp]
// log f の先頭 n 項。f[0] == 1 が必要。log f = ∫ (f' / f)
vector<mint> fps_log(const vector<mint>& f, int n) {
    assert(!f.empty() && f[0] == 1);
    vector<mint> df(max(n - 1, 0));
    for (int i = 1; i < n && i < (int)f.size(); i++) df[i - 1] = f[i] * i;
    vector<mint> q = prefix(atcoder::convolution(df, fps_inv(f, n)), n);
    vector<mint> res(n);
    for (int i = 1; i < n; i++) res[i] = q[i - 1] / i;  // 積分（定数項は 0）
    return res;
}

// exp f の先頭 n 項。f[0] == 0 が必要。g ← g (1 − log g + f)
vector<mint> fps_exp(const vector<mint>& f, int n) {
    assert(f.empty() || f[0] == 0);
    vector<mint> g = {1};
    for (int m = 1; m < n; m *= 2) {
        vector<mint> h = fps_log(g, 2 * m);
        for (int i = 0; i < 2 * m; i++) h[i] = (i < (int)f.size() ? f[i] : 0) - h[i];
        h[0] += 1;
        g = prefix(atcoder::convolution(g, h), 2 * m);
    }
    return prefix(g, n);
}
// --8<-- [end:log-exp]

// 確かめ用の素朴な O(n^2) の逆元：f g = 1 の係数を下から決める
vector<mint> naive_inv(const vector<mint>& f, int n) {
    vector<mint> g(n);
    mint i0 = f[0].inv();
    for (int k = 0; k < n; k++) {
        mint s = (k == 0 ? 1 : 0);
        for (int j = 1; j <= k && j < (int)f.size(); j++) s -= f[j] * g[k - j];
        g[k] = s * i0;
    }
    return g;
}

// 確かめ用の素朴な exp：g' = f' g の係数を下から決める
vector<mint> naive_exp(const vector<mint>& f, int n) {
    vector<mint> g(n);
    if (n > 0) g[0] = 1;
    for (int k = 1; k < n; k++) {
        mint s = 0;
        for (int j = 1; j <= k && j < (int)f.size(); j++) s += f[j] * j * g[k - j];
        g[k] = s / k;
    }
    return g;
}

void print(const vector<mint>& v) {
    for (int i = 0; i < (int)v.size(); i++) cout << v[i].val() << (i + 1 < (int)v.size() ? " " : "");
    cout << '\n';
}

int main() {
    // 乱数の列で、ニュートン法と素朴な方法が一致することを確かめる
    mt19937 rng(12345);
    for (int n = 1; n <= 70; n++) {
        vector<mint> f(n);
        for (auto& v : f) v = rng() % 998244353;
        f[0] = 1;
        assert(fps_inv(f, n) == naive_inv(f, n));
        assert(fps_exp(fps_log(f, n), n) == f);  // exp と log は互いに逆
        vector<mint> h = f;
        h[0] = 0;
        assert(fps_exp(h, n) == naive_exp(h, n));
    }

    // 入力：n と f の係数 a_0 (= 1), …, a_{n-1}。1/f・log f・exp(f − 1) の先頭 n 項を出す
    int n;
    cin >> n;
    vector<mint> f(n);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        f[i] = a;
    }
    print(fps_inv(f, n));
    print(fps_log(f, n));
    vector<mint> h = f;
    h[0] = 0;
    print(fps_exp(h, n));
}
