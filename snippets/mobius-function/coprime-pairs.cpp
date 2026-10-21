#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:sieve]
// mu[0..v] を作る（v は値の上限）。mu[0] は使わない
vector<int> mobius_table(int v) {
    vector<int> mu(v + 1, 1);
    vector<bool> is_prime(v + 1, true);
    for (int p = 2; p <= v; p++) {
        if (!is_prime[p]) continue;
        for (int j = p; j <= v; j += p) {
            if (j > p) is_prime[j] = false;
            mu[j] = -mu[j];  // 素因数 p を 1 つ持つので符号を反転
        }
        long long pp = (long long)p * p;
        for (long long j = pp; j <= v; j += pp) mu[j] = 0;  // p^2 で割り切れる
    }
    return mu;
}
// --8<-- [end:sieve]

// --8<-- [start:coprime]
// 1 <= i <= n, 1 <= j <= m で gcd(i, j) = 1 となる順序対の数（O(min(n, m))）
long long coprime_direct(int n, int m, const vector<int>& mu) {
    long long res = 0;
    for (int d = 1; d <= min(n, m); d++) {
        res += (long long)mu[d] * (n / d) * (m / d);
    }
    return res;
}
// --8<-- [end:coprime]

// --8<-- [start:quotient]
// 同じ値を、商 (n/d, m/d) の組が変わらない区間ごとに束ねて O(√n + √m) で求める
// smu[k] = mu[1] + ... + mu[k]（smu[0] = 0）
long long coprime_blocks(long long n, long long m, const vector<long long>& smu) {
    long long res = 0;
    long long lim = min(n, m);
    for (long long l = 1; l <= lim;) {
        long long qn = n / l, qm = m / l;
        long long r = min(n / qn, m / qm);  // 両方の商が変わらない右端
        res += (smu[r] - smu[l - 1]) * qn * qm;
        l = r + 1;
    }
    return res;
}
// --8<-- [end:quotient]

int main() {
    int n, m;
    cin >> n >> m;
    int lim = max(n, m);
    vector<int> mu = mobius_table(lim);
    vector<long long> smu(lim + 1, 0);
    for (int k = 1; k <= lim; k++) smu[k] = smu[k - 1] + mu[k];

    long long a = coprime_direct(n, m, mu);
    long long b = coprime_blocks(n, m, smu);
    assert(a == b);
    if ((long long)n * m <= 4000000) {
        long long brute = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++) brute += (gcd(i, j) == 1);
        assert(a == brute);
    }
    // sum_{d | k} mu(d) = [k = 1] を小さい範囲で確かめる
    for (int k = 1; k <= min(lim, 1000); k++) {
        int s = 0;
        for (int d = 1; d <= k; d++)
            if (k % d == 0) s += mu[d];
        assert(s == (k == 1 ? 1 : 0));
    }
    cout << a << '\n';
}
