// 割り算・sqrt を使わずに比べる：分数（傾き）の大小と、距離の大小。
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// a/b と c/d を比べる（b > 0, d > 0）。-1：a/b < c/d、0：等しい、1：a/b > c/d
int compare_frac(long long a, long long b, long long c, long long d) {
    __int128 l = (__int128)a * d, r = (__int128)c * b;  // 10^18 × 10^9 でもあふれない
    return (l > r) - (l < r);
}

// 原点から (x, y) までの距離の 2 乗。|x|, |y| ≤ 10^9 なら 2×10^18 以下で long long に入る
long long dist2(long long x, long long y) { return x * x + y * y; }
// --8<-- [end:core]

int main() {
    assert(compare_frac(1, 3, 2, 6) == 0);
    assert(compare_frac(-1, 2, 1, 3) == -1);
    assert(compare_frac(1000000000000000000LL, 999999999, 1000000000000000000LL, 1000000000) == 1);
    assert(dist2(3, 4) < dist2(0, 6));
    assert(dist2(-1000000000, 1000000000) == 2000000000000000000LL);
    long long a, b, c, d;
    cin >> a >> b >> c >> d;
    int r = compare_frac(a, b, c, d);
    cout << (r < 0 ? "<" : r == 0 ? "=" : ">") << '\n';
}
