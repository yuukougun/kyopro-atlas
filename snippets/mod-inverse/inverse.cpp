// 逆元を 2 通りで求める。法 m が素数ならフェルマーの小定理、一般の m なら拡張ユークリッド。
// 入力：m q、続いて q 個の a。各 a について逆元（なければ -1）を出力する。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// a^n mod m（0 <= a < m、m <= 2^31 程度を想定。積は 64bit に収まる）
long long mod_pow(long long a, long long n, long long m) {
    long long r = 1 % m;
    a %= m;
    while (n > 0) {
        if (n & 1) r = r * a % m;
        a = a * a % m;
        n >>= 1;
    }
    return r;
}

// p が素数で a が p の倍数でないときだけ正しい。a ≡ 0 だと黙って 0 を返す
long long inv_fermat(long long a, long long p) {
    return mod_pow(a, p - 2, p);
}
// --8<-- [end:core]

// --8<-- [start:extgcd]
// 一般の m（m >= 1）。gcd(a, m) != 1 なら逆元はないので -1 を返す
long long inv_extgcd(long long a, long long m) {
    a = (a % m + m) % m;            // 負の a も 0 以上に直す
    long long r0 = m, r1 = a;       // 余りの列
    long long x0 = 0, x1 = 1;       // r_i ≡ x_i * a (mod m) を保つ係数
    while (r1 != 0) {
        long long q = r0 / r1;
        swap(r0 -= q * r1, r1);
        swap(x0 -= q * x1, x1);
    }
    if (r0 != 1) return -1;          // r0 = gcd(a, m)
    return (x0 % m + m) % m;
}
// --8<-- [end:extgcd]

bool is_prime(long long n) {
    if (n < 2) return false;
    for (long long d = 2; d * d <= n; d++)
        if (n % d == 0) return false;
    return true;
}

int main() {
    long long m;
    int q;
    cin >> m >> q;
    for (int i = 0; i < q; i++) {
        long long a;
        cin >> a;
        long long y = inv_extgcd(a, m);
        if (y != -1) {
            assert(((a % m + m) % m) * y % m == 1 % m);
            if (is_prime(m)) assert(inv_fermat((a % m + m) % m, m) == y);
        }
        cout << y << '\n';
    }
}
