#include <bits/stdc++.h>
#include <atcoder/math>
using namespace std;

// a * x + b * y = gcd(a, b) となる (x, y) を求め、gcd(a, b) を返す
long long ext_gcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    long long g = ext_gcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// --8<-- [start:core]
// x ≡ r0 (mod m0) と x ≡ r1 (mod m1) を 1 つの式 x ≡ r (mod m) にまとめる。
// 解がなければ {0, 0} を返す（ACL の crt と同じ約束）。m = lcm(m0, m1) が long long に収まること。
pair<long long, long long> crt_merge(long long r0, long long m0, long long r1, long long m1) {
    r0 = (r0 % m0 + m0) % m0;  // C++ の % は負を返しうるので [0, m) に直す
    r1 = (r1 % m1 + m1) % m1;
    long long p, q;
    long long g = ext_gcd(m0, m1, p, q);  // m0 * p + m1 * q = g
    if ((r1 - r0) % g != 0) return {0, 0};  // 解の存在条件：g が r1 - r0 を割り切る
    long long u1 = m1 / g;
    // m0 * t ≡ r1 - r0 (mod m1) を g で割ると (m0 / g) * t ≡ (r1 - r0) / g (mod u1)。
    // m0 / g の逆元は p なので t ≡ (r1 - r0) / g * p (mod u1)。積は __int128 で計算する
    long long t = (long long)((__int128)((r1 - r0) / g) * p % u1);
    if (t < 0) t += u1;
    long long m = m0 * u1;  // lcm(m0, m1)
    return {r0 + m0 * t, m};  // 0 <= r0 + m0 * t < m0 * u1 = m
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<long long> r(n), m(n);
    for (int i = 0; i < n; i++) cin >> r[i] >> m[i];
    // --8<-- [start:fold]
    long long y = 0, z = 1;  // 式が 0 個のときは x ≡ 0 (mod 1)（すべての整数）
    for (int i = 0; i < n; i++) {
        tie(y, z) = crt_merge(y, z, r[i], m[i]);
        if (z == 0) break;  // 途中で矛盾したら解なし
    }
    // --8<-- [end:fold]
    // ACL の crt と結果が同じであることを確かめる
    assert(make_pair(y, z) == atcoder::crt(r, m));
    if (z == 0) {
        cout << -1 << '\n';
    } else {
        cout << y << ' ' << z << '\n';
    }
}
