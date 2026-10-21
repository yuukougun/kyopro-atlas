#include <bits/stdc++.h>
using namespace std;

// --8<-- [start:core]
// omega[x]：x の異なる素因数の個数（0 ≤ x ≤ n。0 と 1 は 0）
vector<int> count_distinct_prime_factors(int n) {
    vector<int> omega(n + 1, 0);
    for (int p = 2; p <= n; p++) {
        if (omega[p] != 0) continue;  // 小さい素因数を持つ = 合成数
        // p は素数。p の倍数すべてに素因数 p を数える（p² からではなく p から）
        for (int j = p; j <= n; j += p) omega[j]++;
    }
    return omega;
}
// --8<-- [end:core]

int main() {
    int n;
    cin >> n;
    vector<int> omega = count_distinct_prime_factors(n);
    for (int x = 1; x <= n; x++) cout << omega[x] << (x == n ? '\n' : ' ');
    if (n == 0) cout << '\n';
    // 小さい範囲で、試し割りの結果と一致することを確かめる
    for (int x = 1; x <= min(n, 1000); x++) {
        int m = x, c = 0;
        for (int d = 2; d * d <= m; d++) {
            if (m % d != 0) continue;
            c++;
            while (m % d == 0) m /= d;
        }
        if (m > 1) c++;
        assert(omega[x] == c);
    }
}
