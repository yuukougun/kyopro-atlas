// 一次合同式 a x ≡ b (mod m) の最小の非負の解と、解の周期 m/g を求める。
// 入力：Q 個の組 (a, b, m)（0 ≤ a, b、1 ≤ m ≤ 10^18）。出力：x と周期（解がなければ -1）。
#include <bits/stdc++.h>
using namespace std;

array<long long, 3> ext_gcd(long long a, long long b) {
    long long r0 = a, x0 = 1, y0 = 0;
    long long r1 = b, x1 = 0, y1 = 1;
    while (r1 != 0) {
        long long q = r0 / r1;
        r0 -= q * r1;
        x0 -= q * x1;
        y0 -= q * y1;
        swap(r0, r1);
        swap(x0, x1);
        swap(y0, y1);
    }
    return {r0, x0, y0};
}

// --8<-- [start:core]
// a x ≡ b (mod m) の最小の非負の解 x と周期 m/g の組を返す。解がなければ {-1, -1}
pair<long long, long long> solve_congruence(long long a, long long b, long long m) {
    a %= m;
    b %= m;  // a, b ≥ 0 とする（負なら先に m を足して非負にする）
    auto [g, x, y] = ext_gcd(a, m);  // a x + m y = g
    if (b % g != 0) return {-1, -1};  // g で割り切れなければ解なし
    long long mg = m / g;
    // 両辺と法を g で割ると (a/g) x ≡ b/g (mod m/g) で、x は a/g の逆元
    long long inv = (x % mg + mg) % mg;              // 負の係数を [0, m/g) に直す
    long long ans = (long long)((__int128)inv * (b / g) % mg);  // 積は 10^36 になりうる
    return {ans, mg};
}
// --8<-- [end:core]

int main() {
    // 小さい範囲で全探索と照らし合わせる
    for (long long m = 1; m <= 30; m++) {
        for (long long a = 0; a < m; a++) {
            for (long long b = 0; b < m; b++) {
                long long best = -1;
                for (long long t = 0; t < m; t++) {
                    if (a * t % m == b) {
                        best = t;
                        break;
                    }
                }
                auto [x, p] = solve_congruence(a, b, m);
                assert(x == best);
                if (x != -1) assert(m % p == 0 && x < p);
            }
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        long long a, b, m;
        cin >> a >> b >> m;
        auto [x, p] = solve_congruence(a, b, m);
        if (x == -1) cout << -1 << '\n';
        else cout << x << ' ' << p << '\n';
    }
}
