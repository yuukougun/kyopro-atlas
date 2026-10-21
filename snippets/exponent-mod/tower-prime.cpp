#include <bits/stdc++.h>
#include <atcoder/math>
using namespace std;

// --8<-- [start:core]
// a^(b^c) mod p を返す（p は素数、a, b, c >= 0、0^0 = 1 とする）
long long tower_mod_prime(long long a, long long b, long long c, int p) {
    if (a % p == 0) {
        // 底が p の倍数：指数 b^c が 0 なら 1、1 以上なら 0
        bool exponent_is_zero = (b == 0 && c >= 1);
        return exponent_is_zero ? 1 : 0;
    }
    // gcd(a, p) = 1 なので a^(p-1) ≡ 1。指数は p - 1 で割った余りでよい
    long long e = atcoder::pow_mod(b, c, p - 1);  // b^c mod (p - 1)
    return atcoder::pow_mod(a, e, p);
}
// --8<-- [end:core]

int main() {
    const int p = 998244353;
    // 小さい値で直接計算と比べる
    assert(tower_mod_prime(2, 3, 2, p) == 512);   // 2^9
    assert(tower_mod_prime(5, p - 1, 1, p) == 1); // 5^(p-1) ≡ 1
    assert(tower_mod_prime(p, 0, 5, p) == 1);     // p^0 = 1
    assert(tower_mod_prime(p, 3, 4, p) == 0);
    long long a, b, c;
    cin >> a >> b >> c;
    cout << tower_mod_prime(a, b, c, p) << '\n';
}
