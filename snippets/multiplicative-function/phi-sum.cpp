#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

// --8<-- [start:core]
// Σ_{i ≤ N} φ(i) mod 998244353。φ * 1 = id から
// S(n) = n(n+1)/2 − Σ_{i=2}^{n} S(⌊n/i⌋)。
// n ≤ K は篩の累積和、n > K は ⌊N/n⌋ を添字にしてメモする。
struct PhiSum {
    long long n, K;
    vector<long long> small;  // small[x] = S(x)（x ≤ K）
    vector<long long> big;    // big[k] = S(⌊N/k⌋)（⌊N/k⌋ > K）
    vector<bool> done;

    PhiSum(long long n_) : n(n_) {
        K = max(1LL, (long long)cbrtl((long double)n * n));  // 約 N^{2/3}
        K = min(K, n);
        vector<long long> phi(K + 1);
        iota(phi.begin(), phi.end(), 0LL);
        for (long long p = 2; p <= K; p++) {
            if (phi[p] != p) continue;  // p は合成数
            for (long long j = p; j <= K; j += p) phi[j] -= phi[j] / p;
        }
        small.assign(K + 1, 0);
        for (long long x = 1; x <= K; x++) small[x] = (small[x - 1] + phi[x]) % MOD;
        big.assign(n / K + 2, 0);
        done.assign(n / K + 2, false);
    }

    long long tri(long long m) {  // m(m+1)/2 mod MOD
        m %= MOD;
        return m * ((m + 1) % MOD) % MOD * ((MOD + 1) / 2) % MOD;
    }

    long long S(long long m) {
        if (m <= K) return small[m];
        long long k = n / m;  // m = ⌊N/k⌋
        if (done[k]) return big[k];
        long long res = tri(m);
        for (long long l = 2; l <= m;) {
            long long q = m / l, r = m / q;  // ⌊m/i⌋ = q となる i は [l, r]
            res -= (r - l + 1) % MOD * S(q) % MOD;
            l = r + 1;
        }
        res %= MOD;
        if (res < 0) res += MOD;
        done[k] = true;
        return big[k] = res;
    }
};
// --8<-- [end:core]

int main() {
    // 小さい n で、φ を素朴に足した値と一致することを確かめる
    long long acc = 0;
    for (long long n = 1; n <= 2000; n++) {
        long long ph = n, x = n;
        for (long long p = 2; p * p <= x; p++) {
            if (x % p == 0) {
                while (x % p == 0) x /= p;
                ph -= ph / p;
            }
        }
        if (x > 1) ph -= ph / x;
        acc += ph;
        PhiSum ps(n);
        assert(ps.S(n) == acc % MOD);
    }

    long long n;
    cin >> n;
    PhiSum ps(n);
    cout << ps.S(n) << '\n';
}
