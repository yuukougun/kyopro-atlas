// 商の列挙：i = 1..n を ⌊n/i⌋ が同じ値になる区間にまとめ、Σ⌊n/i⌋ と ⌊n/i⌋ の値の種類数を O(√n) で求める
// 入力：T、続いて T 行の n（1 <= n <= 10^12）。各行に Σ_{i=1}^{n} ⌊n/i⌋ と、⌊n/i⌋ の異なる値の個数を出す
#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// Σ_{i=1}^{n} ⌊n/i⌋：i = 1..n を ⌊n/i⌋ の値が同じになる閉区間 [l, r] に分け、
// 区間の r − l + 1 個の項がどれも q なので、まとめて足す
long long sum_floor(long long n) {
    long long sum = 0;
    for (long long l = 1; l <= n;) {
        long long q = n / l;
        long long r = n / q;  // ⌊n/i⌋ = q となる最大の i
        sum += (r - l + 1) * q;
        l = r + 1;            // 次の区間は r の次から
    }
    return sum;
}
// --8<-- [end:core]

// 区間ごとに f(l, r, q) を呼ぶ形（main の確かめに使う。本文には載せない）
template <class F>
void for_each_quotient(long long n, F f) {
    for (long long l = 1; l <= n;) {
        long long q = n / l;
        long long r = n / q;
        f(l, r, q);
        l = r + 1;
    }
}

// --8<-- [start:split]
// ⌊√n⌋ を誤差なしで求める（sqrtl の結果を前後に直す）
long long isqrt(long long n) {
    long long s = sqrtl((long double)n);
    while (s * s > n) s--;
    while ((s + 1) * (s + 1) <= n) s++;
    return s;
}

// xy <= n となる正の整数の組 (x, y) の個数 = Σ⌊n/i⌋ を、√n を境に分けて数える
// x <= s か y <= s の少なくとも一方が成り立つ（s = ⌊√n⌋）。両方が成り立つ s² 組を二重に数えるので引く
long long count_pairs_split(long long n) {
    long long s = isqrt(n), c = 0;
    for (long long x = 1; x <= s; x++) c += n / x;
    return 2 * c - s * s;
}
// --8<-- [end:split]

int main() {
    // 小さい n で、愚直な和・値の種類数と一致することを確かめる
    for (long long n = 1; n <= 3000; n++) {
        long long naive = 0;
        set<long long> vals;
        for (long long i = 1; i <= n; i++) {
            naive += n / i;
            vals.insert(n / i);
        }
        assert(sum_floor(n) == naive);
        assert(count_pairs_split(n) == naive);
        long long blocks = 0;
        for_each_quotient(n, [&](long long l, long long r, long long q) {
            assert(l <= r && n / l == q && n / r == q);  // 区間の両端で商が q
            assert(r == n || n / (r + 1) < q);           // r が最大の i
            blocks++;
        });
        assert(blocks == (long long)vals.size());
        long long s = isqrt(n);
        assert(blocks == 2 * s - (n / s == s ? 1 : 0));  // 種類数の式
    }

    int t;
    cin >> t;
    for (int k = 0; k < t; k++) {
        long long n;
        cin >> n;
        long long blocks = 0;
        for_each_quotient(n, [&](long long, long long, long long) { blocks++; });
        long long sum = sum_floor(n);
        assert(sum == count_pairs_split(n));
        cout << sum << ' ' << blocks << '\n';
    }
    return 0;
}
