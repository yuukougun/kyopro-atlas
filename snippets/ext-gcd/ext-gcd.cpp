// 拡張ユークリッドの互除法：a x + b y = gcd(a, b) となる整数 x, y を求める。
// 入力：Q 個の組 (a, b)（0 ≤ a, b ≤ 10^18）。出力：g x y。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// a x + b y = g = gcd(a, b) となる {g, x, y} を返す（a, b ≥ 0）
array<long long, 3> ext_gcd(long long a, long long b) {
    // 不変条件：r0 = a*x0 + b*y0 かつ r1 = a*x1 + b*y1
    long long r0 = a, x0 = 1, y0 = 0;
    long long r1 = b, x1 = 0, y1 = 1;
    while (r1 != 0) {
        long long q = r0 / r1;
        // 余り r0 - q*r1 も、係数を同じように引けば a と b の組み合わせのまま
        r0 -= q * r1;
        x0 -= q * x1;
        y0 -= q * y1;
        swap(r0, r1);
        swap(x0, x1);
        swap(y0, y1);
    }
    return {r0, x0, y0};  // r0 = gcd(a, b)
}
// --8<-- [end:core]

int main() {
    // 小さい範囲で、等式と係数の大きさ（|x| ≤ b/g、|y| ≤ a/g）を確かめる
    for (long long a = 1; a <= 60; a++) {
        for (long long b = 1; b <= 60; b++) {
            auto [g, x, y] = ext_gcd(a, b);
            assert(g == gcd(a, b));
            assert(a * x + b * y == g);
            assert(abs(x) <= b / g && abs(y) <= a / g);
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        long long a, b;
        cin >> a >> b;
        auto [g, x, y] = ext_gcd(a, b);
        assert((__int128)a * x + (__int128)b * y == g);
        cout << g << ' ' << x << ' ' << y << '\n';
    }
}
