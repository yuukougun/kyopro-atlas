// 約数・倍数のゼータ変換とメビウス変換を、素数ごとの累積和で O(N log log N) で行う。
// 添字は 1..n を使い、0 は使わない（0 はすべての数の倍数になってしまうため）。
// 入力：n と a_1..a_n。出力：約数ゼータ・倍数ゼータ・a と a の GCD 畳み込み・LCM 畳み込み（添字 1..n）。
// main の中で、愚直な O(n^2) の計算と一致すること、逆変換で元に戻ることを assert で確かめる。
#include <bits/stdc++.h>
using namespace std;

// n 以下の素数の一覧（エラトステネスの篩）
vector<int> primes_upto(int n) {
    vector<bool> is_prime(n + 1, true);
    vector<int> ps;
    for (int p = 2; p <= n; p++) {
        if (!is_prime[p]) continue;
        ps.push_back(p);
        for (long long q = 1LL * p * p; q <= n; q += p) is_prime[q] = false;
    }
    return ps;
}

// --8<-- [start:divisor]
// 約数ゼータ：F[m] = Σ_{d | m} f[d]。素数 p ごとに、p の指数の小さい方から累積する
void divisor_zeta(vector<long long>& v, const vector<int>& ps) {
    int n = (int)v.size() - 1;  // 添字は 1..n
    for (int p : ps)
        for (int i = 1; 1LL * i * p <= n; i++) v[i * p] += v[i];  // i を小さい順に
}
// 約数メビウス（逆変換）：同じ式を引き算にして、i を大きい順に回す
void divisor_mobius(vector<long long>& v, const vector<int>& ps) {
    int n = (int)v.size() - 1;
    for (int p : ps)
        for (int i = n / p; i >= 1; i--) v[i * p] -= v[i];
}
// --8<-- [end:divisor]

// --8<-- [start:multiple]
// 倍数ゼータ：G[d] = Σ_{d | m, m ≤ n} f[m]。p の指数の大きい方から累積する
void multiple_zeta(vector<long long>& v, const vector<int>& ps) {
    int n = (int)v.size() - 1;
    for (int p : ps)
        for (int i = n / p; i >= 1; i--) v[i] += v[i * p];  // i を大きい順に
}
// 倍数メビウス（逆変換）：引き算にして、i を小さい順に回す
void multiple_mobius(vector<long long>& v, const vector<int>& ps) {
    int n = (int)v.size() - 1;
    for (int p : ps)
        for (int i = 1; 1LL * i * p <= n; i++) v[i] -= v[i * p];
}
// --8<-- [end:multiple]

// --8<-- [start:convolution]
// GCD 畳み込み：h[k] = Σ_{gcd(i, j) = k} f[i] g[j]（倍数ゼータ → 各点の積 → 倍数メビウス）
vector<long long> gcd_convolution(vector<long long> f, vector<long long> g, const vector<int>& ps) {
    multiple_zeta(f, ps);
    multiple_zeta(g, ps);
    for (size_t k = 1; k < f.size(); k++) f[k] *= g[k];
    multiple_mobius(f, ps);
    return f;
}
// LCM 畳み込み：h[m] = Σ_{lcm(i, j) = m} f[i] g[j]（m ≤ n の分だけ。約数の版で同じ手順）
vector<long long> lcm_convolution(vector<long long> f, vector<long long> g, const vector<int>& ps) {
    divisor_zeta(f, ps);
    divisor_zeta(g, ps);
    for (size_t k = 1; k < f.size(); k++) f[k] *= g[k];
    divisor_mobius(f, ps);
    return f;
}
// --8<-- [end:convolution]

void print(const vector<long long>& v) {
    for (size_t i = 1; i < v.size(); i++) cout << v[i] << (i + 1 < v.size() ? ' ' : '\n');
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> ps = primes_upto(n);

    vector<long long> dz = a, mz = a;
    divisor_zeta(dz, ps);
    multiple_zeta(mz, ps);
    vector<long long> gc = gcd_convolution(a, a, ps);
    vector<long long> lc = lcm_convolution(a, a, ps);

    // 愚直な計算と比べる
    for (int m = 1; m <= n; m++) {
        long long sd = 0, sm = 0, sg = 0, sl = 0;
        for (int d = 1; d <= n; d++) {
            if (m % d == 0) sd += a[d];
            if (d % m == 0) sm += a[d];
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if (gcd(i, j) == m) sg += a[i] * a[j];
                if (lcm(1LL * i, 1LL * j) == m) sl += a[i] * a[j];
            }
        assert(dz[m] == sd && mz[m] == sm && gc[m] == sg && lc[m] == sl);
    }
    // 逆変換で元に戻る
    vector<long long> back1 = dz, back2 = mz;
    divisor_mobius(back1, ps);
    multiple_mobius(back2, ps);
    assert(back1 == a && back2 == a);

    print(dz);
    print(mz);
    print(gc);
    print(lc);
}
