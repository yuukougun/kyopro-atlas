#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
const long long MOD = 998244353;

// 素数 P について、x^n ≡ y (mod P) となる正の n がある組 (x, y) の個数 mod 998244353
long long power_pair(long long P) {
    // P - 1 を素因数分解する。O(√P)
    long long m = P - 1;
    vector<pair<long long, int>> fac;  // (素数, 指数)
    for (long long p = 2; p * p <= m; p++) {
        if (m % p != 0) continue;
        int e = 0;
        while (m % p == 0) m /= p, e++;
        fac.push_back({p, e});
    }
    if (m > 1) fac.push_back({m, 1});

    // P - 1 の約数 d を (d, φ(d)) の組で作る。φ は素因数ごとの積
    vector<pair<long long, long long>> divs = {{1, 1}};
    for (auto [p, e] : fac) {
        int sz = divs.size();
        for (int i = 0; i < sz; i++) {
            auto [d, ph] = divs[i];
            long long pk = 1;
            for (int k = 1; k <= e; k++) {
                pk *= p;  // φ(p^k) = p^k - p^(k-1)
                divs.push_back({d * pk, ph * (pk - pk / p)});
            }
        }
    }

    // 位数が d の x は φ(d) 個あり、それぞれ y が d 通り。x = 0 は (0, 0) の 1 組
    long long ans = 1;
    for (auto [d, ph] : divs) ans = (ans + d % MOD * (ph % MOD)) % MOD;
    return ans;
}
// --8<-- [end:core]

// 小さい素数で、x の累乗を実際にたどって数える
long long brute(long long P) {
    long long cnt = 0;
    for (long long x = 0; x < P; x++) {
        set<long long> ys;
        long long v = x % P;
        for (long long n = 1; n <= P; n++) {
            ys.insert(v);
            v = v * x % P;
        }
        cnt += ys.size();
    }
    return cnt;
}

int main() {
    for (long long P : {2, 3, 5, 7, 11, 13, 31, 97, 101, 211, 257}) {
        assert(power_pair(P) == brute(P) % MOD);
    }
    long long P;
    cin >> P;
    cout << power_pair(P) << '\n';
}
