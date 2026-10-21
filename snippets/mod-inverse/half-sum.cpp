// 1 + 2 + … + X = X(X+1)/2 を 10^9+7 で割った余り（0 <= X <= 10^18）を 2 通りで求める。
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

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

// --8<-- [start:core]
// 方法 1：各因数の余りを取ってから掛け、2 の逆元を掛ける
long long tri_inv(long long x) {
    long long a = x % MOD, b = (x + 1) % MOD;
    long long inv2 = mod_pow(2, MOD - 2, MOD);  // = 500000004
    return a * b % MOD * inv2 % MOD;
}

// 方法 2：余りを取る前に、偶数の方の因数を整数のまま 2 で割る
long long tri_exact(long long x) {
    long long a = x, b = x + 1;
    if (a % 2 == 0) a /= 2; else b /= 2;
    return (a % MOD) * (b % MOD) % MOD;
}

// 誤り：(x(x+1) mod p) を整数として 2 で割る。余りは奇数のこともある
// long long tri_wrong(long long x) { return (x % MOD) * ((x + 1) % MOD) % MOD / 2; }
// --8<-- [end:core]

int main() {
    long long x;
    cin >> x;
    long long r = tri_inv(x);
    assert(r == tri_exact(x));
    cout << r << '\n';
}
