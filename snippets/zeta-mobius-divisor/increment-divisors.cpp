// 各操作で「i の約数 j すべての A_j に 1 を足す」を何回でも行い、A をすべて等しくする最小の操作回数（できなければ -1）。
// 操作 i の回数を x_i、最後の共通の値を T とすると、T - A_j = Σ_{j | i} x_i（倍数ゼータ）なので、
// x は (T - A) の倍数メビウス変換で、T の 1 次式 x_i = c_i T + d_i になる。x_i ≥ 0 から T の範囲を求める。
#include <bits/stdc++.h>
using namespace std;

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

void multiple_mobius(vector<long long>& v, const vector<int>& ps) {
    int n = (int)v.size() - 1;
    for (int p : ps)
        for (int i = 1; 1LL * i * p <= n; i++) v[i] -= v[i * p];
}

long long floor_div(long long a, long long b) {  // b > 0
    return a >= 0 ? a / b : -((-a + b - 1) / b);
}
long long ceil_div(long long a, long long b) {  // b > 0
    return -floor_div(-a, b);
}

int main() {
    int n;
    cin >> n;
    vector<long long> a(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> ps = primes_upto(n);

    // --8<-- [start:core]
    // x_i = c_i T + d_i：T の係数 c は「すべて 1」の、定数 d は「-A」の倍数メビウス変換
    vector<long long> c(n + 1, 1), d(n + 1, 0);
    for (int i = 1; i <= n; i++) d[i] = -a[i];
    multiple_mobius(c, ps);
    multiple_mobius(d, ps);

    // すべての i で c_i T + d_i ≥ 0 となる整数 T の範囲 [lo, hi]
    const long long INF = LLONG_MAX / 4;
    long long lo = -INF, hi = INF;
    bool ok = true;
    for (int i = 1; i <= n; i++) {
        if (c[i] > 0) lo = max(lo, ceil_div(-d[i], c[i]));
        else if (c[i] < 0) hi = min(hi, floor_div(d[i], -c[i]));
        else if (d[i] < 0) ok = false;  // T によらず x_i < 0
    }
    // 操作の総数は Σ x_i = T - A_1（1 はすべての i の約数）なので、T は小さいほどよい
    cout << (ok && lo <= hi ? lo - a[1] : -1) << '\n';
    // --8<-- [end:core]
}
