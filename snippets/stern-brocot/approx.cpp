#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 分子・分母が n 以下の既約分数のうち、x/y 以下で最大のもの L と x/y 以上で最小のもの R を返す。
// 分数は {分子, 分母}。L がなければ {0, 1}、R がなければ {1, 0}。x, y は正。
pair<array<long long, 2>, array<long long, 2>> approx(long long n, long long x, long long y) {
    long long a = 0, b = 1, c = 1, d = 0;  // L = a/b < x/y < c/d = R を保つ（隣り合う：bc - ad = 1）
    while (true) {
        // 右へまとめて進む：(a + k c)/(b + k d) < x/y となる最大の k（分子・分母が n 以下の範囲で）
        __int128 k = ((__int128)x * b - (__int128)y * a - 1) / ((__int128)y * c - (__int128)x * d);
        if (c > 0) k = min<__int128>(k, (n - a) / c);
        if (d > 0) k = min<__int128>(k, (n - b) / d);
        a += (long long)k * c, b += (long long)k * d;
        // 左へまとめて進む：(c + m a)/(d + m b) > x/y となる最大の m
        __int128 m = ((__int128)y * c - (__int128)x * d - 1) / ((__int128)x * b - (__int128)y * a);
        if (a > 0) m = min<__int128>(m, (n - c) / a);
        m = min<__int128>(m, (n - d) / b);
        c += (long long)m * a, d += (long long)m * b;
        if (k == 0 && m == 0) break;  // どちらにも進めない
    }
    // 中間の分数 (a+c)/(b+d) が x/y に等しく、範囲に入るなら、それが両方の答え
    long long p = a + c, q = b + d;
    if (p <= n && q <= n && (__int128)p * y == (__int128)q * x) return {{p, q}, {p, q}};
    return {{a, b}, {c, d}};
}
// --8<-- [end:core]

int main() {
    // 3.14159 に近い、分子・分母が 1000 以下の分数（355/113 は分子が 1000 以下）
    assert((approx(1000, 314159, 100000) == pair<array<long long, 2>, array<long long, 2>>{{688, 219}, {355, 113}}));
    int t;
    cin >> t;
    while (t--) {
        long long n, x, y;
        cin >> n >> x >> y;
        auto [l, r] = approx(n, x, y);
        cout << l[0] << ' ' << l[1] << ' ' << r[0] << ' ' << r[1] << '\n';
    }
}
