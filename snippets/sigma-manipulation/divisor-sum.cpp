// Σ_{K=1}^{N} K × d(K)（d(K) は K の約数の個数）を、約数 d ごとの和に入れ替えて O(N) で求める。
// 小さい N では、約数を数える愚直な二重ループと一致することを assert で確かめる。
#include <bits/stdc++.h>
using namespace std;

// 入れ替えた式：Σ_{d=1}^{N} d × (1 + 2 + … + M)、M = ⌊N/d⌋
long long solve(long long n) {
    // --8<-- [start:core]
    long long ans = 0;
    for (long long d = 1; d <= n; d++) {
        long long m = n / d;               // d の倍数 d, 2d, …, md が N 以下にある
        ans += d * (m * (m + 1) / 2);      // その和 d(1 + 2 + … + m) を一度に足す
    }
    // --8<-- [end:core]
    return ans;
}

// 元の式のまま：K ごとに約数を数える（O(N^2)。確かめる用）
long long naive(long long n) {
    long long ans = 0;
    for (long long k = 1; k <= n; k++) {
        long long cnt = 0;
        for (long long d = 1; d <= k; d++) {
            if (k % d == 0) cnt++;
        }
        ans += k * cnt;
    }
    return ans;
}

int main() {
    for (long long n = 0; n <= 300; n++) assert(solve(n) == naive(n));
    long long n;
    cin >> n;
    cout << solve(n) << '\n';
}
