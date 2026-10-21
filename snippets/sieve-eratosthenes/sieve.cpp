#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// is_prime[x]：x が素数なら true（0 ≤ x ≤ n）
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = false;
    if (n >= 1) is_prime[1] = false;
    for (long long p = 2; p * p <= n; p++) {
        if (!is_prime[p]) continue;
        for (long long j = p * p; j <= n; j += p) is_prime[j] = false;  // p² から消す
    }
    return is_prime;
}
// --8<-- [end:core]

int main() {
    int n, q;
    cin >> n >> q;
    vector<bool> is_prime = sieve(n);
    // --8<-- [start:prefix]
    // s[i]：区間 [0, i) にある素数の個数（半開区間）
    vector<int> s(n + 2, 0);
    for (int i = 0; i <= n; i++) s[i + 1] = s[i] + (is_prime[i] ? 1 : 0);
    for (int k = 0; k < q; k++) {
        int l, r;  // 閉区間 [l, r]（0 ≤ l ≤ r ≤ n）
        cin >> l >> r;
        cout << s[r + 1] - s[l] << '\n';
    }
    // --8<-- [end:prefix]
    // 小さい範囲で、試し割りの結果と一致することを確かめる
    for (int x = 0; x <= min(n, 1000); x++) {
        bool ok = x >= 2;
        for (int d = 2; d * d <= x; d++) if (x % d == 0) ok = false;
        assert(is_prime[x] == ok);
    }
}
