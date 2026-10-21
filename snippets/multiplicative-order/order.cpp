#include <bits/stdc++.h>
using namespace std;

// a * b mod m。m が 10^12 程度でも溢れないよう __int128 で掛ける
long long mul_mod(long long a, long long b, long long m) {
    return (long long)((__int128)a * b % m);
}

long long pow_mod(long long a, long long n, long long m) {
    long long r = 1 % m;
    a %= m;
    while (n > 0) {
        if (n & 1) r = mul_mod(r, a, m);
        a = mul_mod(a, a, m);
        n >>= 1;
    }
    return r;
}

// n の素因数を重複なしで返す。O(√n)
vector<long long> prime_factors(long long n) {
    vector<long long> ps;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p != 0) continue;
        ps.push_back(p);
        while (n % p == 0) n /= p;
    }
    if (n > 1) ps.push_back(n);
    return ps;
}

// φ(m) を試し割りで求める。O(√m)
long long euler_phi(long long m) {
    long long res = m;
    for (long long p : prime_factors(m)) res -= res / p;
    return res;
}

// --8<-- [start:core]
// gcd(a, m) = 1 のときの a の位数。phi は φ(m)、ps は phi の素因数（重複なし）
// O(log phi × log m)
long long multiplicative_order(long long a, long long m, long long phi,
                               const vector<long long>& ps) {
    long long d = phi;  // 位数の倍数であることを保つ
    for (long long q : ps) {
        // d/q もまだ位数の倍数なら q を 1 つ取り除く
        while (d % q == 0 && pow_mod(a, d / q, m) == 1) d /= q;
    }
    return d;
}
// --8<-- [end:core]

// --8<-- [start:root]
// 素数 p の最小の原始根。p − 1 の各素因数 q で g^((p−1)/q) ≠ 1 なら原始根
long long primitive_root(long long p) {
    if (p == 2) return 1;
    vector<long long> ps = prime_factors(p - 1);
    for (long long g = 2;; g++) {
        bool ok = true;
        for (long long q : ps) {
            if (pow_mod(g, (p - 1) / q, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}
// --8<-- [end:root]

int main() {
    // 位数を 1 から順に試す素朴な方法と比べる
    for (long long m = 1; m <= 300; m++) {
        long long phi = euler_phi(m);
        vector<long long> ps = prime_factors(phi);
        for (long long a = 0; a < m; a++) {
            if (gcd(a, m) != 1) continue;
            long long k = 1;
            while (pow_mod(a, k, m) != 1 % m) k++;
            assert(multiplicative_order(a, m, phi, ps) == k);
            assert(phi % k == 0);
        }
    }
    // 素数 p で、位数が d の元はちょうど φ(d) 個
    for (long long p : {2, 3, 5, 7, 13, 31, 97, 101, 211}) {
        vector<long long> ps = prime_factors(p - 1);
        map<long long, long long> cnt;
        for (long long a = 1; a < p; a++) cnt[multiplicative_order(a, p, p - 1, ps)]++;
        for (auto [d, c] : cnt) assert((p - 1) % d == 0 && c == euler_phi(d));
        long long g = primitive_root(p);
        assert(multiplicative_order(g, p, p - 1, ps) == p - 1);
    }
    assert(primitive_root(998244353) == 3);
    assert(primitive_root(7) == 3);
    assert(primitive_root(469762049) == 3);
    assert(primitive_root(1000000007) == 5);
    assert(primitive_root(200003) == 2);
    long long a, m;
    cin >> a >> m;
    long long phi = euler_phi(m);
    cout << multiplicative_order(a, m, phi, prime_factors(phi)) << ' ' << primitive_root(m) << '\n';
}
