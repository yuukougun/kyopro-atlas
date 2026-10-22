#include <bits/stdc++.h>
using namespace std;

long long isqrt_ll(long long n) {
    long long r = sqrtl((long double)n);
    while (r * r > n) r--;
    while ((r + 1) * (r + 1) <= n) r++;
    return r;
}

// --8<-- [start:core]
// N 以下の素数の個数 π(N)。商の値 x = ⌊N/k⌋ ごとに S(x) を持つ。
// lo[x] = S(x)（x ≤ v）、hi[k] = S(⌊N/k⌋)（k ≤ v）。
// 初めは S(x) = x − 1（2 以上の整数をすべて素数とみなす）。
long long prime_count(long long n) {
    if (n < 2) return 0;
    long long v = isqrt_ll(n);
    vector<long long> lo(v + 1), hi(v + 1);
    for (long long x = 1; x <= v; x++) lo[x] = x - 1;
    for (long long k = 1; k <= v; k++) hi[k] = n / k - 1;
    for (long long p = 2; p <= v; p++) {
        if (lo[p] == lo[p - 1]) continue;  // p は合成数
        long long sp = lo[p - 1];          // p 未満の素数の個数
        long long p2 = p * p;
        // 大きい x から更新する（S(x/p) は更新前の値を読む）
        long long kmax = min(v, n / p2);
        for (long long k = 1; k <= kmax; k++) {
            long long d = k * p;  // ⌊N/k⌋/p = ⌊N/d⌋
            long long s = (d <= v) ? hi[d] : lo[n / d];
            hi[k] -= s - sp;
        }
        for (long long x = v; x >= p2; x--) lo[x] -= lo[x / p] - sp;
    }
    return hi[1];
}
// --8<-- [end:core]

int main() {
    // 小さい n で、エラトステネスの篩の数え上げと一致することを確かめる
    const int M = 20000;
    vector<bool> comp(M + 1, false);
    int cnt = 0;
    for (int i = 2; i <= M; i++) {
        if (!comp[i]) {
            cnt++;
            for (long long j = (long long)i * i; j <= M; j += i) comp[j] = true;
        }
        assert(prime_count(i) == cnt);
    }
    assert(prime_count(0) == 0 && prime_count(1) == 0);

    int q;
    cin >> q;
    while (q--) {
        long long n;
        cin >> n;
        cout << prime_count(n) << '\n';
    }
}
