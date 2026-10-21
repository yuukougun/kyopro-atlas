// 素数 p を法として、1..n の逆元を O(n) でまとめて作る（n < p が条件）。
// 入力：p n。inv[1..n] を空白区切りで出力する。
#include <bits/stdc++.h>
using namespace std;

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
// p = q*i + r（q = p / i、r = p % i < i）から i^{-1} ≡ -q * r^{-1}
vector<long long> inverse_table(int n, long long p) {
    vector<long long> inv(n + 1, 0);  // inv[0] は使わない
    if (n >= 1) inv[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = (p - (p / i) * inv[p % i] % p) % p;  // 負にしないよう p から引く
    }
    return inv;
}
// --8<-- [end:core]

int main() {
    long long p;
    int n;
    cin >> p >> n;
    assert(n < p);
    vector<long long> inv = inverse_table(n, p);
    for (int i = 1; i <= n; i++) {
        assert(inv[i] * i % p == 1);
        assert(inv[i] == mod_pow(i, p - 2, p));
        cout << inv[i] << (i == n ? '\n' : ' ');
    }
    if (n == 0) cout << '\n';
}
