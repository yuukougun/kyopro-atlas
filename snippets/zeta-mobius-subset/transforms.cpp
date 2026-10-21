// 部分集合の高速ゼータ変換・メビウス変換と、OR 畳み込み・AND 畳み込み。
// 入力：n と、長さ 2^n の列 f・g。
// 出力：f の部分集合ゼータ・f の上位集合ゼータ・f と g の OR 畳み込み・AND 畳み込み。
// main の中で、愚直な O(4^n) の計算と一致すること、逆変換で元に戻ることを assert で確かめる。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 部分集合ゼータ：v[S] ← Σ_{T ⊆ S} v[T]。bit を外側に回す
void subset_zeta(vector<long long>& v, int n) {
    for (int i = 0; i < n; i++)
        for (int s = 0; s < (1 << n); s++)
            if (s >> i & 1) v[s] += v[s ^ (1 << i)];
}
// 部分集合メビウス（逆変換）：同じ順で引き算にする
void subset_mobius(vector<long long>& v, int n) {
    for (int i = 0; i < n; i++)
        for (int s = 0; s < (1 << n); s++)
            if (s >> i & 1) v[s] -= v[s ^ (1 << i)];
}
// --8<-- [end:core]

// --8<-- [start:superset]
// 上位集合ゼータ：v[S] ← Σ_{T ⊇ S} v[T]。i ビット目が 0 の S に、1 にした S を足す
void superset_zeta(vector<long long>& v, int n) {
    for (int i = 0; i < n; i++)
        for (int s = 0; s < (1 << n); s++)
            if (!(s >> i & 1)) v[s] += v[s | (1 << i)];
}
void superset_mobius(vector<long long>& v, int n) {
    for (int i = 0; i < n; i++)
        for (int s = 0; s < (1 << n); s++)
            if (!(s >> i & 1)) v[s] -= v[s | (1 << i)];
}
// --8<-- [end:superset]

// --8<-- [start:convolution]
// OR 畳み込み：h[U] = Σ_{A | B = U} f[A] g[B]（部分集合ゼータ → 各点の積 → メビウス）
vector<long long> or_convolution(vector<long long> f, vector<long long> g, int n) {
    subset_zeta(f, n);
    subset_zeta(g, n);
    for (int s = 0; s < (1 << n); s++) f[s] *= g[s];
    subset_mobius(f, n);
    return f;
}
// AND 畳み込み：h[U] = Σ_{A & B = U} f[A] g[B]（上位集合の版で同じ手順）
vector<long long> and_convolution(vector<long long> f, vector<long long> g, int n) {
    superset_zeta(f, n);
    superset_zeta(g, n);
    for (int s = 0; s < (1 << n); s++) f[s] *= g[s];
    superset_mobius(f, n);
    return f;
}
// --8<-- [end:convolution]

void print(const vector<long long>& v) {
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i + 1 == v.size() ? '\n' : ' ');
}

int main() {
    int n;
    cin >> n;
    int m = 1 << n;
    vector<long long> f(m), g(m);
    for (auto& x : f) cin >> x;
    for (auto& x : g) cin >> x;

    // 愚直な計算
    vector<long long> sub(m, 0), sup(m, 0), hor(m, 0), hand(m, 0);
    for (int s = 0; s < m; s++)
        for (int t = 0; t < m; t++) {
            if ((t & s) == t) sub[s] += f[t];
            if ((t & s) == s) sup[s] += f[t];
            hor[s | t] += f[s] * g[t];
            hand[s & t] += f[s] * g[t];
        }

    vector<long long> a = f;
    subset_zeta(a, n);
    assert(a == sub);
    subset_mobius(a, n);
    assert(a == f);
    vector<long long> b = f;
    superset_zeta(b, n);
    assert(b == sup);
    superset_mobius(b, n);
    assert(b == f);
    vector<long long> c = or_convolution(f, g, n), d = and_convolution(f, g, n);
    assert(c == hor);
    assert(d == hand);

    print(sub);
    print(sup);
    print(c);
    print(d);
}
