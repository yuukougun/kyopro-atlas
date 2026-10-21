#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// 0 <= n のとき、r * r <= n < (r + 1) * (r + 1) となる r を返す
long long isqrt(long long n) {
    long long r = sqrtl((long double)n);  // 近い値。±1 ずれることがある
    while (r > 0 && r > n / r) r--;         // r * r > n なら減らす
    while (r + 1 <= n / (r + 1)) r++;       // (r + 1)^2 <= n なら増やす
    return r;
}
// --8<-- [end:core]

int main() {
    // 小さい値と、平方数の前後を素朴な定義と比べる
    for (long long n = 0; n <= 100000; n++) {
        long long r = isqrt(n);
        assert(r * r <= n && n < (r + 1) * (r + 1));
    }
    for (long long x : {1000000000LL, 999999999LL, 3037000499LL}) {
        assert(isqrt(x * x) == x);
        assert(isqrt(x * x - 1) == x - 1);
    }
    assert(isqrt(LLONG_MAX) == 3037000499LL);

    int q;
    cin >> q;
    while (q--) {
        long long n;
        cin >> n;
        cout << isqrt(n) << '\n';
    }
}
